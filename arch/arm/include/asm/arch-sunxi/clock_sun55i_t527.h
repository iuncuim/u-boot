/*
 * Allwinner T527 clock register definitions
 *
 * (C) Copyright 2024 Jernej Skrabec <jernej.skrabec@gmail.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _SUNXI_CLOCK_SUN55I_T527_H
#define _SUNXI_CLOCK_SUN55I_T527_H

#ifndef __ASSEMBLY__
#include <linux/bitops.h>
#endif

struct sunxi_ccm_reg {
	u8 reserved_0x000[16];
	u32 pll5_cfg;		/* 0x010 pll5 (ddr) control */
	u8 reserved_0x014[12];
	u32 pll6_cfg;		/* 0x020 pll6 (periph0) control */
	u8 reserved_0x020[4];
	u32 pll_periph1_cfg;	/* 0x028 pll periph1 control */
	u8 reserved_0x028[4];
	u32 pll7_cfg;		/* 0x030 pll7 (gpu) control */
	u8 reserved_0x034[12];
	u32 pll3_cfg;		/* 0x040 pll3 (video0) control */
	u8 reserved_0x044[4];
	u32 pll_video1_cfg;	/* 0x048 pll video1 control */
	u8 reserved_0x04c[4];
	u32 pll_video2_cfg;	/* 0x050 pll video2 control */
	u8 reserved_0x054[4];
	u32 pll4_cfg;		/* 0x058 pll4 (ve) control */
	u8 reserved_0x05c[12];
	u32 pll_video3_cfg;	/* 0x068 pll video3 control */
	u8 reserved_0x06c[12];
	u32 pll2_cfg;		/* 0x078 pll2 (audio) control */
	u8 reserved_0x07c[148];
	u32 pll5_pat0;		/* 0x110 pll5 (ddr) pattern0 */
	u32 pll5_pat1;		/* 0x114 pll5 (ddr) pattern1 */
	u8 reserved_0x118[8];
	u32 pll_periph0_pat0;	/* 0x120 pll periph0 pattern0 */
	u32 pll_periph0_pat1;	/* 0x124 pll periph0 pattern1 */
	u32 pll_periph1_pat0;	/* 0x128 pll periph1 pattern0 */
	u32 pll_periph1_pat1;	/* 0x12c pll periph1 pattern1 */
	u32 pll7_pat0;		/* 0x130 pll7 (gpu) pattern0 */
	u32 pll7_pat1;		/* 0x134 pll7 (gpu) pattern1 */
	u8 reserved_0x138[8];
	u32 pll3_pat0;		/* 0x140 pll3 (video0) pattern0 */
	u32 pll3_pat1;		/* 0x144 pll3 (video0) pattern1 */
	u32 pll_video1_pat0;	/* 0x148 pll video0 pattern0 */
	u32 pll_video1_pat1;	/* 0x14c pll video0 pattern1 */
	u32 pll_video2_pat0;	/* 0x150 pll video1 pattern0 */
	u32 pll_video2_pat1;	/* 0x154 pll video1 pattern1 */
	u32 pll4_pat0;		/* 0x158 pll4 (ve) pattern0 */
	u32 pll4_pat1;		/* 0x15c pll4 (ve) pattern1 */
	u8 reserved_0x160[8];
	u32 pll_video3_pat0;	/* 0x168 pll video2 pattern0 */
	u32 pll_video3_pat1;	/* 0x16c pll video2 pattern1 */
	u8 reserved_0x170[8];
	u32 pll2_pat0;		/* 0x178 pll2 (audio) pattern0 */
	u32 pll2_pat1;		/* 0x17c pll2 (audio) pattern1 */
	u8 reserved_0x180[400];
	u32 pll5_bias;		/* 0x310 pll5 (ddr) bias */
	u8 reserved_0x314[12];
	u32 pll6_bias;		/* 0x320 pll6 (periph0) bias */
	u8 reserved_0x324[4];
	u32 pll_periph1_bias;	/* 0x328 pll periph1 bias */
	u8 reserved_0x32c[4];
	u32 pll7_bias;		/* 0x330 pll7 (gpu) bias */
	u8 reserved_0x334[12];
	u32 pll3_bias;		/* 0x340 pll3 (video0) bias */
	u8 reserved_0x344[4];
	u32 pll_video1_bias;	/* 0x348 pll video1 bias */
	u8 reserved_0x34c[4];
	u32 pll_video2_bias;	/* 0x350 pll video2 bias */
	u8 reserved_0x354[4];
	u32 pll4_bias;		/* 0x358 pll4 (ve) bias */
	u8 reserved_0x35c[12];
	u32 pll_video3_bias;	/* 0x368 pll video3 bias */
	u8 reserved_0x36c[12];
	u32 pll2_bias;		/* 0x378 pll2 (audio) bias */
	u8 reserved_0x37c[404];
	u32 psi_ahb1_ahb2_cfg;	/* 0x510 PSI/AHB1/AHB2 clock control */
	u8 reserved_0x514[12];
	u32 apb1_cfg;		/* 0x520 APB1 clock control */
	u32 apb2_cfg;		/* 0x524 APB2 clock control */
	u8 reserved_0x528[24];
	u32 mbus_cfg;		/* 0x540 MBUS clock control */
	u8 reserved_0x544[8];
	u32 nsi_gate_reset;	/* 0x54c NSI gate/reset control */
	u32 gic_cfg;		/* 0x550 GIC clock control */
	u8 reserved_0x554[172];
	u32 de_clk_cfg;		/* 0x600 DE clock control */
	u8 reserved_0x604[8];
	u32 de_gate_reset;	/* 0x60c DE gate/reset control */
	u8 reserved_0x610[16];
	u32 di_clk_cfg;		/* 0x620 DI clock control */
	u8 reserved_0x024[8];
	u32 di_gate_reset;	/* 0x62c DI gate/reset control */
	u8 reserved_0x630[64];
	u32 gpu_clk_cfg;	/* 0x670 GPU clock control */
	u8 reserved_0x674[8];
	u32 gpu_gate_reset;	/* 0x67c GPU gate/reset control */
	u32 ce_clk_cfg;		/* 0x680 CE clock control */
	u8 reserved_0x684[8];
	u32 ce_gate_reset;	/* 0x68c CE gate/reset control */
	u32 ve_clk_cfg;		/* 0x690 VE clock control */
	u8 reserved_0x694[8];
	u32 ve_gate_reset;	/* 0x69c VE gate/reset control */
	u8 reserved_0x6a0[108];
	u32 dma_gate_reset;	/* 0x70c DMA gate/reset control */
	u8 reserved_0x710[12];
	u32 msgbox_gate_reset;	/* 0x71c Message Box gate/reset control */
	u8 reserved_0x720[12];
	u32 spinlock_gate_reset;/* 0x72c Spinlock gate/reset control */
	u32 timer0_cfg;		/* 0x730 Timer0 clock control */
	u32 timer1_cfg;		/* 0x734 Timer1 clock control */
	u32 timer2_cfg;		/* 0x738 Timer2 clock control */
	u32 timer3_cfg;		/* 0x73c Timer3 clock control */
	u32 timer4_cfg;		/* 0x740 Timer4 clock control */
	u32 timer5_cfg;		/* 0x744 Timer5 clock control */
	u8 reserved_0x748[4];
	u32 timer_gate_reset;	/* 0x74c Timer gate/reset control */
	u8 reserved_0x750[60];
	u32 dbgsys_gate_reset;	/* 0x78c Debugging system gate/reset control */
	u8 reserved_0x790[28];
	u32 pwm_gate_reset;	/* 0x7ac PWM gate/reset control */
	u32 iommu_cfg;		/* 0x7b0 IOMMU clock control */
	u8 reserved_0x7b4[8];
	u32 iommu_gate_reset;	/* 0x7bc IOMMU gate/reset control */
	u8 reserved_0x7c0[64];
	u32 dram_clk_cfg;	/* 0x800 DRAM clock control */
	u32 mbus_gate;		/* 0x804 MBUS gate control */
	u8 reserved_0x808[4];
	u32 dram_gate_reset;	/* 0x80c DRAM gate/reset control */
	u32 nand0_clk_cfg;	/* 0x810 NAND0 clock control */
	u32 nand1_clk_cfg;	/* 0x814 NAND1 clock control */
	u8 reserved_0x818[20];
	u32 nand_gate_reset;	/* 0x82c NAND gate/reset control */
	u32 sd0_clk_cfg;	/* 0x830 MMC0 clock control */
	u32 sd1_clk_cfg;	/* 0x834 MMC1 clock control */
	u32 sd2_clk_cfg;	/* 0x838 MMC2 clock control */
	u8 reserved_0x83c[16];
	u32 sd_gate_reset;	/* 0x84c MMC gate/reset control */
	u8 reserved_0x850[60];
	u32 sysdap_gate_reset;	/* 0x88c MMC gate/reset control */
	u8 reserved_0x890[124];
	u32 uart_gate_reset;	/* 0x90c UART gate/reset control */
	u8 reserved_0x910[12];
	u32 twi_gate_reset;	/* 0x91c I2C gate/reset control */
	u8 reserved_0x920[32];
	u32 spi0_clk_cfg;	/* 0x940 SPI0 clock control */
	u32 spi1_clk_cfg;	/* 0x944 SPI1 clock control */
	u32 spi2_clk_cfg;	/* 0x948 SPI2 clock control */
	u8 reserved_0x94c[4];
	u32 spifc_clk_cfg;	/* 0x950 SPIFC clock control */
	u8 reserved_0x954[24];
	u32 spi_gate_reset;	/* 0x96c SPI gate/reset control */
	u32 emac_25m_cfg;	/* 0x970 EMAC 25M clock control */
	u8 reserved_0x974[8];
	u32 emac_gate_reset;	/* 0x97c EMAC gate/reset control */
	u8 reserved_0x980[64];
	u32 irtx_clk_cfg;	/* 0x9c0 IR TX clock control */
	u8 reserved_0x9c4[8];
	u32 irtx_gate_reset;	/* 0x9cc IR TX gate/reset control */
	u8 reserved_0x9d0[44];
	u32 ths_gate_reset;	/* 0x9fc THS gate/reset control */
	u8 reserved_0xa00[112];
	u32 usb0_clk_cfg;	/* 0xa70 USB0(OTG) clock control */
	u32 usb1_clk_cfg;	/* 0xa74 USB1(XHCI) clock control */
	u8 reserved_0xa78[8];
	u32 usb2_ref_cfg;	/* 0xa80 USB2_REF clock control */
	u32 usb3_pcie_ref_cfg;	/* 0xa84 USB3_PCIE_REF clock control */
	u32 usb3_suspend_cfg;	/* 0xa88 USB3_SUSPEND clock control */
	u32 usb_gate_reset;	/* 0xa8c USB gate/reset control */
	// u8 reserved_0xa90[32];
	// u32 pcie_ref_clk_cfg;	/* 0xab0 PCIE REF clock control */
	// u32 pcie_axi_clk_cfg;	/* 0xab4 PCIE AXI clock control */
	// u32 pcie_aux_clk_cfg;	/* 0xab8 PCIE AUX clock control */
	// u32 pcie_gate_reset;	/* 0xabc PCIE gate/reset control */
	// u8 reserved_0xac0[64];
	// u32 hdmi_clk_cfg;	/* 0xb00 HDMI clock control */
	// u32 hdmi_slow_clk_cfg;	/* 0xb04 HDMI slow clock control */
	// u8 reserved_0xb08[8];
	// u32 hdmi_cec_clk_cfg;	/* 0xb10 HDMI CEC clock control */
	// u8 reserved_0xb14[8];
	// u32 hdmi_gate_reset;	/* 0xb1c HDMI gate/reset control */
	// u8 reserved_0xb20[60];
	// u32 tcon_top_gate_reset;/* 0xb5c TCON TOP gate/reset control */
	// u32 tcon_lcd0_clk_cfg;	/* 0xb60 TCON LCD0 clock control */
	// u8 reserved_0xb64[24];
	// u32 tcon_lcd_gate_reset;/* 0xb7c TCON LCD gate/reset control */
	// u32 tcon_tv0_clk_cfg;	/* 0xb80 TCON TV0 clock control */
	// u8 reserved_0xb84[24];
	// u32 tcon_tv_gate_reset;	/* 0xb9c TCON TV gate/reset control */
	// u8 reserved_0xba0[96];
	// u32 csi_misc_clk_cfg;	/* 0xc00 CSI MISC clock control */
	// u32 csi_top_clk_cfg;	/* 0xc04 CSI TOP clock control */
	// u32 csi_mclk_cfg;	/* 0xc08 CSI Master clock control */
	// u8 reserved_0xc0c[32];
	// u32 csi_gate_reset;	/* 0xc2c CSI gate/reset control */
	// u8 reserved_0xc30[16];
	// u32 hdcp_clk_cfg;	/* 0xc40 HDCP clock control */
	// u8 reserved_0xc44[8];
	// u32 hdcp_gate_reset;	/* 0xc4c HDCP gate/reset control */
	// u8 reserved_0xc50[688];
	// u32 ccu_sec_switch;	/* 0xf00 CCU security switch */
	// u32 pll_lock_dbg_ctrl;	/* 0xf04 PLL lock debugging control */
};
check_member(sunxi_ccm_reg, usb_gate_reset, 0xa8c);

