/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2020 Jernej Skrabec <jernej.skrabec@siol.net>
 */

enum axp313_reg {
	AXP313_CHIP_VERSION = 0x3,
	AXP313_OUTPUT_CTRL1 = 0x10,
	AXP313_DCDC3_VOLTAGE = 0x15,
	// AXP313_SHUTDOWN = 0x32,
};

#define AXP313_CHIP_VERSION_MASK	0xcf

#define AXP313_OUTPUT_CTRL1_DCDC3_EN	(1 << 2)

// #define AXP313_POWEROFF			(1 << 7)

// #define AXP_POWER_STATUS		0x00
// #define AXP_POWER_STATUS_ALDO_IN		BIT(0)
