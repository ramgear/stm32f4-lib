/**
 ******************************************************************************
 * @file	flash.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	04-Sep-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

#include <flash.h>

void
flash_opt_enable(flash_opt opt)
{
	CPU_MOD_REG(FLASH_REG->ACR, opt, 1);
}

void
flash_opt_disable(flash_opt opt)
{
	CPU_MOD_REG(FLASH_REG->ACR, opt, 0);
}

void
flash_set_latency(uint32 latency)
{
	CPU_MOD_REG(FLASH_REG->ACR, FLASH_ACR_LATENCY, latency);
}

