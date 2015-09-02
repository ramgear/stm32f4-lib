/**
 ******************************************************************************
 * @file	pwr_reg.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	28-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INCLUDE_REGISTERS_PWR_REG_H_
#define INCLUDE_REGISTERS_PWR_REG_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <cpu.h>

/* Exported types ------------------------------------------------------------*/

 /**
   * @brief Power Control
   */

 typedef PWR_TypeDef pwr_t;

/* Exported constants --------------------------------------------------------*/

#define PWR_REG			((pwr_t	*)PWR_BASE)   /*!< Power configuration struct           */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void
pwr_init(void);

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_REGISTERS_PWR_REG_H_ */

/*****************************END OF FILE**************************************/