struct cpu_pll_cfg  {
	u8 reserved0[4];
	u32 cpu_l_pll;
	u32 cpu_dsu_pll;
	u32 cpu_b_pll;
	u32 cpu_l_pll_pattern0;
	u32 cpu_l_pll_pattern1;
	u32 cpu_dsu_pll_pattern0;
	u32 cpu_dsu_pll_pattern1;
	u32 cpu_b_pll_pattern0;
	u32 cpu_b_pll_pattern1;
	u8 reserved1[4];
	u32 cpu_l_pll_bias;
	u32 cpu_dsu_pll_bias;
	u32 cpu_b_pll_bias;
	u8 reserved2[4];
	u32 cpu_l_pll_tunning0;
	u32 cpu_l_pll_tunning1;
	u32 cpu_dsu_pll_tunning0;
	u32 cpu_dsu_pll_tunning1;
	u32 cpu_b_pll_tunning0;
	u32 cpu_b_pll_tunning1;
	u32 cpu_l_pll_ssc;
	u32 cpu_dsu_pll_ssc;
	u32 cpu_b_pll_ssc;
	u32 cpua_clk_cfg;
	u32 cpub_clk_cfg;
	u32 cpu_gating;
	u32 dsu_clk_cfg;
	u32 pll_test_cfg;
};
check_member(cpu_pll_cfg, pll_test_cfg, 0x70);

