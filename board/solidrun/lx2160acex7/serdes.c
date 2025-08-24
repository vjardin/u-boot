// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2025 Josua Mayer <josua@solid-run.com>
 *
 */

#include <fdt_support.h>

/* SerDes base address */
#define LYNX_28G_SDn_BASE(block)		((void *)0x01EA0000 + (block) * 0x10000)

/* Protocol Configuration Register 0 */
#define LYNX_28G_PCC0				0x1080
#define LYNX_28G_PCC0_PEXA_CFG			GENMASK(30, 28)
#define LYNX_28G_PCC0_PEXB_CFG			GENMASK(26, 24)

/* Protocol Configuration Register 2 */
#define LYNX_28G_PCC2				0x1088
#define LYNX_28G_PCC2_SATAA_CFG			GENMASK(30, 28)
#define LYNX_28G_PCC2_SATAB_CFG			GENMASK(26, 24)
#define LYNX_28G_PCC2_SATAC_CFG			GENMASK(22, 20)
#define LYNX_28G_PCC2_SATAD_CFG			GENMASK(18, 16)

/* Protocol Configuration Register 8 */
#define LYNX_28G_PCC8				0x10A0
#define LYNX_28G_PCC8_SGMIIA_CFG		GENMASK(30, 28)
#define LYNX_28G_PCC8_SGMIIB_CFG		GENMASK(26, 24)
#define LYNX_28G_PCC8_SGMIIC_CFG		GENMASK(22, 20)
#define LYNX_28G_PCC8_SGMIID_CFG		GENMASK(18, 16)
#define LYNX_28G_PCC8_SGMIIE_CFG		GENMASK(14, 12)
#define LYNX_28G_PCC8_SGMIIF_CFG		GENMASK(10, 8)
#define LYNX_28G_PCC8_SGMIIG_CFG		GENMASK(6, 4)
#define LYNX_28G_PCC8_SGMIIH_CFG		GENMASK(2, 0)

/* Protocol Configuration Register C */
#define LYNX_28G_PCCC				0x10B0
#define LYNX_28G_PCCC_SXGMIIA_CFG		GENMASK(30, 28)
#define LYNX_28G_PCCC_SXGMIIB_CFG		GENMASK(26, 24)
#define LYNX_28G_PCCC_SXGMIIC_CFG		GENMASK(22, 20)
#define LYNX_28G_PCCC_SXGMIID_CFG		GENMASK(18, 16)
#define LYNX_28G_PCCC_SXGMIIE_CFG		GENMASK(14, 12)
#define LYNX_28G_PCCC_SXGMIIF_CFG		GENMASK(10, 8)
#define LYNX_28G_PCCC_SXGMIIG_CFG		GENMASK(6, 4)
#define LYNX_28G_PCCC_SXGMIIH_CFG		GENMASK(2, 0)

/* Protocol Configuration Register D */
#define LYNX_28G_PCCD				0x10B4
#define LYNX_28G_PCCD_E25GA_CFG			GENMASK(30, 28)
#define LYNX_28G_PCCD_E25GB_CFG			GENMASK(26, 24)
#define LYNX_28G_PCCD_E25GC_CFG			GENMASK(22, 20)
#define LYNX_28G_PCCD_E25GD_CFG			GENMASK(18, 16)
#define LYNX_28G_PCCD_E25GE_CFG			GENMASK(14, 12)
#define LYNX_28G_PCCD_E25GF_CFG			GENMASK(10, 8)
#define LYNX_28G_PCCD_E25GG_CFG			GENMASK(6, 4)
#define LYNX_28G_PCCD_E25GH_CFG			GENMASK(2, 0)

/* Protocol Configuration Register E */
#define LYNX_28G_PCCE				0x10B8
#define LYNX_28G_PCCE_E40GA_CFG			GENMASK(30, 28)
#define LYNX_28G_PCCE_E40GB_CFG			GENMASK(26, 24)
#define LYNX_28G_PCCE_E50GA_CFG			GENMASK(22, 20)
#define LYNX_28G_PCCE_E50GB_CFG			GENMASK(18, 16)
#define LYNX_28G_PCCE_E100GA_CFG		GENMASK(14, 12)
#define LYNX_28G_PCCE_E100GB_CFG		GENMASK(10, 8)

