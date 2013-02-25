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
#include <linux/gpio.h>
#include <linux/usb/otg.h>
#include <linux/usb/musb.h>

#include <asm/mach-types.h>

#include <video/omapdss.h>
#include <video/omap-panel-tc358765.h>

#include "mux.h"
#include "control.h"
#include "common.h"
#include "soc.h"
#include "common-board-devices.h"
#include "board-omap4blazetablet-dts.h"

static struct omap_musb_board_data musb_board_data = {
	.interface_type		= MUSB_INTERFACE_UTMI,
	.mode			= MUSB_OTG,
	.power			= 200,
};

#ifdef CONFIG_PANEL_TC358765
static struct tc358765_board_data tablet_dsi_panel = {
	.lp_time	= 0x4,
	.clrsipo	= 0x3,
	.lv_is		= 0x1,
	.lv_nd		= 0x6,
	.vtgen		= 0x1,
	.vsdelay	= 0xf,
	.pin_config = {
		.num_pins       = 10,
		.pins           = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 },
	},
};

static struct omap_dss_device tablet_lcd_device = {
	.name                   = "lcd",
	.driver_name            = "tc358765",
	.type                   = OMAP_DISPLAY_TYPE_DSI,
	.data			= &tablet_dsi_panel,
	.phy.dsi                = {
		.module		= 0,
	},
	.panel = {
		.timings = {
			.x_res		= 1280,
			.y_res		= 800,
			.pixel_clock	= 65183,
			.hfp		= 10,
			.hsw		= 20,
			.hbp		= 10,
			.vfp		= 4,
			.vsw		= 4,
			.vbp		= 4,
		},
		.dsi_mode = OMAP_DSS_DSI_VIDEO_MODE,
		.dsi_vm_timings = {
				.hsa			= 0,
				.hfp			= 6,
				.hbp			= 21,
				.vsa			= 4,
				.vfp			= 4,
				.vbp			= 4,

				.vp_hsync_end		= false,
				.vp_vsync_end		= false,

				.blanking_mode		= 0,
				.hsa_blanking_mode	= 1,
				.hfp_blanking_mode	= 1,
				.hbp_blanking_mode	= 1,

				.ddr_clk_always_on	= true,

				.window_sync		= 4,
		}
	},

	.ctrl = {
		.pixel_size = 24,
	},

	.reset_gpio     = 102,
	.channel = OMAP_DSS_CHANNEL_LCD,
	.platform_enable = NULL,
	.platform_disable = NULL,
};

static struct omap_dss_device *tablet_dss_devices[] = {
	&tablet_lcd_device,
};

static struct omap_dss_board_info tablet_dss_data = {
	.num_devices	= ARRAY_SIZE(tablet_dss_devices),
	.devices	= tablet_dss_devices,
	.default_device	= &tablet_lcd_device,
};

static void __init tablet_lcd_init(void)
{
	u32 reg;
	int status;

	/* Enable 3 lanes in DSI1 module, disable pull down */
	reg = omap4_ctrl_pad_readl(OMAP4_CTRL_MODULE_PAD_CORE_CONTROL_DSIPHY);
	reg &= ~OMAP4_DSI1_LANEENABLE_MASK;
	reg |= 0x1f << OMAP4_DSI1_LANEENABLE_SHIFT;
	reg &= ~OMAP4_DSI1_PIPD_MASK;
	reg |= 0x1f << OMAP4_DSI1_PIPD_SHIFT;
	omap4_ctrl_pad_writel(reg, OMAP4_CTRL_MODULE_PAD_CORE_CONTROL_DSIPHY);

	status = gpio_request_one(tablet_lcd_device.reset_gpio,
				GPIOF_OUT_INIT_LOW, "lcd_reset_gpio");
	gpio_set_value(tablet_lcd_device.reset_gpio, 1);

	if (status)
		pr_err("%s: Could not get lcd_reset_gpio\n", __func__);
}

static void __init tablet_display_init(void)
{
	/* Ruslan: fref_clk4_out is mux'ed in dtb */
	tablet_lcd_init();
	omap_display_init(&tablet_dss_data);
}
#else /* CONFIG_PANEL_TC358765 */
static void __init tablet_display_init(void){};
#endif /* CONFIG_PANEL_TC358765 */



void __init omap4_blazetablet_init(void)
{
	usb_musb_init(&musb_board_data);
	tablet_display_init();
}
