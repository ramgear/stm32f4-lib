/**
 ******************************************************************************
 * @file	usart.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	31-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INCLUDE_USART_H_
#define INCLUDE_USART_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <cpu.h>
#include <rcc.h>
#include <nvic.h>
#include <gpio.h>

/* Exported types ------------------------------------------------------------*/
typedef USART_TypeDef	usart_t;

#define	USART_NUM_MAX	6

typedef enum usart_num
{
	SERIAL1,
	SERIAL2,
	SERIAL3,
	SERIAL4,
	SERIAL5,
	SERIAL6,
	SERIAL_INVALID,
} usart_num;

typedef	void (*usart_rx_handler)(void *sender, char data);
typedef	void (*usart_tx_handler)(void *sender);

/**********************************************************************************
 * GPIO Functions
 *********************************************************************************/

void
usart_init(usart_num num);

void
usart_set_owner(usart_num num, void *owner);

boolean
usart_available(usart_num num);

void
usart_release(usart_num num);

void
usart_set_speed(usart_num num, uint32 speed);

gpio_af
usart_get_af(usart_num num);

void
usart_set_rx_handler(usart_num num, usart_rx_handler handler);

void
usart_set_tx_handler(usart_num num, usart_tx_handler handler);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_USART_H_ */

/*****************************END OF FILE**************************************/