/* pll1 bit field */
#define CCM_PLL1_CTRL_EN		BIT(31)
#define CCM_PLL1_LDO_EN			BIT(30)
#define CCM_PLL1_LOCK_EN		BIT(29)
#define CCM_PLL1_LOCK			BIT(28)
#define CCM_PLL1_OUT_EN			BIT(27)
#define CCM_PLL1_UPDATE			BIT(26)
#define CCM_PLL1_CTRL_M0(m)		(((m) - 1) << 20)
#define CCM_PLL1_CTRL_P(p)		(((p) - 1) << 16)
#define CCM_PLL1_CTRL_P_MASK		(0x0f << 16)
#define CCM_PLL1_CTRL_N(n)		((n) << 8)
#define CCM_PLL1_CTRL_N_MASK		(0xff << 8)
#define CCM_PLL1_CTRL_M1(m)		((m) - 1)
#define CCM_PLL1_CTRL_M1_MASK		0x0f

/* cpu clock config bit field */
#define CPU_CLK_SRC_HOSC		(0 << 24)
#define CPU_CLK_SRC_CPUPLL		(3 << 24)
#define CPU_CLK_CTRL_P(p)		((p) << 16)
#define CPU_CLK_CTRL_N(n)		(((n) - 1) << 8)
#define CPU_CLK_CTRL_M1(m)		(((m) - 1) << 2)
#define CPU_CLK_CTRL_M(m)		((m) - 1)

