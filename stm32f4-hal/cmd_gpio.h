/**
 ******************************************************************************
 * @file	cmd_gpio.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	18-Sep-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CMD_GPIO_H_
#define CMD_GPIO_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "shell.h"
#include "gpio.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
 SHELL_FUNC(gpio);

#ifdef __cplusplus
}
#endif

#endif /* CMD_GPIO_H_ */

/*****************************END OF FILE**************************************/