/* Lane a General Control Register */
#define LYNX_28G_LNaGCR0(lane)			(0x800 + (lane) * 0x100 + 0x0)
#define LYNX_28G_LNaGCR0_PORT_RST_LEFT		BIT(17)
#define LYNX_28G_LNaGCR0_PORT_LN0_B		BIT(16)
#define LYNX_28G_LNaGCR0_PROTO_SEL_MSK		GENMASK(7, 3)
#define LYNX_28G_LNaGCR0_PROTO_SEL_PCI		0x0
#define LYNX_28G_LNaGCR0_PROTO_SEL_SGMII	0x8
#define LYNX_28G_LNaGCR0_PROTO_SEL_SATA		0x10
#define LYNX_28G_LNaGCR0_PROTO_SEL_XFI		0x50
#define LYNX_28G_LNaGCR0_PROTO_SEL_25G		0xD0

/* Lane a Tx Reset Control Register */
#define LYNX_28G_LNaTRSTCTL(lane)		(0x800 + (lane) * 0x100 + 0x20)
#define LYNX_28G_LNaTRSTCTL_DIS			BIT(24)

/* Lane a Rx Reset Control Register */
#define LYNX_28G_LNaRRSTCTL(lane)		(0x800 + (lane) * 0x100 + 0x40)
#define LYNX_28G_LNaRRSTCTL_DIS			BIT(24)

/* Reset Control Word 27 (RO) */
#define RCWSR27_R				((void *)0x01e00168)
#define RCWSR27_EC1_PMUX_MASK			0x00000003
#define RCWSR27_EC1_PMUX_WRIOP_MAC_17_RGMII	0x00000000
#define RCWSR27_EC2_PMUX_MASK			0x0000000C
#define RCWSR27_EC2_PMUX_WRIOP_MAC_18_RGMII	0x00000000

enum {
	DPMAC1 = 0,
	DPMAC2,
	DPMAC3,
	DPMAC4,
	DPMAC5,
	DPMAC6,
	DPMAC7,
	DPMAC8,
	DPMAC9,
	DPMAC10,
	DPMAC11,
	DPMAC12,
	DPMAC13,
	DPMAC14,
	DPMAC15,
	DPMAC16,
	DPMAC17,
	DPMAC18,
	DPMAC_MAX
};

#ifdef CONFIG_OF_BOARD_FIXUP

