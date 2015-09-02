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

void
systick_init(uint32 freq_hz);

void
systick_irq_enable(void);

void
systick_irq_disable(void);

void
systick_set_callback(irq_callback_t cb);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_SYSTICK_H_ */
