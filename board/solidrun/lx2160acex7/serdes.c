// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2025 Josua Mayer <josua@solid-run.com>
 *
 */

#include <fdt_support.h>

/* Devoce Configuration Register base address */
#define DCFG_CCSR_BASE				(void *)0x01E00000

/* Device Disable Register 1 */
#define DCFG_CCSR_DEVDISR1			0x0070
#define DCFG_CCSR_DEVDISR1_DCE			BIT(25)
#define DCFG_CCSR_DEVDISR1_SEC			BIT(22)
#define DCFG_CCSR_DEVDISR1_SATA4		BIT(19)
#define DCFG_CCSR_DEVDISR1_SATA3		BIT(18)
#define DCFG_CCSR_DEVDISR1_SATA2		BIT(17)
#define DCFG_CCSR_DEVDISR1_SATA1		BIT(16)
#define DCFG_CCSR_DEVDISR1_USB1			BIT(12)
#define DCFG_CCSR_DEVDISR1_ESDHC2		BIT(10)
#define DCFG_CCSR_DEVDISR1_QDMA			BIT(8)
#define DCFG_CCSR_DEVDISR1_ESDHC1		BIT(2)

/* Device Disable Register 2 */
#define DCFG_CCSR_DEVDISR2			0x0074
#define DCFG_CCSR_DEVDISR2_MAC18		BIT(17)
#define DCFG_CCSR_DEVDISR2_MAC17		BIT(16)
#define DCFG_CCSR_DEVDISR2_MAC16		BIT(15)
#define DCFG_CCSR_DEVDISR2_MAC15		BIT(14)
#define DCFG_CCSR_DEVDISR2_MAC14		BIT(13)
#define DCFG_CCSR_DEVDISR2_MAC13		BIT(12)
#define DCFG_CCSR_DEVDISR2_MAC12		BIT(11)
#define DCFG_CCSR_DEVDISR2_MAC11		BIT(10)
#define DCFG_CCSR_DEVDISR2_MAC10		BIT(9)
#define DCFG_CCSR_DEVDISR2_MAC9			BIT(8)
#define DCFG_CCSR_DEVDISR2_MAC8			BIT(7)
#define DCFG_CCSR_DEVDISR2_MAC7			BIT(6)
#define DCFG_CCSR_DEVDISR2_MAC6			BIT(5)
#define DCFG_CCSR_DEVDISR2_MAC5			BIT(4)
#define DCFG_CCSR_DEVDISR2_MAC4			BIT(3)
#define DCFG_CCSR_DEVDISR2_MAC3			BIT(2)
#define DCFG_CCSR_DEVDISR2_MAC2			BIT(1)
#define DCFG_CCSR_DEVDISR2_MAC1			BIT(0)

/* SerDes base address */
#define LYNX_28G_SDn_BASE(block)		(DCFG_CCSR_BASE + 0x000A0000 + (block) * 0x10000)

/* Protocol Configuration Register 0 */
#define LYNX_28G_PCC0				0x1080
#define LYNX_28G_PCC0_PEXA_CFG_MASK		GENMASK(30, 28)
#define LYNX_28G_PCC0_PEXA_CFG(val)		((val << 28) & LYNX_28G_PCC0_PEXA_CFG_MASK)
#define LYNX_28G_PCC0_PEXB_CFG_MASK		GENMASK(26, 24)
#define LYNX_28G_PCC0_PEXB_CFG(val)		((val << 24) & LYNX_28G_PCC0_PEXB_CFG_MASK)

/* Protocol Configuration Register 2 */
#define LYNX_28G_PCC2				0x1088
#define LYNX_28G_PCC2_SATAA_CFG_MASK		GENMASK(30, 28)
#define LYNX_28G_PCC2_SATAA_CFG(val)		((val << 28) & LYNX_28G_PCC2_SATAA_CFG_MASK)
#define LYNX_28G_PCC2_SATAB_CFG_MASK		GENMASK(26, 24)
#define LYNX_28G_PCC2_SATAB_CFG(val)		((val << 24) & LYNX_28G_PCC2_SATAB_CFG_MASK)
#define LYNX_28G_PCC2_SATAC_CFG_MASK		GENMASK(22, 20)
#define LYNX_28G_PCC2_SATAC_CFG(val)		((val << 20) & LYNX_28G_PCC2_SATAC_CFG_MASK)
#define LYNX_28G_PCC2_SATAD_CFG_MASK		GENMASK(18, 16)
#define LYNX_28G_PCC2_SATAD_CFG(val)		((val << 16) & LYNX_28G_PCC2_SATAD_CFG_MASK)

