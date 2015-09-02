/**
 ******************************************************************************
 * @file	types.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	28-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INCLUDE_TYPES_H_
#define INCLUDE_TYPES_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <defines.h>

/* Exported types ------------------------------------------------------------*/
 typedef bool		boolean;
 typedef uint8_t	uint08;		/* Unsigned  8 bit quantity                           */
 typedef int8_t		sint08;		/* Signed    8 bit quantity                           */
 typedef uint16_t	uint16;		/* Unsigned 16 bit quantity                           */
 typedef int16_t	sint16;		/* Signed   16 bit quantity                           */
 typedef uint32_t	uint32;		/* Unsigned 32 bit quantity                           */
 typedef int32_t	sint32;		/* Signed   32 bit quantity                           */
 typedef float		float32;	/* Single precision floating point                    */
 typedef double		float64;	/* Double precision floating point                    */

 typedef __io	uint32	reg32;

 typedef void		(*voidFuncPtr)(void);
 typedef void		(*voidArgFuncPtr)(void *);

 typedef voidArgFuncPtr	irq_callback_t;

/* Exported constants --------------------------------------------------------*/

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

#endif /* INCLUDE_TYPES_H_ */

/*****************************END OF FILE**************************************/
