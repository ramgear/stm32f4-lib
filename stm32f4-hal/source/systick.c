/**
 * @file	systick.c
 * @brief	Framework header file.
 * @details	Framework header file.
 * @version	1.0
 * @date	Aug 30, 2015
 * @author	Eakkasit L.
 * @bug		No known bug
 * @warning	Improper use can crash your application
 * @copyright	GNU Public License.
 */

#include <systick.h>
#include <rcc.h>
#include <nvic.h>

irq_callback_t SysTickCallback;

volatile uint32 systick_milli;
uint32 systick_us_per_count;

void
systick_init(void)
{
	uint32 ticks = rcc_get_sys_clk_freq()  / 999;	/* Fixed systick to 1ms */

	if(ticks > SYSTICK_LOAD_RELOAD_MSK)
		return;	/* Impossible reload value */

	nvic_set_irq_priority(SysTick_IRQn, 0xF);		/* Set lowest priority */

	SYSTICK_REG->LOAD	= ticks;	/* set reload register */
	SYSTICK_REG->VAL	= 0;
	SYSTICK_REG->CTRL	= SYSTICK_CTRL_CLKSOURCE_MSK | SYSTICK_CTRL_TICKINT_MSK | SYSTICK_CTRL_ENABLE_MSK;
	systick_milli = 0;
	systick_us_per_count = rcc_get_sys_clk_freq() / 1000000;
}

void
systick_irq_enable(void)
{
	nvic_irq_enable(SysTick_IRQn);
}

void
systick_irq_disable(void)
{
	nvic_irq_disable(SysTick_IRQn);
}

void
systick_set_callback(irq_callback_t cb)
{
	SysTickCallback = cb;
}

void
systick_delay_ms(uint32 ms)
{
	uint32 end_ms = systick_milli + ms;
	while(systick_milli < end_ms)
		;
}

void
systick_delay_us(uint32 us)
{
	uint32 end_us = systick_get_micro() + us;
	while(systick_get_micro() < end_us)
		;
}

void
SysTick_Handler(void)
{
	CPU_SR_ALLOC
	CPU_ENTER_CRITICAL
	++systick_milli;
	CPU_EXIT_CRITICAL

	if(SysTickCallback != NULL)
		(*SysTickCallback)((void *)&systick_milli);
}

