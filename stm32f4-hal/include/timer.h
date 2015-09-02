/**
 * @file	timer.h
 * @brief	Framework header file.
 * @details	Framework header file.
 * @version	1.0
 * @date	Aug 30, 2015
 * @author	Eakkasit L.
 * @bug		No known bug
 * @warning	Improper use can crash your application
 * @copyright	GNU Public License.
 */

#ifndef INCLUDE_TIMER_H_
#define INCLUDE_TIMER_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <cpu.h>
#include <gpio.h>

typedef TIM_TypeDef		_timer_t;


typedef enum timer_num
{
	TIMER1,
	TIMER2,
	TIMER3,
	TIMER4,
	TIMER5,
	TIMER6,
	TIMER7,
	TIMER8,
	TIMER9,
	TIMER10,
	TIMER11,
	TIMER12,
	TIMER13,
	TIMER14,
} timer_num;

gpio_af
timer_get_af(timer_num timer);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_TIMER_H_ */