/* Protocol Configuration Register 8 */
#define LYNX_28G_PCC8				0x10A0
#define LYNX_28G_PCC8_SGMIIA_CFG_MASK		GENMASK(30, 28)
#define LYNX_28G_PCC8_SGMIIA_CFG(val)		((val << 28) & LYNX_28G_PCC8_SGMIIA_CFG_MASK)
#define LYNX_28G_PCC8_SGMIIB_CFG_MASK		GENMASK(26, 24)
#define LYNX_28G_PCC8_SGMIIB_CFG(val)		((val << 24) & LYNX_28G_PCC8_SGMIIB_CFG_MASK)
#define LYNX_28G_PCC8_SGMIIC_CFG_MASK		GENMASK(22, 20)
#define LYNX_28G_PCC8_SGMIIC_CFG(val)		((val << 20) & LYNX_28G_PCC8_SGMIIC_CFG_MASK)
#define LYNX_28G_PCC8_SGMIID_CFG_MASK		GENMASK(18, 16)
#define LYNX_28G_PCC8_SGMIID_CFG(val)		((val << 16) & LYNX_28G_PCC8_SGMIID_CFG_MASK)
#define LYNX_28G_PCC8_SGMIIE_CFG_MASK		GENMASK(14, 12)
#define LYNX_28G_PCC8_SGMIIE_CFG(val)		((val << 12) & LYNX_28G_PCC8_SGMIIE_CFG_MASK)
#define LYNX_28G_PCC8_SGMIIF_CFG_MASK		GENMASK(10, 8)
#define LYNX_28G_PCC8_SGMIIF_CFG(val)		((val << 8) & LYNX_28G_PCC8_SGMIIF_CFG_MASK)
#define LYNX_28G_PCC8_SGMIIG_CFG_MASK		GENMASK(6, 4)
#define LYNX_28G_PCC8_SGMIIG_CFG(val)		((val << 4) & LYNX_28G_PCC8_SGMIIG_CFG_MASK)
#define LYNX_28G_PCC8_SGMIIH_CFG_MASK		GENMASK(2, 0)
#define LYNX_28G_PCC8_SGMIIH_CFG(val)		((val << 0) & LYNX_28G_PCC8_SGMIIH_CFG_MASK)

/* Protocol Configuration Register C */
#define LYNX_28G_PCCC				0x10B0
#define LYNX_28G_PCCC_SXGMIIA_XFI		BIT(31)
#define LYNX_28G_PCCC_SXGMIIA_CFG_MASK		GENMASK(30, 28)
#define LYNX_28G_PCCC_SXGMIIA_CFG(val)		((val << 28) & LYNX_28G_PCCC_SXGMIIA_CFG_MASK)
#define LYNX_28G_PCCC_SXGMIIB_XFI		BIT(27)
#define LYNX_28G_PCCC_SXGMIIB_CFG_MASK		GENMASK(26, 24)
#define LYNX_28G_PCCC_SXGMIIB_CFG(val)		((val << 24) & LYNX_28G_PCCC_SXGMIIB_CFG_MASK)
#define LYNX_28G_PCCC_SXGMIIC_XFI		BIT(23)
#define LYNX_28G_PCCC_SXGMIIC_CFG_MASK		GENMASK(22, 20)
#define LYNX_28G_PCCC_SXGMIIC_CFG(val)		((val << 20) & LYNX_28G_PCCC_SXGMIIC_CFG_MASK)
#define LYNX_28G_PCCC_SXGMIID_XFI		BIT(19)
#define LYNX_28G_PCCC_SXGMIID_CFG_MASK		GENMASK(18, 16)
#define LYNX_28G_PCCC_SXGMIID_CFG(val)		((val << 16) & LYNX_28G_PCCC_SXGMIID_CFG_MASK)
#define LYNX_28G_PCCC_SXGMIIE_XFI		BIT(15)
#define LYNX_28G_PCCC_SXGMIIE_CFG_MASK		GENMASK(14, 12)
#define LYNX_28G_PCCC_SXGMIIE_CFG(val)		((val << 12) & LYNX_28G_PCCC_SXGMIIE_CFG_MASK)
#define LYNX_28G_PCCC_SXGMIIF_XFI		BIT(11)
#define LYNX_28G_PCCC_SXGMIIF_CFG_MASK		GENMASK(10, 8)
#define LYNX_28G_PCCC_SXGMIIF_CFG(val)		((val << 8) & LYNX_28G_PCCC_SXGMIIF_CFG_MASK)
#define LYNX_28G_PCCC_SXGMIIG_XFI		BIT(7)
#define LYNX_28G_PCCC_SXGMIIG_CFG_MASK		GENMASK(6, 4)
#define LYNX_28G_PCCC_SXGMIIG_CFG(val)		((val << 4) & LYNX_28G_PCCC_SXGMIIG_CFG_MASK)
#define LYNX_28G_PCCC_SXGMIIH_XFI		BIT(3)
#define LYNX_28G_PCCC_SXGMIIH_CFG_MASK		GENMASK(2, 0)
#define LYNX_28G_PCCC_SXGMIIH_CFG(val)		((val << 0) & LYNX_28G_PCCC_SXGMIIH_CFG_MASK)

