/**
 ******************************************************************************
 * @file	flash.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	04-Sep-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef FLASH_H_
#define FLASH_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <cpu.h>

/* Exported types ------------------------------------------------------------*/
 typedef FLASH_TypeDef flash_t;

 typedef enum flash_opt
 {
	 FLASH_OPT_PREFETCH_BUFFER	= FLASH_ACR_PRFTEN,
	 FLASH_OPT_INS_CACHE		= FLASH_ACR_ICEN,
	 FLASH_OPT_DATA_CACHE		= FLASH_ACR_DCEN,
 } flash_opt;

/* Exported constants --------------------------------------------------------*/
#define FLASH_REG			((flash_t	*)FLASH_R_BASE)

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void
flash_opt_enable(flash_opt opt);

void
flash_opt_disable(flash_opt opt);

void
flash_set_latency(uint32 latency);

#ifdef __cplusplus
}
#endif

#endif /* FLASH_H_ */

/*****************************END OF FILE**************************************/
