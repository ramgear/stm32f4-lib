/**
 * @file	exti.h
 * @brief	Framework header file.
 * @details	Framework header file.
 * @version	1.0
 * @date	Aug 29, 2015
 * @author	Eakkasit L.
 * @bug		No known bug
 * @warning	Improper use can crash your application
 * @copyright	GNU Public License.
 */

#ifndef INCLUDE_EXTI_H_
#define INCLUDE_EXTI_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <cpu.h>
#include <gpio.h>

typedef EXTI_TypeDef		exti_t;
#define EXTI_REG			((exti_t	*)EXTI_BASE)

#define EXTI_NUM			16

typedef enum exti_num
{
	EXTI_0,
	EXTI_1,
	EXTI_2,
	EXTI_3,
	EXTI_4,
	EXTI_5,
	EXTI_6,
	EXTI_7,
	EXTI_8,
	EXTI_9,
	EXTI_10,
	EXTI_11,
	EXTI_12,
	EXTI_13,
	EXTI_14,
	EXTI_15,
} exti_num;

typedef enum exti_trigger
{
	EXTI_TRIGGER_RISING		= 1,
	EXTI_TRIGGER_FALLING	= 2,
	EXTI_TRIGGER_CHANGE		= 3,
} exti_trigger;

void
exti_set_owner(exti_num num, void *owner);

boolean
exti_available(exti_num num);

void
exti_release(exti_num num);

void
exti_enable(exti_num num);

void
exti_disable(exti_num num);

void
exti_set_trigger(exti_num num, exti_trigger trigger);

void
exti_set_callback(exti_num num, irq_callback_t cb);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_EXTI_H_ */