/* Protocol Configuration Register D */
#define LYNX_28G_PCCD				0x10B4
#define LYNX_28G_PCCD_E25GA_CFG_MASK		GENMASK(30, 28)
#define LYNX_28G_PCCD_E25GA_CFG(val)		((val << 28) & LYNX_28G_PCCD_E25GA_CFG_MASK)
#define LYNX_28G_PCCD_E25GB_CFG_MASK		GENMASK(26, 24)
#define LYNX_28G_PCCD_E25GB_CFG(val)		((val << 24) & LYNX_28G_PCCD_E25GB_CFG_MASK)
#define LYNX_28G_PCCD_E25GC_CFG_MASK		GENMASK(22, 20)
#define LYNX_28G_PCCD_E25GC_CFG(val)		((val << 20) & LYNX_28G_PCCD_E25GC_CFG_MASK)
#define LYNX_28G_PCCD_E25GD_CFG_MASK		GENMASK(18, 16)
#define LYNX_28G_PCCD_E25GD_CFG(val)		((val << 16) & LYNX_28G_PCCD_E25GD_CFG_MASK)
#define LYNX_28G_PCCD_E25GE_CFG_MASK		GENMASK(14, 12)
#define LYNX_28G_PCCD_E25GE_CFG(val)		((val << 12) & LYNX_28G_PCCD_E25GE_CFG_MASK)
#define LYNX_28G_PCCD_E25GF_CFG_MASK		GENMASK(10, 8)
#define LYNX_28G_PCCD_E25GF_CFG(val)		((val << 8) & LYNX_28G_PCCD_E25GF_CFG_MASK)
#define LYNX_28G_PCCD_E25GG_CFG_MASK		GENMASK(6, 4)
#define LYNX_28G_PCCD_E25GG_CFG(val)		((val << 4) & LYNX_28G_PCCD_E25GG_CFG_MASK)
#define LYNX_28G_PCCD_E25GH_CFG_MASK		GENMASK(2, 0)
#define LYNX_28G_PCCD_E25GH_CFG(val)		((val << 0) & LYNX_28G_PCCD_E25GH_CFG_MASK)

/* Protocol Configuration Register E */
#define LYNX_28G_PCCE				0x10B8
#define LYNX_28G_PCCE_E40GA_CFG_MASK		GENMASK(30, 28)
#define LYNX_28G_PCCE_E40GA_CFG(val)		((val << 28) & LYNX_28G_PCCE_E40GA_CFG_MASK)
#define LYNX_28G_PCCE_E40GB_CFG_MASK		GENMASK(26, 24)
#define LYNX_28G_PCCE_E40GB_CFG(val)		((val << 24) & LYNX_28G_PCCE_E40GB_CFG_MASK)
#define LYNX_28G_PCCE_E50GA_CFG_MASK		GENMASK(22, 20)
#define LYNX_28G_PCCE_E50GA_CFG(val)		((val << 20) & LYNX_28G_PCCE_E50GA_CFG_MASK)
#define LYNX_28G_PCCE_E50GB_CFG_MASK		GENMASK(18, 16)
#define LYNX_28G_PCCE_E50GB_CFG(val)		((val << 16) & LYNX_28G_PCCE_E50GB_CFG_MASK)
#define LYNX_28G_PCCE_E100GA_CFG_MASK		GENMASK(14, 12)
#define LYNX_28G_PCCE_E100GA_CFG(val)		((val << 12) & LYNX_28G_PCCE_E100GA_CFG_MASK)
#define LYNX_28G_PCCE_E100GB_CFG_MASK		GENMASK(10, 8)
#define LYNX_28G_PCCE_E100GB_CFG(val)		((val << 8) & LYNX_28G_PCCE_E100GB_CFG_MASK)

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

/* Device Disable Register 1 */
#define DCFG_CCSR_DEVDISR1			0x0070
#define DCFG_CCSR_DEVDISR1_DCE			BIT(25)
#define DCFG_CCSR_DEVDISR1_SEC			BIT(22)
#define DCFG_CCSR_DEVDISR1_SATA4		BIT(19)
#define DCFG_CCSR_DEVDISR1_SATA3		BIT(18)
#define DCFG_CCSR_DEVDISR1_SATA2		BIT(17)
#define DCFG_CCSR_DEVDISR1_SATA1		BIT(16)
#define DCFG_CCSR_DEVDISR1_USB1			BIT(12)
#define DCFG_CCSR_DEVDISR1_ESDHC2		BIT(10)
#define DCFG_CCSR_DEVDISR1_QDMA			BIT(8)
#define DCFG_CCSR_DEVDISR1_ESDHC1		BIT(2)