/* fix mac nodes based on serdes protocol */
static void board_fix_fdt_macs(void *fdt) {
	struct mac_node {
		const char *const path;
		const char *status;
		const char *mode;
	} macs[DPMAC_MAX] = {
		{ "/fsl-mc@80c000000/dpmacs/dpmac@1", "disabled" },
		{ "/fsl-mc@80c000000/dpmacs/dpmac@2", "disabled" },
		{ "/fsl-mc@80c000000/dpmacs/dpmac@3", "disabled" },
		{ "/fsl-mc@80c000000/dpmacs/dpmac@4", "disabled" },
		{ "/fsl-mc@80c000000/dpmacs/dpmac@5", "disabled" },
		{ "/fsl-mc@80c000000/dpmacs/dpmac@6", "disabled" },
		{ "/fsl-mc@80c000000/dpmacs/dpmac@7", "disabled" },
		{ "/fsl-mc@80c000000/dpmacs/dpmac@8", "disabled" },
		{ "/fsl-mc@80c000000/dpmacs/dpmac@9", "disabled" },
		{ "/fsl-mc@80c000000/dpmacs/dpmac@a", "disabled" },
		{ "/fsl-mc@80c000000/dpmacs/dpmac@b", "disabled" },
		{ "/fsl-mc@80c000000/dpmacs/dpmac@c", "disabled" },
		{ "/fsl-mc@80c000000/dpmacs/dpmac@d", "disabled" },
		{ "/fsl-mc@80c000000/dpmacs/dpmac@e", "disabled" },
		{ "/fsl-mc@80c000000/dpmacs/dpmac@f", "disabled" },
		{ "/fsl-mc@80c000000/dpmacs/dpmac@10", "disabled" },
		{ "/fsl-mc@80c000000/dpmacs/dpmac@11", "disabled" },
		{ "/fsl-mc@80c000000/dpmacs/dpmac@12", "disabled" },
	};

	struct {
		const u32 __iomem *pcr;
		const u32 pcr_ena_mask;
		const char *const mode;
		const unsigned int mac;
	} ports[] = {
		{
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIIA_CFG,
			.mode = "sgmii",
			.mac = DPMAC10,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIIB_CFG,
			.mode = "sgmii",
			.mac = DPMAC9,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIIC_CFG,
			.mode = "sgmii",
			.mac = DPMAC8,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIID_CFG,
			.mode = "sgmii",
			.mac = DPMAC7,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIIE_CFG,
			.mode = "sgmii",
			.mac = DPMAC6,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIIF_CFG,
			.mode = "sgmii",
			.mac = DPMAC5,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIIG_CFG,
			.mode = "sgmii",
			.mac = DPMAC4,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIIH_CFG,
			.mode = "sgmii",
			.mac = DPMAC3,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIA_CFG,
			.mode = "xgmii",
			.mac = DPMAC10,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIB_CFG,
			.mode = "xgmii",
			.mac = DPMAC9,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIC_CFG,
			.mode = "xgmii",
			.mac = DPMAC8,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIID_CFG,
			.mode = "xgmii",
			.mac = DPMAC7,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIE_CFG,
			.mode = "xgmii",
			.mac = DPMAC6,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIF_CFG,
			.mode = "xgmii",
			.mac = DPMAC5,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIG_CFG,
			.mode = "xgmii",
			.mac = DPMAC4,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIH_CFG,
			.mode = "xgmii",
			.mac = DPMAC3,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCD,
			.pcr_ena_mask = LYNX_28G_PCCD_E25GA_CFG,
			.mode = "25g-aui",
			.mac = DPMAC3,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCD,
			.pcr_ena_mask = LYNX_28G_PCCD_E25GB_CFG,
			.mode = "25g-aui",
			.mac = DPMAC4,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCD,
			.pcr_ena_mask = LYNX_28G_PCCD_E25GC_CFG,
			.mode = "25g-aui",
			.mac = DPMAC5,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCD,
			.pcr_ena_mask = LYNX_28G_PCCD_E25GD_CFG,
			.mode = "25g-aui",
			.mac = DPMAC6,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCD,
			.pcr_ena_mask = LYNX_28G_PCCD_E25GE_CFG,
			.mode = "25g-aui",
			.mac = DPMAC7,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCD,
			.pcr_ena_mask = LYNX_28G_PCCD_E25GF_CFG,
			.mode = "25g-aui",
			.mac = DPMAC8,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCD,
			.pcr_ena_mask = LYNX_28G_PCCD_E25GG_CFG,
			.mode = "25g-aui",
			.mac = DPMAC9,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCD,
			.pcr_ena_mask = LYNX_28G_PCCD_E25GH_CFG,
			.mode = "25g-aui",
			.mac = DPMAC10,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCE,
			.pcr_ena_mask = LYNX_28G_PCCE_E40GA_CFG,
			.mode = "xlaui4",
			.mac = DPMAC1,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCE,
			.pcr_ena_mask = LYNX_28G_PCCE_E40GB_CFG,
			.mode = "xlaui4",
			.mac = DPMAC2,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCE,
			.pcr_ena_mask = LYNX_28G_PCCE_E50GA_CFG,
			.mode = "caui2",
			.mac = DPMAC1,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCE,
			.pcr_ena_mask = LYNX_28G_PCCE_E50GB_CFG,
			.mode = "caui2",
			.mac = DPMAC2,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCE,
			.pcr_ena_mask = LYNX_28G_PCCE_E100GA_CFG,
			.mode = "caui4",
			.mac = DPMAC1,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCE,
			.pcr_ena_mask = LYNX_28G_PCCE_E100GB_CFG,
			.mode = "caui4",
			.mac = DPMAC2,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIIA_CFG,
			.mode = "sgmii",
			.mac = DPMAC18,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIIB_CFG,
			.mode = "sgmii",
			.mac = DPMAC17,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIIC_CFG,
			.mode = "sgmii",
			.mac = DPMAC16,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIID_CFG,
			.mode = "sgmii",
			.mac = DPMAC15,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIIE_CFG,
			.mode = "sgmii",
			.mac = DPMAC14,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIIF_CFG,
			.mode = "sgmii",
			.mac = DPMAC13,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIIG_CFG,
			.mode = "sgmii",
			.mac = DPMAC12,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIIH_CFG,
			.mode = "sgmii",
			.mac = DPMAC11,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIA_CFG,
			.mode = "xgmii",
			.mac = DPMAC18,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIB_CFG,
			.mode = "xgmii",
			.mac = DPMAC17,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIC_CFG,
			.mode = "xgmii",
			.mac = DPMAC16,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIID_CFG,
			.mode = "xgmii",
			.mac = DPMAC15,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIE_CFG,
			.mode = "xgmii",
			.mac = DPMAC14,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIF_CFG,
			.mode = "xgmii",
			.mac = DPMAC13,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIG_CFG,
			.mode = "xgmii",
			.mac = DPMAC12,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIH_CFG,
			.mode = "xgmii",
			.mac = DPMAC11,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCCD,
			.pcr_ena_mask = LYNX_28G_PCCD_E25GA_CFG,
			.mode = "25g-aui",
			.mac = DPMAC18,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCCD,
			.pcr_ena_mask = LYNX_28G_PCCD_E25GB_CFG,
			.mode = "25g-aui",
			.mac = DPMAC17,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCCD,
			.pcr_ena_mask = LYNX_28G_PCCD_E25GC_CFG,
			.mode = "25g-aui",
			.mac = DPMAC16,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCCD,
			.pcr_ena_mask = LYNX_28G_PCCD_E25GD_CFG,
			.mode = "25g-aui",
			.mac = DPMAC15,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCCD,
			.pcr_ena_mask = LYNX_28G_PCCD_E25GE_CFG,
			.mode = "25g-aui",
			.mac = DPMAC14,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCCD,
			.pcr_ena_mask = LYNX_28G_PCCD_E25GF_CFG,
			.mode = "25g-aui",
			.mac = DPMAC13,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCCD,
			.pcr_ena_mask = LYNX_28G_PCCD_E25GG_CFG,
			.mode = "25g-aui",
			.mac = DPMAC12,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCCD,
			.pcr_ena_mask = LYNX_28G_PCCD_E25GH_CFG,
			.mode = "25g-aui",
			.mac = DPMAC11,
		}
	};

	for (int i = 0; i < ARRAY_SIZE(ports); i++) {
		if (*ports[i].pcr & ports[i].pcr_ena_mask) {
			macs[ports[i].mac].status = "okay";
			macs[ports[i].mac].mode = ports[i].mode;
		}
	}

	/* workaround for dpmac17.18 rgmii ports */
	{
		const u32 __iomem *const rcwsr27 = RCWSR27_R;
		if ((*rcwsr27 & RCWSR27_EC1_PMUX_MASK) == RCWSR27_EC1_PMUX_WRIOP_MAC_17_RGMII) {
			macs[DPMAC17].status = "okay";
			macs[DPMAC17].mode = "rgmii-id";
		}
		if ((*rcwsr27 & RCWSR27_EC2_PMUX_MASK) == RCWSR27_EC2_PMUX_WRIOP_MAC_18_RGMII) {
			macs[DPMAC18].status = "okay";
			macs[DPMAC18].mode = "rgmii-id";
		}
	}

	for (int i = 0; i < ARRAY_SIZE(macs); i++) {
		fdt_delprop(fdt, fdt_path_offset(fdt, macs[i].path), "phy-mode");
		do_fixup_by_path_string(fdt, macs[i].path, "status", macs[i].status);
		do_fixup_by_path_string(fdt, macs[i].path, "phy-connection-type", macs[i].mode);
	}
}

