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
#include <systick.h>
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
rx_irq_callback(void *sender, uint32 count);
void
tx_irq_callback(void *sender);

class HardwareSerial
{
protected:
	usart_num		m_serial_no;

	char			tx_buffer[USART_BUFFER_SIZE];
	char			rx_buffer[USART_BUFFER_SIZE];
	bool			tx_ready;
	volatile bool			mReceived;

public:
	AlternatePin	m_RxPin;
	AlternatePin	m_TxPin;

public:
	HardwareSerial()
	: m_serial_no(SERIAL_INVALID), tx_ready(false), mReceived(false)
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
			  usart_send_dma(m_serial_no, (const uint08 *)tx_buffer, ret);
/*
			  ptr = (uint08 *)tx_buffer;
			  tx_ready = true;
			  while(ret--)
			  {
				  while(!tx_ready);
				  usart_send(m_serial_no, *ptr++);
			  }*/
		    }

		  va_end (ap);
	}

	void
	WaitReceiveData(uint32 timeout = 1000)
	{
		uint32 milli_end = systick_get_milli() + timeout;

		while(!mReceived && (systick_get_milli() < milli_end));

		if(!mReceived)
		{
			strcpy(rx_buffer, "Timeout!\r\n");
		}
	}

	void
	GetReceivedData(char *data)
	{
		strcpy(data, rx_buffer);
		memset(rx_buffer, 0, USART_BUFFER_SIZE);
		mReceived = false;
	}

	virtual void
	OnRxInterrupt(uint32 count)
	{
		memset(rx_buffer, 0, sizeof(rx_buffer));
		usart_read(m_serial_no, (uint08 *)rx_buffer, count);
		mReceived = true;
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
