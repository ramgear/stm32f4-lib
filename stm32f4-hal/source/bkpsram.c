/**
 ******************************************************************************
 * @file	bkpsram.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	07-Sep-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

#include <bkpsram.h>
#include <pwr.h>

void
bkpsram_init(void)
{
	pwr_bkpsram_enable();
}

