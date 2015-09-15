/**
 ******************************************************************************
 * @file	cpu.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	04-Sep-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

#include <cpu.h>
#include <nvic.h>
#include <rcc.h>
#include <pwr.h>
#include <flash.h>
#include <scb.h>
#include <systick.h>


 void
 cpu_init_early(void)
 {
	 /* Reset clock */
	 rcc_reset();

	 /* Initial system control */
	 scb_init();
	 scb_set_vector(FLASH_BASE);

	/* Initial flash */
	flash_opt_enable(FLASH_OPT_INS_CACHE);
	flash_opt_enable(FLASH_OPT_DATA_CACHE);
	flash_opt_enable(FLASH_OPT_PREFETCH_BUFFER);
	flash_set_latency(FLASH_ACR_LATENCY_5WS);

	/* Initial power */
	pwr_enable();
	pwr_set_vos(1);

	/* Initial clocks */
	rcc_turn_on_clk(RCC_CLK_HSE);
	rcc_configure_pll(336,8,2,7);
	rcc_set_pllsrc(RCC_PLLSRC_HSE);
	rcc_turn_on_clk(RCC_CLK_PLL);

	rcc_switch_sysclk(RCC_CLKSRC_PLL);
	rcc_set_prescaler(RCC_PRESCALER_AHB, RCC_AHB_SYSCLK_DIV_1);
	rcc_set_prescaler(RCC_PRESCALER_APB1, RCC_APB1_HCLK_DIV_4);
	rcc_set_prescaler(RCC_PRESCALER_APB2, RCC_APB2_HCLK_DIV_2);

	/* Update global clock value */
	rcc_clk_update();
 }

 void
 cpu_init(void)
 {
	 /* Set 3 bit (8) preemption and 5 bit (32) sub-priority*/
	 nvic_set_priority_group(NVIC_PRIO_GROUP_4);

	/* Initial system tick timer */
	systick_init();
	systick_irq_enable();
 }


