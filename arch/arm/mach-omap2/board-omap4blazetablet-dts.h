/*
 * arch/arm/mach-omap2/board-omap4blazetablet-dts.h
 *
 * Author: Ruslan Bilovol <ruslan.bilovol@ti.com>
 *
 * Copyright (C) 2013 Texas Instruments
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef _BOARD_OMAP4_BLAZETABLET_DTS_H
#define _BOARD_OMAP4_BLAZETABLET_DTS_H

#include "common.h"

#ifdef CONFIG_MACH_OMAP4_BLAZETABLET_DTS
extern void __init omap4_blazetablet_init(void);
#else
static inline void __init omap4_blazetablet_init(void){};
#endif

#endif /* _BOARD_OMAP4_BLAZETABLET_DTS_H */
