// SPDX-License-Identifier: GPL-2.0+
/*
 * AXP858 driver based on AXP221 driver
 *
 *
 * (C) Copyright 2015 Vishnu Patekar <vishnuptekar0510@gmail.com>
 *
 * Based on axp221.c
 * (C) Copyright 2014 Hans de Goede <hdegoede@redhat.com>
 * (C) Copyright 2013 Oliver Schinagl <oliver@schinagl.nl>
 */

#include <common.h>
#include <command.h>
#include <errno.h>
#include <asm/arch/gpio.h>
#include <asm/arch/pmic_bus.h>
#include <axp_pmic.h>

static u8 axp858_mvolt_to_cfg(int mvolt, int min, int max, int div)
{
	if (mvolt < min)
		mvolt = min;
	else if (mvolt > max)
		mvolt = max;

	return  (mvolt - min) / div;
}

int axp_set_dcdc1(unsigned int mvolt)
{
	int ret;
	u8 cfg = axp858_mvolt_to_cfg(mvolt, 1500, 3400, 100);

	if (mvolt == 0)
		return pmic_bus_clrbits(AXP858_OUTPUT_CTRL1,
					AXP858_OUTPUT_CTRL1_DCDC1_EN);

	ret = pmic_bus_write(AXP858_DCDC1_CTRL, cfg);
	if (ret)
		return ret;

	return pmic_bus_setbits(AXP858_OUTPUT_CTRL1,
				AXP858_OUTPUT_CTRL1_DCDC1_EN);
}

int axp_set_dcdc2(unsigned int mvolt)
{
	int ret;
	u8 cfg;

	if (mvolt >= 1220)
		//cfg = 70 + axp858_mvolt_to_cfg(mvolt, 1220, 1540, 20);
		cfg = 70 + axp858_mvolt_to_cfg(mvolt, 1220, 1300, 20);
	else
		cfg = axp858_mvolt_to_cfg(mvolt, 500, 1200, 10);

	if (mvolt == 0)
		return pmic_bus_clrbits(AXP858_OUTPUT_CTRL1,
					AXP858_OUTPUT_CTRL1_DCDC2_EN);

	ret = pmic_bus_write(AXP858_DCDC2_CTRL, cfg);
	if (ret)
		return ret;

	return pmic_bus_setbits(AXP858_OUTPUT_CTRL1,
				AXP858_OUTPUT_CTRL1_DCDC2_EN);
}

int axp_set_dcdc3(unsigned int mvolt)
{
	int ret;
	u8 cfg;

	if (mvolt >= 1220)
		//cfg = 70 + axp858_mvolt_to_cfg(mvolt, 1220, 1540, 20);
		cfg = 70 + axp858_mvolt_to_cfg(mvolt, 1220, 1300, 20);
	else
		cfg = axp858_mvolt_to_cfg(mvolt, 500, 1200, 10);

	if (mvolt == 0)
		return pmic_bus_clrbits(AXP858_OUTPUT_CTRL1,
					AXP858_OUTPUT_CTRL1_DCDC3_EN);

	ret = pmic_bus_write(AXP858_DCDC3_CTRL, cfg);
	if (ret)
		return ret;

	return pmic_bus_setbits(AXP858_OUTPUT_CTRL1,
				AXP858_OUTPUT_CTRL1_DCDC3_EN);
}

int axp_set_dcdc5(unsigned int mvolt)
{
	int ret;
	u8 cfg;

	if (mvolt >= 1140)
		cfg = 32 + axp858_mvolt_to_cfg(mvolt, 1140, 1840, 20);
	else
		cfg = axp858_mvolt_to_cfg(mvolt, 800, 1120, 10);

	if (mvolt == 0)
		return pmic_bus_clrbits(AXP858_OUTPUT_CTRL1,
					AXP858_OUTPUT_CTRL1_DCDC5_EN);

	ret = pmic_bus_write(AXP858_DCDC5_CTRL, cfg);
	if (ret)
		return ret;

	return pmic_bus_setbits(AXP858_OUTPUT_CTRL1,
				AXP858_OUTPUT_CTRL1_DCDC5_EN);
}

int axp_set_aldo(int aldo_num, unsigned int mvolt)
{
	int ret;
	u8 cfg;

	if (aldo_num < 1 || aldo_num > 3)
		return -EINVAL;

	if (mvolt == 0)
		return pmic_bus_clrbits(AXP858_OUTPUT_CTRL2,
				AXP858_OUTPUT_CTRL2_ALDO1_EN << (aldo_num - 1));

	cfg = axp858_mvolt_to_cfg(mvolt, 700, 3300, 100);
	ret = pmic_bus_write(AXP858_ALDO1_CTRL + (aldo_num - 1), cfg);
	if (ret)
		return ret;

	return pmic_bus_setbits(AXP858_OUTPUT_CTRL2,
				AXP858_OUTPUT_CTRL2_ALDO1_EN << (aldo_num - 1));
}

/* TODO: re-work other AXP drivers to consolidate ALDO functions. */
int axp_set_aldo1(unsigned int mvolt)
{
	return axp_set_aldo(1, mvolt);
}

