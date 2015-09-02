/**
 * @file	gpio.h
 * @brief	Framework header file.
 * @details	Framework header file.
 * @version	1.0
 * @date	Aug 28, 2015
 * @author	Eakkasit L.
 * @bug		No known bug
 * @warning	Improper use can crash your application
 * @copyright	GNU Public License.
 */

#ifndef INCLUDE_GPIO_H_
#define INCLUDE_GPIO_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <cpu.h>

#define	GPIO_PORT_NUM	9

 /**********************************************************************************
  * GPIO Types
  *********************************************************************************/

 /**
  * @brief	List of available GPIO Ports.
  */
typedef enum gpio_port
{
	PORTA,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	PORTF,
	PORTG,
	PORTH,
	PORTI,
} gpio_port;

 /**
  * @brief	List of available GPIO Pins.
  */
 typedef enum gpio_pin
 {
 	PA0,
 	PA1,
 	PA2,
 	PA3,
 	PA4,
 	PA5,
 	PA6,
 	PA7,
 	PA8,
 	PA9,
 	PA10,
 	PA11,
 	PA12,
 	PA13,
 	PA14,
 	PA15,
 	PB0,
 	PB1,
 	PB2,
 	PB3,
 	PB4,
 	PB5,
 	PB6,
 	PB7,
 	PB8,
 	PB9,
 	PB10,
 	PB11,
 	PB12,
 	PB13,
 	PB14,
 	PB15,
 	PC0,
 	PC1,
 	PC2,
 	PC3,
 	PC4,
 	PC5,
 	PC6,
 	PC7,
 	PC8,
 	PC9,
 	PC10,
 	PC11,
 	PC12,
 	PC13,
 	PC14,
 	PC15,
 	PD0,
 	PD1,
 	PD2,
 	PD3,
 	PD4,
 	PD5,
 	PD6,
 	PD7,
 	PD8,
 	PD9,
 	PD10,
 	PD11,
 	PD12,
 	PD13,
 	PD14,
 	PD15,
 #if defined(GPIOE)
 	PE0,
 	PE1,
 	PE2,
 	PE3,
 	PE4,
 	PE5,
 	PE6,
 	PE7,
 	PE8,
 	PE9,
 	PE10,
 	PE11,
 	PE12,
 	PE13,
 	PE14,
 	PE15,
 #endif
 #if defined(GPIOF)
 	PF0,
 	PF1,
 	PF2,
 	PF3,
 	PF4,
 	PF5,
 	PF6,
 	PF7,
 	PF8,
 	PF9,
 	PF10,
 	PF11,
 	PF12,
 	PF13,
 	PF14,
 	PF15,
 #endif
 #if defined(GPIOG)
 	PG0,
 	PG1,
 	PG2,
 	PG3,
 	PG4,
 	PG5,
 	PG6,
 	PG7,
 	PG8,
 	PG9,
 	PG10,
 	PG11,
 	PG12,
 	PG13,
 	PG14,
 	PG15,
 #endif
 #if defined(GPIOH)
 	PH0,
 	PH1,
 	PH2,
 	PH3,
 	PH4,
 	PH5,
 	PH6,
 	PH7,
 	PH8,
 	PH9,
 	PH10,
 	PH11,
 	PH12,
 	PH13,
 	PH14,
 	PH15,
 #endif
 #if defined(GPIOI)
 	PI0,
 	PI1,
 	PI2,
 	PI3,
 	PI4,
 	PI5,
 	PI6,
 	PI7,
 	PI8,
 	PI9,
 	PI10,
 	PI11,
 	PI12,
 	PI13,
 	PI14,
 	PI15,
 #endif
	INVALID_PIN
 } gpio_pin;

 typedef enum
 {
	 GPIO_MODE_INPUT,
	 GPIO_MODE_OUTPUT,
	 GPIO_MODE_ALTERNATE,
	 GPIO_MODE_ANALOG,
 } gpio_mode;

 typedef enum
 {
	 GPIO_OUTPUT_PP,
	 GPIO_OUTPUT_OD,
 } gpio_output;

 typedef enum
 {
	 GPIO_SPEED_LOW,
	 GPIO_SPEED_MEDIUM,
	 GPIO_SPEED_FAST,
	 GPIO_SPEED_HIGH,
 } gpio_speed;

 typedef enum
 {
	 GPIO_PUPD_NONE,
	 GPIO_PUPD_UP,
	 GPIO_PUPD_DOWN,
 } gpio_pupd;

 typedef enum
 {
	GPIO_AF_SYS                  = 0, 	/**< System. */
	GPIO_AF_TIM_1_2              = 1, 	/**< Timers 1 and 2. */
	GPIO_AF_TIM_3_4_5            = 2, 	/**< Timers 3, 4, and 5. */
	GPIO_AF_TIM_8_9_10_11        = 3, 	/**< Timers 8 through 11. */
	GPIO_AF_I2C                  = 4, 	/**< I2C 1, 2, and 3. */
	GPIO_AF_SPI_1_2              = 5, 	/**< SPI1, SPI2/I2S2. */
	GPIO_AF_SPI3                 = 6, 	/**< SPI3/I2S3. */
	GPIO_AF_USART_1_2_3          = 7, 	/**< USART 1, 2, and 3. */
	GPIO_AF_USART_4_5_6          = 8, 	/**< UART 4 and 5, USART 6. */
	GPIO_AF_CAN_1_2_TIM_12_13_14 = 9, 	/**< CAN 1 and 2, timers 12, 13, and 14. */
	GPIO_AF_USB_OTG_FS_HS        = 10, 	/**< USB OTG HS and FS. */
	GPIO_AF_ETH                  = 11, 	/**< Ethernet MII and RMII. */
	GPIO_AF_FSMC_SDIO_OTG_FS     = 12, 	/**< FSMC, SDIO, and USB OTG FS. */
	GPIO_AF_DCMI                 = 13, 	/**< DCMI. */
	GPIO_AF_EVENTOUT             = 15, 	/**< EVENTOUT. */
	GPIO_AF_INVALID				 = -1
 } gpio_af;

 typedef struct
 {
	const gpio_port		port;
	const uint08		pin;
 } gpio_pin_dev;


 /**********************************************************************************
  * GPIO Functions
  *********************************************************************************/

const gpio_pin_dev *
gpio_init(gpio_pin pin);

const gpio_pin_dev *
gpio_get_dev(gpio_pin pin);

boolean
gpio_available(gpio_pin pin);

void
gpio_release(gpio_pin pin);

void
gpio_set_mode(const gpio_pin_dev *dev, gpio_mode mode);

void
gpio_set_output(const gpio_pin_dev *dev, gpio_output otype);

void
gpio_set_speed(const gpio_pin_dev *dev, gpio_speed speed);

void
gpio_set_pupd(const gpio_pin_dev *dev, gpio_pupd pupd);

void
gpio_set_af(const gpio_pin_dev *dev, gpio_af af);

void
gpio_set_bit(const gpio_pin_dev *dev);

void
gpio_clear_bit(const gpio_pin_dev *dev);

void
gpio_toggle_bit(const gpio_pin_dev *dev);

boolean
gpio_read_bit(const gpio_pin_dev *dev);

boolean
gpio_get_out_stat(const gpio_pin_dev *dev);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_GPIO_H_ */