/* Device Disable Register 2 */
#define DCFG_CCSR_DEVDISR2			0x0074
#define DCFG_CCSR_DEVDISR2_MAC18		BIT(17)
#define DCFG_CCSR_DEVDISR2_MAC17		BIT(16)
#define DCFG_CCSR_DEVDISR2_MAC16		BIT(15)
#define DCFG_CCSR_DEVDISR2_MAC15		BIT(14)
#define DCFG_CCSR_DEVDISR2_MAC14		BIT(13)
#define DCFG_CCSR_DEVDISR2_MAC13		BIT(12)
#define DCFG_CCSR_DEVDISR2_MAC12		BIT(11)
#define DCFG_CCSR_DEVDISR2_MAC11		BIT(10)
#define DCFG_CCSR_DEVDISR2_MAC10		BIT(9)
#define DCFG_CCSR_DEVDISR2_MAC9			BIT(8)
#define DCFG_CCSR_DEVDISR2_MAC8			BIT(7)
#define DCFG_CCSR_DEVDISR2_MAC7			BIT(6)
#define DCFG_CCSR_DEVDISR2_MAC6			BIT(5)
#define DCFG_CCSR_DEVDISR2_MAC5			BIT(4)
#define DCFG_CCSR_DEVDISR2_MAC4			BIT(3)
#define DCFG_CCSR_DEVDISR2_MAC3			BIT(2)
#define DCFG_CCSR_DEVDISR2_MAC2			BIT(1)
#define DCFG_CCSR_DEVDISR2_MAC1			BIT(0)

/*
 * evaluate DEVDISR registers to understand which interfaces are not
 * available, and disable their protocol converters.
 */
