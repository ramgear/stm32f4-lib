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
static volatile uint32	system_ticks;

void
systick_init(uint32 freq_hz)
{
	uint32 ticks = SystemCoreClock  / freq_hz - 1;

	if(ticks > SYSTICK_LOAD_RELOAD_MSK)
		return;	/* Impossible reload value */

	nvic_set_irq_priority(SysTick_IRQn, 0xF);		/* Set lowest priority */

	SYSTICK_REG->LOAD	= ticks;	/* set reload register */
	SYSTICK_REG->VAL	= 0;
	SYSTICK_REG->CTRL	= SYSTICK_CTRL_CLKSOURCE_MSK | SYSTICK_CTRL_TICKINT_MSK | SYSTICK_CTRL_ENABLE_MSK;
	system_ticks = 0;
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
SysTick_Handler(void)
{
	if(SysTickCallback != NULL)
		(*SysTickCallback)((void *)&system_ticks);
}

