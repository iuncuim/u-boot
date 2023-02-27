// SPDX-License-Identifier: GPL-2.0+
/*
 * AXP305 driver
 *
 * (C) Copyright 2020 Jernej Skrabec <jernej.skrabec@siol.net>
 *
 * Based on axp221.c
 * (C) Copyright 2014 Hans de Goede <hdegoede@redhat.com>
 * (C) Copyright 2013 Oliver Schinagl <oliver@schinagl.nl>
 */

#include <common.h>
#include <command.h>
#include <errno.h>
#include <asm/arch/pmic_bus.h>
#include <axp_pmic.h>

#define AXP313_DCDC3_1220MV_OFFSET 71

static u8 axp313_mvolt_to_cfg(int mvolt, int min, int max, int div)
{
	if (mvolt < min)
		mvolt = min;
	else if (mvolt > max)
		mvolt = max;

	return  (mvolt - min) / div;
}

int axp_set_dcdc3(unsigned int mvolt)
{
	int ret;
	u8 cfg;

	ret = pmic_bus_read(AXP313_DCDC3_VOLTAGE, &cfg);

	if (mvolt >= 1220)
		cfg = AXP313_DCDC3_1220MV_OFFSET +
			axp313_mvolt_to_cfg(mvolt, 1220, 1860, 20);
	else
		cfg = axp313_mvolt_to_cfg(mvolt, 500, 1200, 10);
	if (mvolt == 0)
		return pmic_bus_clrbits(AXP313_OUTPUT_CTRL1,
					AXP313_OUTPUT_CTRL1_DCDC3_EN);

	ret = pmic_bus_write(AXP313_DCDC3_VOLTAGE, cfg);
	if (ret){
		return ret;
	}		

	return pmic_bus_setbits(AXP313_OUTPUT_CTRL1,
				AXP313_OUTPUT_CTRL1_DCDC3_EN);
}

int axp_init(void)
{
	u8 axp_chip_id;
	int ret;
	ret = pmic_bus_init();
	if (ret)
		return ret;

	ret = pmic_bus_read(AXP313_CHIP_VERSION, &axp_chip_id);
	if (ret)
		return ret;
	if (axp_chip_id != 0x4B)
		return -ENODEV;
	return ret;
}


