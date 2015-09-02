/**
 * @file	timer.c
 * @brief	Framework header file.
 * @details	Framework header file.
 * @version	1.0
 * @date	Aug 30, 2015
 * @author	Eakkasit L.
 * @bug		No known bug
 * @warning	Improper use can crash your application
 * @copyright	GNU Public License.
 */

#include <timer.h>
#include <rcc.h>

#define TIMER_DEV_ENTRY(__TIM,TYP)	\
	[TIMER##__TIM] = {TIM##__TIM##_BASE, TIMER_##TYP, RCC_TIM##__TIM}

typedef enum timer_type
{
	TIMER_ADVANCE,
	TIMER_GENERAL,
	TIMER_BASIC
} timer_type;

typedef struct timer_dev
{
	const uint32		reg;
	const timer_type	type;
	const rcc_clk_id	clk_id;
} timer_dev;

__lookup_table
timer_dev timer_dev_table[] =
{
		TIMER_DEV_ENTRY(1,	ADVANCE	),
		TIMER_DEV_ENTRY(2,	GENERAL	),
		TIMER_DEV_ENTRY(3,	GENERAL	),
		TIMER_DEV_ENTRY(4,	GENERAL	),
		TIMER_DEV_ENTRY(5,	GENERAL	),
		TIMER_DEV_ENTRY(6,	BASIC	),
		TIMER_DEV_ENTRY(7,	BASIC	),
		TIMER_DEV_ENTRY(8,	ADVANCE	),
		TIMER_DEV_ENTRY(9,	GENERAL	),
		TIMER_DEV_ENTRY(10,	GENERAL	),
		TIMER_DEV_ENTRY(11,	GENERAL	),
		TIMER_DEV_ENTRY(12,	GENERAL	),
		TIMER_DEV_ENTRY(13,	GENERAL	),
		TIMER_DEV_ENTRY(14,	GENERAL	),
};


gpio_af
timer_get_af(timer_num timer)
{
	switch(timer)
	{
		case TIMER1:
		case TIMER2:
			return GPIO_AF_TIM_1_2;
		case TIMER3:
		case TIMER4:
		case TIMER5:
	        return GPIO_AF_TIM_3_4_5;
		case TIMER8:
		case TIMER9:
		case TIMER10:
		case TIMER11:
	        return GPIO_AF_TIM_8_9_10_11;
		case TIMER12:
		case TIMER13:
		case TIMER14:
	        return GPIO_AF_CAN_1_2_TIM_12_13_14;
	    default:
	        return (gpio_af)-1;
	}
}
