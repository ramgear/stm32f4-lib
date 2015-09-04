/**
 ******************************************************************************
 * @file	pwr.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	28-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

#include <pwr.h>
#include <rcc.h>

void
pwr_init(void)
{
	pwr_enable();
	pwr_set_vos(1);
}

void
pwr_enable(void)
{
	rcc_clk_enable(RCC_PWR);
}

void
pwr_set_vos(uint32 vos)
{
	PWR_REG->CR |= CPU_MOD_VAL(vos, PWR_CR_VOS);
}

