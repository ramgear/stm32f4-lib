/**
 * @file	systick.h
 * @brief	Framework header file.
 * @details	Framework header file.
 * @version	1.0
 * @date	Aug 30, 2015
 * @author	Eakkasit L.
 * @bug		No known bug
 * @warning	Improper use can crash your application
 * @copyright	GNU Public License.
 */

#ifndef INCLUDE_SYSTICK_H_
#define INCLUDE_SYSTICK_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <core/nvic.h>
#include <core/systick.h>


#define SYSTICK_REG			((systick_t	*)SYSTICK_BASE)		/*!< SysTick configuration struct           */

#define	__delay_ms			systick_delay_ms
#define	__delay_us			systick_delay_us

#define	SYSTICK_FREQ_HZ		100

typedef union system_time
{
	uint16	microsecond;
	uint16	millisecond;
	uint08	second;
	uint08	minute;
	uint08	hour;
	uint08	date;
} system_time;

extern volatile uint32 systick_ticks;
extern uint32 systick_us_per_tick;
extern uint32 systick_count_per_us;

CPU_INL_FUNC
uint32 systick_get_micro(void)
{
	return (systick_ticks * systick_us_per_tick + (((SYSTICK_REG->LOAD + 1) - SYSTICK_REG->VAL) / systick_count_per_us));
}

CPU_INL_FUNC
uint32 systick_get_milli(void)
{
	return (systick_get_micro() / 1000);
}

void
systick_init(void);

void
systick_irq_enable(void);

void
systick_irq_disable(void);

void
systick_set_callback(irq_callback_t cb);

void
systick_delay_ms(uint32 ms);

void
systick_delay_us(uint32 us);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_SYSTICK_H_ */
