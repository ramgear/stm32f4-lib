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
#include <stdarg.h>
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
rx_irq_callback(void *sender, uint08 *data, uint08 len);
void
tx_irq_callback(void *sender);

class HardwareSerial
{
protected:
	usart_num		m_serial_no;

	char			tx_buffer[USART_BUFFER_SIZE];
	char			rx_buffer[USART_BUFFER_SIZE];
	uint32			rx_index;
	bool			tx_ready;
	bool			RxReceived;

public:
	AlternatePin	m_RxPin;
	AlternatePin	m_TxPin;

public:
	HardwareSerial()
	: m_serial_no(SERIAL_INVALID), rx_index(0), tx_ready(false), RxReceived(false)
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

	virtual void
	Begin(uint32 speed)
	{
		if(m_RxPin == INVALID_PIN || m_TxPin == INVALID_PIN)
		{
			trace("ERROR: Please select RX/TX before start!");

			return;
		}

		gpio_set_af(m_RxPin, usart_get_af(m_serial_no));
		gpio_set_af(m_TxPin, usart_get_af(m_serial_no));

		//usart_frame_enable(m_serial_no, true);

		usart_set_speed(m_serial_no, speed);
	}

	virtual void
	Send(const char *format, ...)
	{
		int ret;
		  va_list ap;
		  uint08	*ptr;

		  va_start (ap, format);

		  // Print to the local buffer
		  ret = vsnprintf (tx_buffer, sizeof(tx_buffer), format, ap);
		  if (ret > 0)
		    {
			  //trace("Send: %s", tx_buffer);

			  ptr = (uint08 *)tx_buffer;
			  tx_ready = true;
			  while(ret--)
			  {
				  while(!tx_ready);
				  usart_send(m_serial_no, *ptr++);
			  }
		    }

		  va_end (ap);
	}

	void OnRxInterrupt(uint08 *data, uint08 len)
	{
		(void)len;

		rx_buffer[rx_index++] = *data;

		if(*data == '\n')
		{
			rx_buffer[rx_index] = 0;
			rx_index = 0;

			RxReceived = true;
		}
	}

	void OnTxInterrupt(void)
	{
		tx_ready = true;
	}
};

#ifdef __cplusplus
}
#endif

#endif /* HARDWARESERIAL_H_ */

/*****************************END OF FILE**************************************/
