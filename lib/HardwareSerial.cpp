/**
 ******************************************************************************
 * @file	HardwareSerial.cpp
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	02-Sep-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

#include <HardwareSerial.h>

void
rx_irq_callback(void *sender, uint32 count)
{
	((HardwareSerial *)sender)->OnRxInterrupt(count);
}

void
tx_irq_callback(void *sender)
{
	((HardwareSerial *)sender)->OnTxInterrupt();
}
