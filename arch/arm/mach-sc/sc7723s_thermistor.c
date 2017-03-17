 /*
  * sc7732s_thermistor.c - thermistor for SC7730S projects
  *
  * Copyright (C) 2014 Samsung Electronics
  * SangYoung Son <hello.son@samsung.com>
  *
  * This program is free software; you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <mach/sc7723s_thermistor.h>
#include <mach/sec_thermistor.h>

#if defined(CONFIG_SEC_THERMISTOR)
#if defined(CONFIG_MACH_CORE3_W)
static struct sec_therm_adc_table temper_table_ap[] = {
	{543 , 700},
	{632 , 650},
	{721 , 600},
	{832 , 550},
	{944 , 500},
	{1061 , 450},
	{1178 , 400},
	{1323 , 350},
	{1468 , 300},
	{1607 , 250},
	{1747 , 200},
	{1869 , 150},
	{1992 , 100},
	{2087 , 50},
	{2182 , 0},
	{2260 , -50},
	{2329 , -100},
	{2386 , -150},
	{2448 , -200},
};

static struct sec_therm_adc_table temper_table_dcxo[] = {
	{673 , 700},
	{788 , 650},
	{903 , 600},
	{1052 , 550},
	{1202 , 500},
	{1377 , 450},
	{1553 , 400},
	{1754 , 350},
	{1955 , 300},
	{2169 , 250},
	{2383 , 200},
	{2588 , 150},
	{2793 , 100},
	{2949 , 50},
	{3106 , 0},
	{3254 , -50},
	{3380 , -100},
	{3473 , -150},
	{3556 , -200},
};	
#elif defined(CONFIG_MACH_YOUNG23GDTV) || defined(CONFIG_MACH_J13G)
static struct sec_therm_adc_table temper_table_ap[] = {
	{579 , 670},
	{617 , 650},
	{650 , 600},
	{718 , 580},
	{816 , 550},
	{939 , 500},
	{1052 , 450},
	{1110 , 430},
	{1182 , 400},
	{1316 , 350},
	{1458 , 300},
	{1598 , 250},
	{1727 , 200},
	{1856 , 150},
	{1979 , 100},
	{2080 , 50},
	{2136 , 20},
	{2167 , 0},
	{2213 , -20},
	{2258 , -50},
	{2291 , -70},
	{2386 , -150},
	{2410 , -200},
};

static struct sec_therm_adc_table temper_table_dcxo[] = {
	{674 , 670},
	{707 , 650},
	{750 , 630},
	{824 , 600},
	{956 , 550},
	{1104 , 500},
	{1262 , 450},
	{1319 , 430},
	{1422 , 400},
	{1506 , 350},
	{1693 , 300},
	{1915 , 250},
	{2201 , 200},
	{2395 , 150},
	{2466 , 100},
	{2793 , 50},
	{2870 , 20},
	{2931 , 0},
	{2982 , -20},
	{3062 , -50},
	{3117 , -70},
	{3277 , -150},
	{3343 , -200},
};

#elif defined(CONFIG_MACH_GRANDNEOVE3G)
static struct sec_therm_adc_table temper_table_ap[] = {
	{290 , 900},
	{350 , 850},
	{400 , 800},
	{469 , 750},
	{530 , 700},
	{614 , 650},
	{737 , 600},
	{848 , 550},
	{945 , 500},
	{1067 , 450},
	{1189 , 400},
	{1341 , 350},
	{1493 , 300},
	{1621 , 250},
	{1749 , 200},
	{1853 , 150},
	{1956 , 100},
	{2061 , 50},
	{2165 , 0},
	{2255 , -50},
	{2312 , -100},
	{2365 , -150},
	{2402, -200},
};

static struct sec_therm_adc_table temper_table_dcxo[] = {
	{673 , 700},
	{788 , 650},
	{903 , 600},
	{1052 , 550},
	{1202 , 500},
	{1377 , 450},
	{1553 , 400},
	{1754 , 350},
	{1955 , 300},
	{2169 , 250},
	{2383 , 200},
	{2588 , 150},
	{2793 , 100},
	{2949 , 50},
	{3106 , 0},
	{3254 , -50},
	{3380 , -100},
	{3473 , -150},
	{3556 , -200},
};

#else
static struct sec_therm_adc_table temper_table_ap[] = {
	{981 , 670}, /* 67 */
	{1041 , 650}, /* 65 */
	{1080 , 630}, /* 63 */
	{1142 , 600}, /* 60 */
	{1292 , 550}, /* 55 */
	{1477 , 500}, /* 50 */
	{1657 , 450}, /* 45 */
	{1707 , 430}, /* 43 */
	{1780 , 400}, /* 40 */
	{1972 , 350}, /* 35 */
	{2180 , 300}, /* 30 */
	{2373 , 250}, /* 25 */
	{2563 , 200}, /* 20 */
	{2842 , 150}, /* 15 */
	{3122 , 100}, /* 10 */
	{3292 , 50}, /* 5 */
	{3383 , 20}, /* 2 */
	{3424 , 0}, /* 0 */
	{3466 , -20}, /* -2 */
	{3543 , -50}, /* -5 */
	{3593 , -70}, /* -7 */
	{3782 , -150}, /* -15 */
	{3887, -200},	 /* -20 */
};

static struct sec_therm_adc_table temper_table_dcxo[] = {
	{981 , 670}, /* 67 */
	{1041 , 650}, /* 65 */
	{1080 , 630}, /* 63 */
	{1142 , 600}, /* 60 */
	{1292 , 550}, /* 55 */
	{1477 , 500}, /* 50 */
	{1657 , 450}, /* 45 */
	{1707 , 430}, /* 43 */
	{1780 , 400}, /* 40 */
	{1972 , 350}, /* 35 */
	{2180 , 300}, /* 30 */
	{2373 , 250}, /* 25 */
	{2563 , 200}, /* 20 */
	{2842 , 150}, /* 15 */
	{3122 , 100}, /* 10 */
	{3292 , 50}, /* 5 */
	{3383 , 20}, /* 2 */
	{3424 , 0}, /* 0 */
	{3466 , -20}, /* -2 */
	{3543 , -50}, /* -5 */
	{3593 , -70}, /* -7 */
	{3782 , -150}, /* -15 */
	{3887, -200},	 /* -20 */
};
#endif

static struct sec_therm_platform_data sec_therm_pdata = {
	.ap_adc_arr_size	= ARRAY_SIZE(temper_table_ap),
	.ap_adc_table	= temper_table_ap,
	.ap_channel = 3,
	.dcxo_adc_arr_size	= ARRAY_SIZE(temper_table_dcxo),
	.dcxo_adc_table	= temper_table_dcxo,
	.dcxo_channel = 2,
};


struct platform_device sec_device_thermistor = {
	.name = "sec-thermistor",
	.id = -1,
	.dev.platform_data = &sec_therm_pdata,
};

struct sec_therm_platform_data * fill_therm_pdata(struct platform_device *pdev)
{
	pdev->dev.platform_data = &sec_therm_pdata;
	pdev->id = -1;

	return &sec_therm_pdata;
}
#endif
