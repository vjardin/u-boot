// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2018-2021 NXP
 * Copyright 2024 Josua Mayer <josua@solid-run.com>
 */

#include <config.h>
#include <asm/arch/clock.h>
#include <asm/arch-fsl-layerscape/fsl_icid.h>
#include <asm/arch/soc.h>
#include <asm/gpio.h>
#include <clock_legacy.h>
#include <display_options.h>
#include <dm.h>
#include <dm/platform_data/serial_pl01x.h>
#include <fdt_support.h>
#include <fsl-mc/fsl_mc.h>
#include <fsl_ddr.h>
#include <init.h>
#include <malloc.h>
#include <i2c.h>

DECLARE_GLOBAL_DATA_PTR;

int board_early_init_f(void)
{
	fsl_lsch3_early_init_f();
	return 0;
}

#ifdef CONFIG_OF_BOARD_FIXUP
void board_fix_fdt_eth(void *fdt, u32 srds_s1, u32 srds_s2, u32 is_lx2162);
void board_fix_fdt_serdes_ports(void *fdt);

static void board_fix_fdt_pci_silicon(void *fdt) {
	char *reg_names, *reg_name;
	int names_len, old_name_len, new_name_len, remaining_names_len;
	struct str_map {
		char *old_str;
		char *new_str;
	} reg_names_map[] = {
		{ "ccsr", "dbi" },
		{ "pf_ctrl", "ctrl" }
	};
	int off = -1, i = 0;

	/* skip pci fixup on silicon version 1 */
	if (IS_SVR_REV(get_svr(), 1, 0))
		return;

	/* fixup pci controller for silicon version 2 */
	off = fdt_node_offset_by_compatible(fdt, -1, "fsl,lx2160a-pcie");
	while (off != -FDT_ERR_NOTFOUND) {
		fdt_setprop(fdt, off, "compatible", "fsl,ls-pcie",
			    strlen("fsl,ls-pcie") + 1);

		reg_names = (char *)fdt_getprop(fdt, off, "reg-names",
						&names_len);
		if (!reg_names)
			continue;

		reg_name = reg_names;
		remaining_names_len = names_len - (reg_name - reg_names);
		i = 0;
		while ((i < ARRAY_SIZE(reg_names_map)) && remaining_names_len) {
			old_name_len = strlen(reg_names_map[i].old_str);
			new_name_len = strlen(reg_names_map[i].new_str);
			if (memcmp(reg_name, reg_names_map[i].old_str,
				   old_name_len) == 0) {
				/* first only leave required bytes for new_str
				 * and copy rest of the string after it
				 */
				memcpy(reg_name + new_name_len,
				       reg_name + old_name_len,
				       remaining_names_len - old_name_len);
				/* Now copy new_str */
				memcpy(reg_name, reg_names_map[i].new_str,
				       new_name_len);
				names_len -= old_name_len;
				names_len += new_name_len;
				i++;
			}

			reg_name = memchr(reg_name, '\0', remaining_names_len);
			if (!reg_name)
				break;

			reg_name += 1;

			remaining_names_len = names_len -
					      (reg_name - reg_names);
		}

		fdt_setprop(fdt, off, "reg-names", reg_names, names_len);
		off = fdt_node_offset_by_compatible(fdt, off,
						    "fsl,lx2160a-pcie");
	}
}

/* fdt fixup for u-boot itself */
int board_fix_fdt(void *fdt)
{
	/* allocate space in case properties must be added */
	fdt_increase_size(fdt, 512);

	/* fix fdt */
	board_fix_fdt_serdes_ports(fdt);
	board_fix_fdt_pci_silicon(fdt);

	return 0;
}
#endif

int checkboard(void)
{
	enum boot_src src = get_boot_src();
	char buf[64];

	cpu_name(buf);

	puts("Boot Source: ");
	if (src == BOOT_SOURCE_SD_MMC) {
		puts("SD\n");
	} else if (src == BOOT_SOURCE_SD_MMC2) {
		puts("eMMC\n");
	} else if (src == BOOT_SOURCE_XSPI_NOR) {
		puts("FlexSPI\n");
	} else {
		puts("Unknown\n");
	}

	return 0;
}

unsigned long get_board_sys_clk(void)
{
	return 100000000;
}

unsigned long get_board_ddr_clk(void)
{
	return 100000000;
}

int board_init(void)
{
#if !defined(CONFIG_SYS_EARLY_PCI_INIT)
	pci_init();
#endif

	return 0;
}

