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
rx_irq_callback(void *sender, uint08 *data, uint08 len)
{
	((HardwareSerial *)sender)->OnRxInterrupt(data, len);
}

void
tx_irq_callback(void *sender)
{
	((HardwareSerial *)sender)->OnTxInterrupt();
}
