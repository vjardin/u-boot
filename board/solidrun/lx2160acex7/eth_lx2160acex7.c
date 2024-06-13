// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2018-2021 NXP
 *
 */

#include <config.h>
#include <asm/io.h>
#include <command.h>
#include <fm_eth.h>
#include <fsl_mdio.h>
#include <fsl-mc/fsl_mc.h>
#include <fsl-mc/ldpaa_wriop.h>
#include <netdev.h>
#include <asm/arch/clock.h>
#include <fdt_support.h>

DECLARE_GLOBAL_DATA_PTR;

int board_eth_init(struct bd_info *bis)
{
	return pci_eth_init(bis);
}

#if defined(CONFIG_RESET_PHY_R)
void reset_phy(void)
{
#if defined(CONFIG_FSL_MC_ENET)
	mc_env_boot();
#endif
}
#endif /* CONFIG_RESET_PHY_R */

#ifndef CONFIG_CMD_TLV_EEPROM
int mac_read_from_eeprom(void)
{
	return 0;
}
#endif

int do_mac(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
	puts("Not implemented.\n");
	return CMD_RET_FAILURE;
}
