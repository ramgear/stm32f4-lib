/**
 * @file	syscfg.h
 * @brief	Framework header file.
 * @details	Framework header file.
 * @version	1.0
 * @date	Aug 29, 2015
 * @author	Eakkasit L.
 * @bug		No known bug
 * @warning	Improper use can crash your application
 * @copyright	GNU Public License.
 */

#ifndef INCLUDE_SYSCFG_H_
#define INCLUDE_SYSCFG_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <cpu.h>
#include <exti.h>
#include <gpio.h>

typedef SYSCFG_TypeDef	syscfg_t;
#define SYSCFG_REG	((syscfg_t *)SYSCFG_BASE)

void
syscfg_init(void);

void
syscfg_set_exti(exti_num num, gpio_port port);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_SYSCFG_H_ */