void board_disable_unused_proto_converters(void) {
	struct {
		const u32 __iomem *devdisr;
		const u32 devdisr_bit;
		u32 __iomem *const pcr;
		const u32 pcr_dis_mask;
		const u32 pcr_dis_val;
	} map[] = {
		{	/* dpmac1: 40G/50G/100G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC1,
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCE,
			.pcr_dis_mask = LYNX_28G_PCCE_E40GA_CFG_MASK | LYNX_28G_PCCE_E50GA_CFG_MASK | LYNX_28G_PCCE_E100GA_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCCE_E40GA_CFG(0) | LYNX_28G_PCCE_E50GA_CFG(0) | LYNX_28G_PCCE_E100GA_CFG(0),
		}, {	/* dpmac2: 40G/50G/100G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC2,
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCE,
			.pcr_dis_mask = LYNX_28G_PCCE_E40GB_CFG_MASK | LYNX_28G_PCCE_E50GB_CFG_MASK | LYNX_28G_PCCE_E100GB_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCCE_E40GB_CFG(0) | LYNX_28G_PCCE_E50GB_CFG(0) | LYNX_28G_PCCE_E100GB_CFG(0),
		}, {	/* dpmac3: 1G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC3,
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCC8,
			.pcr_dis_mask = LYNX_28G_PCC8_SGMIIH_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCC8_SGMIIH_CFG(0),
		}, {	/* dpmac3: 10G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC3,
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_dis_mask = LYNX_28G_PCCC_SXGMIIH_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCCC_SXGMIIH_CFG(0),
		}, {	/* dpmac3: 25G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC3,
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCD,
			.pcr_dis_mask = LYNX_28G_PCCD_E25GA_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCCD_E25GA_CFG(0),
		}, {	/* dpmac4: 1G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC4,
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCC8,
			.pcr_dis_mask = LYNX_28G_PCC8_SGMIIG_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCC8_SGMIIG_CFG(0),
		}, {	/* dpmac4: 10G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC4,
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_dis_mask = LYNX_28G_PCCC_SXGMIIG_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCCC_SXGMIIG_CFG(0),
		}, {	/* dpmac4: 25G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC4,
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCD,
			.pcr_dis_mask = LYNX_28G_PCCD_E25GB_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCCD_E25GB_CFG(0),
		}, {	/* dpmac5: 1G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC5,
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCC8,
			.pcr_dis_mask = LYNX_28G_PCC8_SGMIIF_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCC8_SGMIIF_CFG(0),
		}, {	/* dpmac5: 10G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC5,
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_dis_mask = LYNX_28G_PCCC_SXGMIIF_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCCC_SXGMIIF_CFG(0),
		}, {	/* dpmac5: 25G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC5,
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCD,
			.pcr_dis_mask = LYNX_28G_PCCD_E25GC_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCCD_E25GC_CFG(0),
		}, {	/* dpmac6: 1G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC6,
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCC8,
			.pcr_dis_mask = LYNX_28G_PCC8_SGMIIE_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCC8_SGMIIE_CFG(0),
		}, {	/* dpmac6: 10G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC6,
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_dis_mask = LYNX_28G_PCCC_SXGMIIE_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCCC_SXGMIIE_CFG(0),
		}, {	/* dpmac6: 25G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC6,
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCD,
			.pcr_dis_mask = LYNX_28G_PCCD_E25GD_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCCD_E25GD_CFG(0),
		}, {	/* dpmac7: 1G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC7,
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCC8,
			.pcr_dis_mask = LYNX_28G_PCC8_SGMIID_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCC8_SGMIID_CFG(0),
		}, {	/* dpmac7: 10G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC7,
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_dis_mask = LYNX_28G_PCCC_SXGMIID_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCCC_SXGMIID_CFG(0),
		}, {	/* dpmac7: 25G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC7,
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCD,
			.pcr_dis_mask = LYNX_28G_PCCD_E25GE_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCCD_E25GE_CFG(0),
		}, {	/* dpmac8: 1G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC8,
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCC8,
			.pcr_dis_mask = LYNX_28G_PCC8_SGMIIC_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCC8_SGMIIC_CFG(0),
		}, {	/* dpmac8: 10G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC8,
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_dis_mask = LYNX_28G_PCCC_SXGMIIC_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCCC_SXGMIIC_CFG(0),
		}, {	/* dpmac8: 25G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC8,
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCD,
			.pcr_dis_mask = LYNX_28G_PCCD_E25GF_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCCD_E25GF_CFG(0),
		}, {	/* dpmac9: 1G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC9,
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCC8,
			.pcr_dis_mask = LYNX_28G_PCC8_SGMIIB_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCC8_SGMIIB_CFG(0),
		}, {	/* dpmac9: 10G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC9,
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_dis_mask = LYNX_28G_PCCC_SXGMIIB_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCCC_SXGMIIB_CFG(0),
		}, {	/* dpmac9: 25G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC9,
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCD,
			.pcr_dis_mask = LYNX_28G_PCCD_E25GG_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCCD_E25GG_CFG(0),
		}, {	/* dpmac10: 1G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC10,
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCC8,
			.pcr_dis_mask = LYNX_28G_PCC8_SGMIIA_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCC8_SGMIIA_CFG(0),
		}, {	/* dpmac10: 10G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC10,
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_dis_mask = LYNX_28G_PCCC_SXGMIIA_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCCC_SXGMIIA_CFG(0),
		}, {	/* dpmac10: 25G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC10,
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCD,
			.pcr_dis_mask = LYNX_28G_PCCD_E25GH_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCCD_E25GH_CFG(0),
		}, {	/* dpmac11: 1G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC11,
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC8,
			.pcr_dis_mask = LYNX_28G_PCC8_SGMIIA_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCC8_SGMIIA_CFG(0),
		}, {	/* dpmac12: 1G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC12,
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC8,
			.pcr_dis_mask = LYNX_28G_PCC8_SGMIIB_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCC8_SGMIIB_CFG(0),
		}, {	/* dpmac17: 1G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC17,
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC8,
			.pcr_dis_mask = LYNX_28G_PCC8_SGMIIC_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCC8_SGMIIC_CFG(0),
		}, {	/* dpmac18: 1G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC18,
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC8,
			.pcr_dis_mask = LYNX_28G_PCC8_SGMIID_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCC8_SGMIID_CFG(0),
		}, {	/* dpmac15: 1G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC15,
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC8,
			.pcr_dis_mask = LYNX_28G_PCC8_SGMIIE_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCC8_SGMIIE_CFG(0),
		}, {	/* dpmac16: 1G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC16,
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC8,
			.pcr_dis_mask = LYNX_28G_PCC8_SGMIIF_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCC8_SGMIIF_CFG(0),
		}, {	/* dpmac13: 1G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC13,
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC8,
			.pcr_dis_mask = LYNX_28G_PCC8_SGMIIG_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCC8_SGMIIG_CFG(0),
		}, {	/* dpmac13: 10G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC13,
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCCC,
			.pcr_dis_mask = LYNX_28G_PCCC_SXGMIIG_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCCC_SXGMIIG_CFG(0),
		}, {	/* dpmac14: 1G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC14,
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC8,
			.pcr_dis_mask = LYNX_28G_PCC8_SGMIIH_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCC8_SGMIIH_CFG(0),
		}, {	/* dpmac14: 10G */
			.devdisr = DCFG_CCSR_BASE +  DCFG_CCSR_DEVDISR2,
			.devdisr_bit = DCFG_CCSR_DEVDISR2_MAC14,
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCCC,
			.pcr_dis_mask = LYNX_28G_PCCC_SXGMIIH_CFG_MASK,
			.pcr_dis_val = LYNX_28G_PCCC_SXGMIIH_CFG(0),
		},
	};

	for (int i = 0; i < ARRAY_SIZE(map); i++)
		if (*map[i].devdisr & map[i].devdisr_bit)
			*map[i].pcr &= ~map[i].pcr_dis_mask | map[i].pcr_dis_val;
}

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
		const u32 __iomem *const pcr;
		const u32 pcr_ena_mask;
		const u32 pcr_ena_val;
		const char *const mode;
		const unsigned int mac;
	} ports[] = {
		{
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIIA_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCC8_SGMIIA_CFG(1),
			.mode = "sgmii",
			.mac = DPMAC10,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIIB_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCC8_SGMIIB_CFG(1),
			.mode = "sgmii",
			.mac = DPMAC9,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIIC_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCC8_SGMIIC_CFG(1),
			.mode = "sgmii",
			.mac = DPMAC8,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIID_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCC8_SGMIID_CFG(1),
			.mode = "sgmii",
			.mac = DPMAC7,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIIE_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCC8_SGMIIE_CFG(1),
			.mode = "sgmii",
			.mac = DPMAC6,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIIF_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCC8_SGMIIF_CFG(1),
			.mode = "sgmii",
			.mac = DPMAC5,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIIG_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCC8_SGMIIG_CFG(1),
			.mode = "sgmii",
			.mac = DPMAC4,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIIH_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCC8_SGMIIH_CFG(1),
			.mode = "sgmii",
			.mac = DPMAC3,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIA_CFG_MASK | LYNX_28G_PCCC_SXGMIIA_XFI,
			.pcr_ena_val = LYNX_28G_PCCC_SXGMIIA_CFG(1) | LYNX_28G_PCCC_SXGMIIA_XFI,
			.mode = "xgmii",
			.mac = DPMAC10,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIB_CFG_MASK | LYNX_28G_PCCC_SXGMIIB_XFI,
			.pcr_ena_val = LYNX_28G_PCCC_SXGMIIB_CFG(1) | LYNX_28G_PCCC_SXGMIIB_XFI,
			.mode = "xgmii",
			.mac = DPMAC9,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIC_CFG_MASK | LYNX_28G_PCCC_SXGMIIC_XFI,
			.pcr_ena_val = LYNX_28G_PCCC_SXGMIIC_CFG(1) | LYNX_28G_PCCC_SXGMIIC_XFI,
			.mode = "xgmii",
			.mac = DPMAC8,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIID_CFG_MASK | LYNX_28G_PCCC_SXGMIID_XFI,
			.pcr_ena_val = LYNX_28G_PCCC_SXGMIID_CFG(1) | LYNX_28G_PCCC_SXGMIID_XFI,
			.mode = "xgmii",
			.mac = DPMAC7,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIE_CFG_MASK | LYNX_28G_PCCC_SXGMIIE_XFI,
			.pcr_ena_val = LYNX_28G_PCCC_SXGMIIE_CFG(1) | LYNX_28G_PCCC_SXGMIIE_XFI,
			.mode = "xgmii",
			.mac = DPMAC6,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIF_CFG_MASK | LYNX_28G_PCCC_SXGMIIF_XFI,
			.pcr_ena_val = LYNX_28G_PCCC_SXGMIIF_CFG(1) | LYNX_28G_PCCC_SXGMIIF_XFI,
			.mode = "xgmii",
			.mac = DPMAC5,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIG_CFG_MASK | LYNX_28G_PCCC_SXGMIIG_XFI,
			.pcr_ena_val = LYNX_28G_PCCC_SXGMIIG_CFG(1) | LYNX_28G_PCCC_SXGMIIG_XFI,
			.mode = "xgmii",
			.mac = DPMAC4,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIH_CFG_MASK | LYNX_28G_PCCC_SXGMIIH_XFI,
			.pcr_ena_val = LYNX_28G_PCCC_SXGMIIH_CFG(1) | LYNX_28G_PCCC_SXGMIIH_XFI,
			.mode = "xgmii",
			.mac = DPMAC3,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIA_CFG_MASK | LYNX_28G_PCCC_SXGMIIA_XFI,
			.pcr_ena_val = LYNX_28G_PCCC_SXGMIIA_CFG(1),
			.mode = "usxgmii",
			.mac = DPMAC10,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIB_CFG_MASK | LYNX_28G_PCCC_SXGMIIB_XFI,
			.pcr_ena_val = LYNX_28G_PCCC_SXGMIIB_CFG(1),
			.mode = "usxgmii",
			.mac = DPMAC9,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIC_CFG_MASK | LYNX_28G_PCCC_SXGMIIC_XFI,
			.pcr_ena_val = LYNX_28G_PCCC_SXGMIIC_CFG(1),
			.mode = "usxgmii",
			.mac = DPMAC8,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIID_CFG_MASK | LYNX_28G_PCCC_SXGMIID_XFI,
			.pcr_ena_val = LYNX_28G_PCCC_SXGMIID_CFG(1),
			.mode = "usxgmii",
			.mac = DPMAC7,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIE_CFG_MASK | LYNX_28G_PCCC_SXGMIIE_XFI,
			.pcr_ena_val = LYNX_28G_PCCC_SXGMIIE_CFG(1),
			.mode = "usxgmii",
			.mac = DPMAC6,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIF_CFG_MASK | LYNX_28G_PCCC_SXGMIIF_XFI,
			.pcr_ena_val = LYNX_28G_PCCC_SXGMIIF_CFG(1),
			.mode = "usxgmii",
			.mac = DPMAC5,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIG_CFG_MASK | LYNX_28G_PCCC_SXGMIIG_XFI,
			.pcr_ena_val = LYNX_28G_PCCC_SXGMIIG_CFG(1),
			.mode = "usxgmii",
			.mac = DPMAC4,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIH_CFG_MASK | LYNX_28G_PCCC_SXGMIIH_XFI,
			.pcr_ena_val = LYNX_28G_PCCC_SXGMIIH_CFG(1),
			.mode = "usxgmii",
			.mac = DPMAC3,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCD,
			.pcr_ena_mask = LYNX_28G_PCCD_E25GA_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCCD_E25GA_CFG(1),
			.mode = "25g-aui",
			.mac = DPMAC3,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCD,
			.pcr_ena_mask = LYNX_28G_PCCD_E25GB_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCCD_E25GB_CFG(1),
			.mode = "25g-aui",
			.mac = DPMAC4,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCD,
			.pcr_ena_mask = LYNX_28G_PCCD_E25GC_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCCD_E25GC_CFG(1),
			.mode = "25g-aui",
			.mac = DPMAC5,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCD,
			.pcr_ena_mask = LYNX_28G_PCCD_E25GD_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCCD_E25GD_CFG(1),
			.mode = "25g-aui",
			.mac = DPMAC6,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCD,
			.pcr_ena_mask = LYNX_28G_PCCD_E25GE_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCCD_E25GE_CFG(1),
			.mode = "25g-aui",
			.mac = DPMAC7,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCD,
			.pcr_ena_mask = LYNX_28G_PCCD_E25GF_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCCD_E25GF_CFG(1),
			.mode = "25g-aui",
			.mac = DPMAC8,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCD,
			.pcr_ena_mask = LYNX_28G_PCCD_E25GG_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCCD_E25GG_CFG(1),
			.mode = "25g-aui",
			.mac = DPMAC9,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCD,
			.pcr_ena_mask = LYNX_28G_PCCD_E25GH_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCCD_E25GH_CFG(1),
			.mode = "25g-aui",
			.mac = DPMAC10,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCE,
			.pcr_ena_mask = LYNX_28G_PCCE_E40GA_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCCE_E40GA_CFG(1),
			.mode = "xlaui4",
			.mac = DPMAC1,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCE,
			.pcr_ena_mask = LYNX_28G_PCCE_E40GB_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCCE_E40GB_CFG(1),
			.mode = "xlaui4",
			.mac = DPMAC2,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCE,
			.pcr_ena_mask = LYNX_28G_PCCE_E50GA_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCCE_E50GA_CFG(1),
			.mode = "caui2",
			.mac = DPMAC1,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCE,
			.pcr_ena_mask = LYNX_28G_PCCE_E50GB_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCCE_E50GB_CFG(1),
			.mode = "caui2",
			.mac = DPMAC2,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCE,
			.pcr_ena_mask = LYNX_28G_PCCE_E100GA_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCCE_E100GA_CFG(1),
			.mode = "caui4",
			.mac = DPMAC1,
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCCE,
			.pcr_ena_mask = LYNX_28G_PCCE_E100GB_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCCE_E100GB_CFG(1),
			.mode = "caui4",
			.mac = DPMAC2,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIIA_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCC8_SGMIIA_CFG(1),
			.mode = "sgmii",
			.mac = DPMAC11,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIIB_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCC8_SGMIIB_CFG(1),
			.mode = "sgmii",
			.mac = DPMAC12,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIIC_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCC8_SGMIIC_CFG(1),
			.mode = "sgmii",
			.mac = DPMAC17,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIID_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCC8_SGMIID_CFG(1),
			.mode = "sgmii",
			.mac = DPMAC18,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIIE_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCC8_SGMIIE_CFG(1),
			.mode = "sgmii",
			.mac = DPMAC15,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIIF_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCC8_SGMIIF_CFG(1),
			.mode = "sgmii",
			.mac = DPMAC16,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIIG_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCC8_SGMIIG_CFG(1),
			.mode = "sgmii",
			.mac = DPMAC13,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC8,
			.pcr_ena_mask = LYNX_28G_PCC8_SGMIIH_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCC8_SGMIIH_CFG(1),
			.mode = "sgmii",
			.mac = DPMAC14,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIG_CFG_MASK | LYNX_28G_PCCC_SXGMIIG_XFI,
			.pcr_ena_val = LYNX_28G_PCCC_SXGMIIG_CFG(1) | LYNX_28G_PCCC_SXGMIIG_XFI,
			.mode = "xgmii",
			.mac = DPMAC13,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIH_CFG_MASK | LYNX_28G_PCCC_SXGMIIH_XFI,
			.pcr_ena_val = LYNX_28G_PCCC_SXGMIIH_CFG(1) | LYNX_28G_PCCC_SXGMIIH_XFI,
			.mode = "xgmii",
			.mac = DPMAC14,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIG_CFG_MASK | LYNX_28G_PCCC_SXGMIIG_XFI,
			.pcr_ena_val = LYNX_28G_PCCC_SXGMIIG_CFG(1),
			.mode = "usxgmii",
			.mac = DPMAC13,
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCCC,
			.pcr_ena_mask = LYNX_28G_PCCC_SXGMIIH_CFG_MASK | LYNX_28G_PCCC_SXGMIIH_XFI,
			.pcr_ena_val = LYNX_28G_PCCC_SXGMIIH_CFG(1),
			.mode = "usxgmii",
			.mac = DPMAC14,
		}
	};

	for (int i = 0; i < ARRAY_SIZE(ports); i++) {
		if ((*ports[i].pcr & ports[i].pcr_ena_mask) == ports[i].pcr_ena_val) {
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
		const u32 __iomem *const pcr;
		const u32 pcr_ena_mask;
		const u32 pcr_ena_val;
		const char *const path;
	} ports[] = {
		{
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCC0,
			.pcr_ena_mask = LYNX_28G_PCC0_PEXA_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCC0_PEXA_CFG(1),
			.path = "/pcie@3400000",
		}, {
			.pcr = LYNX_28G_SDn_BASE(0) + LYNX_28G_PCC0,
			.pcr_ena_mask = LYNX_28G_PCC0_PEXB_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCC0_PEXB_CFG(1),
			.path = "/pcie@3500000",
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC0,
			.pcr_ena_mask = LYNX_28G_PCC0_PEXA_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCC0_PEXA_CFG(1),
			.path = "/pcie@3600000",
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC0,
			.pcr_ena_mask = LYNX_28G_PCC0_PEXB_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCC0_PEXB_CFG(1),
			.path = "/pcie@3700000",
		}, {
			.pcr = LYNX_28G_SDn_BASE(2) + LYNX_28G_PCC0,
			.pcr_ena_mask = LYNX_28G_PCC0_PEXA_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCC0_PEXA_CFG(1),
			.path = "/pcie@3800000",
		}, {
			.pcr = LYNX_28G_SDn_BASE(2) + LYNX_28G_PCC0,
			.pcr_ena_mask = LYNX_28G_PCC0_PEXB_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCC0_PEXB_CFG(1),
			.path = "/pcie@3900000",
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC2,
			.pcr_ena_mask = LYNX_28G_PCC2_SATAA_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCC2_SATAA_CFG(1),
			.path = "/sata@3200000",
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC2,
			.pcr_ena_mask = LYNX_28G_PCC2_SATAB_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCC2_SATAB_CFG(1),
			.path = "/sata@3210000",
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC2,
			.pcr_ena_mask = LYNX_28G_PCC2_SATAC_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCC2_SATAC_CFG(1),
			.path = "/sata@3220000",
		}, {
			.pcr = LYNX_28G_SDn_BASE(1) + LYNX_28G_PCC2,
			.pcr_ena_mask = LYNX_28G_PCC2_SATAD_CFG_MASK,
			.pcr_ena_val = LYNX_28G_PCC2_SATAD_CFG(1),
			.path = "/sata@3230000",
		},
	};

	for (int i = 0; i < ARRAY_SIZE(ports); i++) {
		const char *status = "disabled";
		if ((*ports[i].pcr & ports[i].pcr_ena_mask) == ports[i].pcr_ena_val)
			status = "okay";

		do_fixup_by_path_string(fdt, ports[i].path, "status", status);
	}
}

void board_fix_fdt_serdes_ports(void *fdt) {
	board_fix_fdt_pci_sata(fdt);
	board_fix_fdt_macs(fdt);
}

#endif /* CONFIG_OF_BOARD_FIXUP */
