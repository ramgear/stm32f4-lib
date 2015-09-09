/**
 ******************************************************************************
 * @file	HC05Bluetooth.cpp
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	08-Sep-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

#include <HC05Bluetooth.h>

extern "C" void
hc05_stat_changed(void *owner)
{
	((HC05Bluetooth *)owner)->OnStatChanged();
}

volatile bool HC05Bluetooth::m_bStat = false;

void
HC05Bluetooth::Begin(uint32 speed)
{
	/* Initial power pin as open drain output */
	//m_PwrPin = true;

	HardwareSerial::Begin(speed);

	m_StatPin.AttachInterrupt(hc05_stat_changed, EXTI_TRIGGER_CHANGE, true);

	trace("HC-05 speed at %d\r\n", speed);
}