static void board_fix_fdt_pci_sata(void *fdt) {
	struct {
		const u32 __iomem *pcr;
		const u32 pcr_ena_mask;
		const char *const path;
	} ports[] = {
		{
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCC0,
			.pcr_ena_mask = LYNX_28G_PCC0_PEXA_CFG,
			.path = "/pcie@3400000",
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCC0,
			.pcr_ena_mask = LYNX_28G_PCC0_PEXB_CFG,
			.path = "/pcie@3500000",
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC0,
			.pcr_ena_mask = LYNX_28G_PCC0_PEXA_CFG,
			.path = "/pcie@3600000",
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC0,
			.pcr_ena_mask = LYNX_28G_PCC0_PEXB_CFG,
			.path = "/pcie@3700000",
		}, {
			.pcr = LYNX_28G_SDn_BASE(2) + LYNX_28G_PCC0,
			.pcr_ena_mask = LYNX_28G_PCC0_PEXA_CFG,
			.path = "/pcie@3800000",
		}, {
			.pcr = LYNX_28G_SDn_BASE(2) + LYNX_28G_PCC0,
			.pcr_ena_mask = LYNX_28G_PCC0_PEXB_CFG,
			.path = "/pcie@3900000",
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC2,
			.pcr_ena_mask = LYNX_28G_PCC2_SATAA_CFG,
			.path = "/sata@3200000",
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC2,
			.pcr_ena_mask = LYNX_28G_PCC2_SATAB_CFG,
			.path = "/sata@3210000",
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC2,
			.pcr_ena_mask = LYNX_28G_PCC2_SATAC_CFG,
			.path = "/sata@3220000",
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC2,
			.pcr_ena_mask = LYNX_28G_PCC2_SATAD_CFG,
			.path = "/sata@3230000",
		},
	};

	for (int i = 0; i < ARRAY_SIZE(ports); i++) {
		const char *status = "disabled";
		if (*ports[i].pcr & ports[i].pcr_ena_mask)
			status = "okay";

		do_fixup_by_path_string(fdt, ports[i].path, "status", status);
	}
}

void board_fix_fdt_serdes_ports(void *fdt) {
	board_fix_fdt_pci_sata(fdt);
	board_fix_fdt_macs(fdt);
}

#endif /* CONFIG_OF_BOARD_FIXUP */
