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
#include <rcc.h>

void
syscfg_init(void)
{
	rcc_clk_enable(RCC_SYSCFG);
}

void
syscfg_set_exti(exti_num num, gpio_port port)
{
	CPU_MOD_REG(SYSCFG_REG->EXTICR[num >> 2], 0xF << ((num % 4) * 4), port);
}
