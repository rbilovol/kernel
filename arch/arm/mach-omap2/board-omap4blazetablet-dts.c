/*
 * Board support file for OMAP4 Blaze Tablet.
 *
 * This is a transitional board support file for
 * features that are not supported by Device Tree yet
 *
 * Copyright (C) 2013 Texas Instruments
 *
 * Author: Ruslan Bilovol <ruslan.bilovol@ti.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/usb/otg.h>
#include <linux/usb/musb.h>

#include <asm/mach-types.h>

#include "common.h"
#include "common-board-devices.h"
#include "board-omap4blazetablet-dts.h"

static struct omap_musb_board_data musb_board_data = {
	.interface_type		= MUSB_INTERFACE_UTMI,
	.mode			= MUSB_OTG,
	.power			= 200,
};

void __init omap4_blazetablet_init(void)
{
	usb_musb_init(&musb_board_data);
}