int axp_set_aldo2(unsigned int mvolt)
{
	return axp_set_aldo(2, mvolt);
}

int axp_set_aldo3(unsigned int mvolt)
{
	return axp_set_aldo(3, mvolt);
}

// int axp_set_dldo(int dldo_num, unsigned int mvolt)
// {
// 	int ret;
// 	u8 cfg;

// 	if (dldo_num < 1 || dldo_num > 4)
// 		return -EINVAL;

// 	if (mvolt == 0)
// 		return pmic_bus_clrbits(AXP858_OUTPUT_CTRL2,
// 				AXP858_OUTPUT_CTRL2_DLDO1_EN << (dldo_num - 1));

// 	cfg = axp858_mvolt_to_cfg(mvolt, 700, 3300, 100);
// 	if (dldo_num == 2 && mvolt > 3300)
// 		cfg += 1 + axp858_mvolt_to_cfg(mvolt, 3400, 4200, 200);
// 	ret = pmic_bus_write(AXP858_DLDO1_CTRL + (dldo_num - 1), cfg);
// 	if (ret)
// 		return ret;

// 	return pmic_bus_setbits(AXP858_OUTPUT_CTRL2,
// 				AXP858_OUTPUT_CTRL2_DLDO1_EN << (dldo_num - 1));
// }

// int axp_set_eldo(int eldo_num, unsigned int mvolt)
// {
// 	int ret;
// 	u8 cfg;

// 	if (eldo_num < 1 || eldo_num > 3)
// 		return -EINVAL;

// 	if (mvolt == 0)
// 		return pmic_bus_clrbits(AXP858_OUTPUT_CTRL2,
// 				AXP858_OUTPUT_CTRL2_ELDO1_EN << (eldo_num - 1));

// 	cfg = axp858_mvolt_to_cfg(mvolt, 700, 1900, 50);
// 	ret = pmic_bus_write(AXP858_ELDO1_CTRL + (eldo_num - 1), cfg);
// 	if (ret)
// 		return ret;

// 	return pmic_bus_setbits(AXP858_OUTPUT_CTRL2,
// 				AXP858_OUTPUT_CTRL2_ELDO1_EN << (eldo_num - 1));
// }

// int axp_set_fldo(int fldo_num, unsigned int mvolt)
// {
// 	int ret;
// 	u8 cfg;

// 	if (fldo_num < 1 || fldo_num > 3)
// 		return -EINVAL;

// 	if (mvolt == 0)
// 		return pmic_bus_clrbits(AXP858_OUTPUT_CTRL3,
// 				AXP858_OUTPUT_CTRL3_FLDO1_EN << (fldo_num - 1));

// 	if (fldo_num < 3) {
// 		cfg = axp858_mvolt_to_cfg(mvolt, 700, 1450, 50);
// 		ret = pmic_bus_write(AXP858_FLDO1_CTRL + (fldo_num - 1), cfg);
// 	} else {
// 		/*
// 		 * Special case for FLDO3, which is DCDC5 / 2 or FLDOIN / 2
// 		 * Since FLDOIN is unknown, test against DCDC5.
// 		 */
// 		if (mvolt * 2 == CONFIG_AXP_DCDC5_VOLT)
// 			ret = pmic_bus_clrbits(AXP858_FLDO2_3_CTRL,
// 					       AXP858_FLDO2_3_CTRL_FLDO3_VOL);
// 		else
// 			ret = pmic_bus_setbits(AXP858_FLDO2_3_CTRL,
// 					       AXP858_FLDO2_3_CTRL_FLDO3_VOL);
// 	}
// 	if (ret)
// 		return ret;

// 	return pmic_bus_setbits(AXP858_OUTPUT_CTRL3,
// 				AXP858_OUTPUT_CTRL3_FLDO1_EN << (fldo_num - 1));
// }

int axp_set_sw(bool on)
{
	if (on)
		return pmic_bus_setbits(AXP858_OUTPUT_CTRL3,
					AXP858_OUTPUT_CTRL3_SW_EN);

	return pmic_bus_clrbits(AXP858_OUTPUT_CTRL3,
				AXP858_OUTPUT_CTRL3_SW_EN);
}

static int pmu_axp858_ap_reset_enable(void)
{
	u8 reg_value;

	if (pmic_bus_read(AXP858_SHUTDOWN,  &reg_value))
		return -1;

	reg_value |= 1 << 4;
	if (pmic_bus_write(AXP858_SHUTDOWN, reg_value))
		return -1;

	return 0;
}

int axp_init(void)
{
	u8 axp_chip_id;
	int ret;
	u8 reg_value;
    printf("PMIC: AXP853T/AXP858\n");
	ret = pmic_bus_init();
	if (ret)
		return ret;

	ret = pmic_bus_read(AXP858_CHIP_ID, &axp_chip_id);	

	if (!(axp_chip_id == 0x54))
		return -ENODEV;
	else {
		return ret;
	}

	return 0;
}
