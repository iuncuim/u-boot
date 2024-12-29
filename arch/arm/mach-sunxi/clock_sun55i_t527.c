#include <asm/io.h>
#include <asm/arch/cpu.h>
#include <asm/arch/clock.h>
#include <asm/arch/prcm.h>
#include <linux/delay.h>

#ifdef CONFIG_SPL_BUILD
void clock_init_safe(void)
{
	struct sunxi_ccm_reg *const ccm =
		(struct sunxi_ccm_reg *)SUNXI_CCM_BASE;
	struct sunxi_prcm_reg *const prcm =
		(struct sunxi_prcm_reg *)SUNXI_PRCM_BASE;

	setbits_le32(&prcm->sys_pwroff_gating, 0x200);
	udelay(1);
	setbits_le32(&prcm->res_cal_ctrl, 2);
	udelay(1);
	clrbits_le32(&prcm->res_cal_ctrl, 1);
	udelay(1);
	setbits_le32(&prcm->res_cal_ctrl, 1);
	udelay(1);

	clock_set_pll1(408000000);

	writel(CCM_PLL6_DEFAULT, &ccm->pll6_cfg);
	while (!(readl(&ccm->pll6_cfg) & CCM_PLL6_LOCK))
		;

	/* TODO: is this needed? */
	writel(CCM_PLL6_DEFAULT, &ccm->pll_periph1_cfg);
	while (!(readl(&ccm->pll_periph1_cfg) & CCM_PLL6_LOCK))
		;

	writel(CCM_PSI_AHB1_AHB2_DEFAULT, &ccm->psi_ahb1_ahb2_cfg);
	writel(CCM_APB1_DEFAULT, &ccm->apb1_cfg);

	writel(MBUS_RESET, &ccm->mbus_cfg);
	udelay(1);
	writel(MBUS_UPDATE | MBUS_CLK_SRC_DDRPLL | MBUS_CLK_M(4), &ccm->mbus_cfg);
}

void clock_init_uart(void)
{
	struct sunxi_ccm_reg *const ccm =
		(struct sunxi_ccm_reg *)SUNXI_CCM_BASE;

	/* uart clock source is apb2 */
	writel(APB2_CLK_SRC_OSC24M | APB2_CLK_RATE_M(1), &ccm->apb2_cfg);

	/* open the clock for uart */
	setbits_le32(&ccm->uart_gate_reset,
		     1 << (CONFIG_CONS_INDEX - 1));

	/* deassert uart reset */
	setbits_le32(&ccm->uart_gate_reset,
		     1 << (RESET_SHIFT + CONFIG_CONS_INDEX - 1));
}

static void clock_set_pll(u32 *reg, unsigned int n)
{
	u32 val;

	clrbits_le32(reg, CCM_PLL1_OUT_EN);

	val = readl(reg);
	val &= ~(CCM_PLL1_CTRL_P_MASK |
		 CCM_PLL1_CTRL_N_MASK |
		 CCM_PLL1_CTRL_M1_MASK);
	val |= CCM_PLL1_CTRL_P(1) |
	       CCM_PLL1_CTRL_N(n) |
	       CCM_PLL1_CTRL_M1(1);
	writel(val, reg);
	udelay(5);

	setbits_le32(reg, CCM_PLL1_CTRL_EN);
	setbits_le32(reg, CCM_PLL1_LDO_EN);
	udelay(5);
	setbits_le32(reg, CCM_PLL1_LOCK_EN);
	setbits_le32(reg, CCM_PLL1_UPDATE);

	while (!(readl(reg) & CCM_PLL1_LOCK)) {}
	udelay(20);

	setbits_le32(reg, CCM_PLL1_OUT_EN);
	clrbits_le32(reg, CCM_PLL1_LOCK_EN);
	setbits_le32(reg, CCM_PLL1_UPDATE);
}