/* pll5 bit field */
#define CCM_PLL5_CTRL_EN		BIT(31)
#define CCM_PLL5_LDO_EN			BIT(30)
#define CCM_PLL5_LOCK_EN		BIT(29)
#define CCM_PLL5_LOCK			BIT(28)
#define CCM_PLL5_OUT_EN			BIT(27)
#define CCM_PLL5_CTRL_N(n)		(((n) - 1) << 8)
#define CCM_PLL5_CTRL_DIV1(div1)	((div1) << 0)
#define CCM_PLL5_CTRL_DIV2(div0)	((div0) << 1)

/* pll6 bit field */
#define CCM_PLL6_CTRL_EN		BIT(31)
#define CCM_PLL6_LDO_EN			BIT(30)
#define CCM_PLL6_LOCK_EN		BIT(29)
#define CCM_PLL6_LOCK			BIT(28)
#define CCM_PLL6_CTRL_P0_SHIFT		16
#define CCM_PLL6_CTRL_P0_MASK		(0x7 << CCM_PLL6_CTRL_P0_SHIFT)
#define CCM_PLL6_CTRL_N_SHIFT		8
#define CCM_PLL6_CTRL_N_MASK		(0xff << CCM_PLL6_CTRL_N_SHIFT)
#define CCM_PLL6_CTRL_DIV1_SHIFT	0
#define CCM_PLL6_CTRL_DIV1_MASK		(0x1 << CCM_PLL6_CTRL_DIV1_SHIFT)
#define CCM_PLL6_CTRL_DIV2_SHIFT	1
#define CCM_PLL6_CTRL_DIV2_MASK		(0x1 << CCM_PLL6_CTRL_DIV2_SHIFT)