#ifdef CONFIG_BOARD_LATE_INIT
static int setup_fan_ctrl(void) {
	int ret = -ENODEV;
	struct udevice *bus, *dev;

	struct {
		const char *const machine;
		const char *const bus;
		uint8_t addr;
		u32 __iomem *const gpio_reg;
		uint32_t gpio_mask;
	} fanctrl[] = {
		{
			.machine = "solidrun,lx2160a-cex7",
			.bus = "i2c@2000000->i2c-mux@77->i2c@1",
			.addr = 0x18,
			.gpio_reg = (void *)0x02320000,
			.gpio_mask = (1 << 29),
		}, {
			.machine = "solidrun,lx2162a-som",
			.bus = "i2c@2000000",
			.addr = 0x18,
		},
	};

	for (int i = 0; i < ARRAY_SIZE(fanctrl); i++) {
		if (!of_machine_is_compatible(fanctrl[i].machine))
			continue;

		ret = uclass_get_device_by_name(UCLASS_I2C, fanctrl[i].bus, &bus);
		if (ret)
			continue;

		ret = i2c_get_chip(bus, fanctrl[i].addr, 1, &dev);
		if (ret)
			continue;

		/* set low temperatur threshold 64C, slope 1.57%/C, full-speed at 101C (safe for LX2160/LX2162 SoC) */
		ret = dm_i2c_reg_write(dev, 0x25, 0x83);
		if (ret)
			continue;

		/* change gpio direction from output to input for low->high transition with external PU */
		if (fanctrl[i].gpio_reg)
			*fanctrl[i].gpio_reg &= ~fanctrl[i].gpio_mask;

		printf("Fan:   Low 64°C, High 101°C, Slope 1.57%%\n");
	}

	return ret;
}

int fsl_board_late_init(void) {
	setup_fan_ctrl();

	return 0;
}
#endif

#ifdef CONFIG_FSL_MC_ENET
void fdt_fixup_board_enet(void *fdt)
{
	int offset;

	/* mainline linux has fsl-mc below soc node */
	offset = fdt_path_offset(fdt, "/soc/fsl-mc");

	if (offset < 0)
		/* older versions had fsl-mc at root level */
		offset = fdt_path_offset(fdt, "/fsl-mc");

	if (offset < 0) {
		printf("%s: fsl-mc node not found in device tree (error %d)\n",
		       __func__, offset);
		return;
	}

	if (get_mc_boot_status() == 0 &&
	    (is_lazy_dpl_addr_valid() || get_dpl_apply_status() == 0)) {
		fdt_status_okay(fdt, offset);
	} else {
		/* mc startup failed, disable in dtb */
		fdt_status_fail(fdt, offset);
	}
}

void board_quiesce_devices(void)
{
	fsl_mc_ldpaa_exit(gd->bd);
}
#endif

#ifdef CONFIG_OF_BOARD_SETUP
int ft_board_setup(void *blob, struct bd_info *bd)
{
	int i;
	u16 mc_memory_bank = 0;

	u64 *base;
	u64 *size;
	u64 mc_memory_base = 0;
	u64 mc_memory_size = 0;
	u16 total_memory_banks;
	int err;

	err = fdt_increase_size(blob, 512);
	if (err) {
		printf("%s fdt_increase_size: err=%s\n", __func__,
		       fdt_strerror(err));
		return err;
	}

	ft_cpu_setup(blob, bd);

	fdt_fixup_mc_ddr(&mc_memory_base, &mc_memory_size);

	if (mc_memory_base != 0)
		mc_memory_bank++;

	total_memory_banks = CONFIG_NR_DRAM_BANKS + mc_memory_bank;

	base = calloc(total_memory_banks, sizeof(u64));
	size = calloc(total_memory_banks, sizeof(u64));

	/* fixup DT for the three GPP DDR banks */
	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++) {
		base[i] = gd->bd->bi_dram[i].start;
		size[i] = gd->bd->bi_dram[i].size;
	}

#ifdef CONFIG_RESV_RAM
	/* reduce size if reserved memory is within this bank */
	if (gd->arch.resv_ram >= base[0] &&
	    gd->arch.resv_ram < base[0] + size[0])
		size[0] = gd->arch.resv_ram - base[0];
	else if (gd->arch.resv_ram >= base[1] &&
		 gd->arch.resv_ram < base[1] + size[1])
		size[1] = gd->arch.resv_ram - base[1];
	else if (gd->arch.resv_ram >= base[2] &&
		 gd->arch.resv_ram < base[2] + size[2])
		size[2] = gd->arch.resv_ram - base[2];
#endif

	if (mc_memory_base != 0) {
		for (i = 0; i <= total_memory_banks; i++) {
			if (base[i] == 0 && size[i] == 0) {
				base[i] = mc_memory_base;
				size[i] = mc_memory_size;
				break;
			}
		}
	}

	fdt_fixup_memory_banks(blob, base, size, total_memory_banks);

#ifdef CONFIG_USB_HOST
	fsl_fdt_fixup_dr_usb(blob, bd);
#endif

#ifdef CONFIG_FSL_MC_ENET
	fdt_fsl_mc_fixup_iommu_map_entry(blob);
	fdt_fixup_board_enet(blob);
	fdt_reserve_mc_mem(blob, 0x4000);
#endif
	fdt_fixup_icid(blob);

	return 0;
}
#endif