void clock_set_pll1(unsigned int clk)
{
	struct cpu_pll_cfg * const cpc =
		(struct cpu_pll_cfg *)SUNXI_CPU_PLL_CFG_BASE;
	u32 n, val;

	/* switch to safe defaults (HOSC) */
	writel(CPU_CLK_SRC_HOSC | CPU_CLK_CTRL_P(0) | CPU_CLK_CTRL_N(4) |
	       CPU_CLK_CTRL_M1(2) | CPU_CLK_CTRL_M(2), &cpc->cpua_clk_cfg);
	writel(CPU_CLK_SRC_HOSC | CPU_CLK_CTRL_P(0) | CPU_CLK_CTRL_N(4) |
	       CPU_CLK_CTRL_M1(2) | CPU_CLK_CTRL_M(2), &cpc->cpub_clk_cfg);
	udelay(20);
	writel(CPU_CLK_SRC_HOSC | CPU_CLK_CTRL_P(0), &cpc->dsu_clk_cfg);
	udelay(20);

	/* Do not support clocks < 288MHz as they need factor P */
	if (clk < 288000000) clk = 288000000;

	/* clk = 24*n/p, p is ignored if clock is >288MHz */
	n = clk / 24000000;
	clock_set_pll(&cpc->cpu_l_pll, n);
	clock_set_pll(&cpc->cpu_b_pll, n);
	clock_set_pll(&cpc->cpu_dsu_pll, n);

	/* Switch CPU to PLL */
	val = readl(&cpc->cpua_clk_cfg);
	val &= ~CPU_CLK_SRC_HOSC;
	val |= CPU_CLK_SRC_CPUPLL;
	writel(val, &cpc->cpua_clk_cfg);
	udelay(20);

	val = readl(&cpc->cpub_clk_cfg);
	val &= ~CPU_CLK_SRC_HOSC;
	val |= CPU_CLK_SRC_CPUPLL;
	writel(val, &cpc->cpub_clk_cfg);
	udelay(20);

	val = readl(&cpc->dsu_clk_cfg);
	val &= ~CPU_CLK_SRC_HOSC;
	val |= CPU_CLK_SRC_CPUPLL;
	writel(val, &cpc->dsu_clk_cfg);
	udelay(20);
}

int clock_twi_onoff(int port, int state)
{
	struct sunxi_ccm_reg *const ccm =
		(struct sunxi_ccm_reg *)SUNXI_CCM_BASE;
	struct sunxi_prcm_reg *const prcm =
		(struct sunxi_prcm_reg *)SUNXI_PRCM_BASE;
	u32 value, *ptr;
	int shift;

	value = BIT(GATE_SHIFT) | BIT (RESET_SHIFT);

	if (port == 5) {
		shift = 0;
		ptr = &prcm->twi_gate_reset;
	} else {
		shift = port;
		ptr = &ccm->twi_gate_reset;
	}

	/* set the apb clock gate and reset for twi */
	if (state)
		setbits_le32(ptr, value << shift);
	else
		clrbits_le32(ptr, value << shift);

	return 0;
}
#endif /* CONFIG_SPL_BUILD */

/* PLL_PERIPH0 clock, used by the MMC driver */
unsigned int clock_get_pll6(void)
{
	struct sunxi_ccm_reg *const ccm =
		(struct sunxi_ccm_reg *)SUNXI_CCM_BASE;
	uint32_t rval = readl(&ccm->pll6_cfg);
	int n = ((rval & CCM_PLL6_CTRL_N_MASK) >> CCM_PLL6_CTRL_N_SHIFT) + 1;
	int div2 = ((rval & CCM_PLL6_CTRL_DIV2_MASK) >>
		    CCM_PLL6_CTRL_DIV2_SHIFT) + 1;
	int div1, m;

	if (IS_ENABLED(CONFIG_SUNXI_GEN_NCAT2)) {
		div1 = ((rval & CCM_PLL6_CTRL_P0_MASK) >>
			CCM_PLL6_CTRL_P0_SHIFT) + 1;
		m = 1;
	} else {
		div1 = ((rval & CCM_PLL6_CTRL_DIV1_MASK) >>
			CCM_PLL6_CTRL_DIV1_SHIFT) + 1;
		if (IS_ENABLED(CONFIG_MACH_SUN50I_H6))
			m = 4;
		else
			m = 2;
	}

	return 24000000U * n / m / div1 / div2;
}