#define CCM_PLL6_DEFAULT		0xe8216310

/* psi_ahb1_ahb2 bit field */
#define CCM_PSI_AHB1_AHB2_DEFAULT	0x03000002

/* apb1 bit field */
#define CCM_APB1_DEFAULT		0x03000005

/* apb2 bit field */
#define APB2_CLK_SRC_OSC24M		(0x0 << 24)
#define APB2_CLK_SRC_OSC32K		(0x1 << 24)
#define APB2_CLK_SRC_OSC16RC		(0x2 << 24)
#define APB2_CLK_SRC_PLL6		(0x3 << 24)
#define APB2_CLK_SRC_MASK		(0x3 << 24)
#define APB2_CLK_RATE_M(m)		(((m)-1) << 0)
#define APB2_CLK_RATE_M_MASK            (0x1f << 0)

/* MBUS clock bit field */
#define MBUS_ENABLE			BIT(31)
#define MBUS_RESET			BIT(30)
#define MBUS_UPDATE			BIT(27)
#define MBUS_CLK_SRC_MASK		GENMASK(25, 24)
#define MBUS_CLK_SRC_DDRPLL		(0 << 24)
#define MBUS_CLK_SRC_PLL6X2		(1 << 24)
#define MBUS_CLK_SRC_PLL5		(2 << 24)
#define MBUS_CLK_SRC_PLL6X4		(3 << 24)
#define MBUS_CLK_M(m)			(((m)-1) << 0)

/* clock enable shift */
#define ENABLE_SHIFT			(31)

/* Module gate/reset shift */
#define RESET_SHIFT			(16)
#define GATE_SHIFT			(0)

/* DRAM clock bit field */
#define DRAM_CLK_ENABLE			BIT(31)
#define DRAM_CLK_UPDATE			BIT(27)
#define DRAM_CLK_SRC_MASK		GENMASK(26, 24)
#define DRAM_CLK_SRC_PLL5		(0 << 24)
#define DRAM_CLK_M_MASK			(0x1f)
#define DRAM_CLK_M(m)			(((m)-1) << 0)

/* MMC clock bit field */
#define CCM_MMC_CTRL_M(x)		((x) - 1)
#define CCM_MMC_CTRL_N(x)		((x) << 8)
#define CCM_MMC_CTRL_OSCM24		(0x0 << 24)
#define CCM_MMC_CTRL_PLL6		(0x1 << 24)
#define CCM_MMC_CTRL_PLL_PERIPH2X2	(0x2 << 24)
#define CCM_MMC_CTRL_ENABLE		(0x1 << 31)
/* H6 doesn't have these delays */
#define CCM_MMC_CTRL_OCLK_DLY(a)	((void) (a), 0)
#define CCM_MMC_CTRL_SCLK_DLY(a)	((void) (a), 0)

#ifndef __ASSEMBLY__
void clock_set_pll1(unsigned int hz);
unsigned int clock_get_pll6(void);
#endif

#endif /* _SUNXI_CLOCK_SUN50I_H6_H */
