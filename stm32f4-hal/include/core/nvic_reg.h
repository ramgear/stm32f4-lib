/**
 ******************************************************************************
 * @file	reg_nvic.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	28-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INCLUDE_CORE_NVIC_REG_H_
#define INCLUDE_CORE_NVIC_REG_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <cpu.h>

/* Exported types ------------------------------------------------------------*/

 /**
  * @brief	Structure type to access the Nested Vectored Interrupt Controller (NVIC).
  */
typedef struct nvic_reg_t
{
	__io	uint32 	ISER[8];      	/**< Offset: 0x000 (R/W)  Interrupt Set Enable Registers */
			uint32 	RESERVED0[24];
	__io 	uint32 	ICER[8];      	/**< Offset: 0x080 (R/W) Interrupt Clear Enable Registers */
			uint32 	RESERVED1[24];
	__io 	uint32 	ISPR[8];      	/**< Offset: 0x100 (R/W)  Interrupt Set Pending Registers */
			uint32 	RESERVED2[24];
	__io 	uint32 	ICPR[8];      	/**< Offset: 0x180 (R/W)  Interrupt Clear Pending Registers */
			uint32 	RESERVED3[24];
	__io 	uint32 	IABR[8];		/**< Offset: 0x200 (R/W)  Interrupt Active bit Registers */
			uint32 	RESERVED4[56];
	__io 	uint08  IP[240];		/**< Offset: 0x300 (R/W)  Interrupt Priority Registers */
			uint32 	RESERVED5[644];
	__o		uint32	STIR;         	/**< Offset: 0xE00 ( /W)  Software Trigger Interrupt Registers */
 } nvic_reg_t;

/* Exported constants --------------------------------------------------------*/

#define NVIC_REG			((nvic_reg_t	*)NVIC_BASE      )   /*!< NVIC configuration struct           */

 /* Software Triggered Interrupt Register Definitions */
 #define NVIC_STIR_INTID_POS                 0                                          /*!< STIR: INTLINESNUM Position */
 #define NVIC_STIR_INTID_MSK                (0x1FFUL << NVIC_STIR_INTID_POS)            /*!< STIR: INTLINESNUM Mask */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_CORE_NVIC_REG_H_ */

/*****************************END OF FILE**************************************/
