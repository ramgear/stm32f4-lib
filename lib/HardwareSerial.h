/**
 ******************************************************************************
 * @file	HardwareSerial.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	02-Sep-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HARDWARESERIAL_H_
#define HARDWARESERIAL_H_

/* Includes ------------------------------------------------------------------*/
#include <usart.h>
#include <AlternatePin.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void
rx_irq_callback(void *sender, char data);
void
tx_irq_callback(void *sender);

class HardwareSerial
{
protected:
	usart_num		m_serial_no;

public:
	AlternatePin	m_RxPin;
	AlternatePin	m_TxPin;

public:
	HardwareSerial()
	: m_serial_no(SERIAL_INVALID)
	{

	}

	virtual ~HardwareSerial()
	{
		if(m_serial_no != SERIAL_INVALID)
			usart_release(m_serial_no);
	}

	HardwareSerial& operator=(const usart_num serial)
	{
		if(m_serial_no != SERIAL_INVALID)
			usart_release(m_serial_no);

		m_serial_no = serial;
		usart_init(serial);
		usart_set_owner(serial, this);
		usart_set_rx_handler(serial, rx_irq_callback);
		usart_set_tx_handler(serial, tx_irq_callback);

		return *this;
	}

	void
	Begin(uint32 speed)
	{
		if(m_RxPin == INVALID_PIN || m_TxPin == INVALID_PIN)
		{
			trace("ERROR: Please select RX/TX before start!");

			return;
		}

		gpio_set_af(m_RxPin, usart_get_af(m_serial_no));
		gpio_set_af(m_TxPin, usart_get_af(m_serial_no));

		usart_set_speed(m_serial_no, speed);
	}

	void OnRxInterrupt(char data)
	{
		(void)data;
	}

	void OnTxInterrupt(void)
	{

	}
};

#ifdef __cplusplus
}
#endif

#endif /* HARDWARESERIAL_H_ */

/*****************************END OF FILE**************************************/
