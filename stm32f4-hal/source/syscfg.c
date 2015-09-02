/**
 * @file	syscfg.c
 * @brief	Framework header file.
 * @details	Framework header file.
 * @version	1.0
 * @date	Aug 29, 2015
 * @author	Eakkasit L.
 * @bug		No known bug
 * @warning	Improper use can crash your application
 * @copyright	GNU Public License.
 */


#include <syscfg.h>

void
syscfg_set_exti(exti_num num, gpio_port port)
{
    __set_reg_val(&SYSCFG_REG->EXTICR[num >> 2], (num % 4) * 4, 0xF, port);
}
