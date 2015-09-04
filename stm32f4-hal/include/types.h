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
 typedef bool					boolean;
 typedef unsigned 	char		uint08;		/* Unsigned  8 bit quantity                           */
 typedef signed		char		sint08;		/* Signed    8 bit quantity                           */
 typedef unsigned 	short		uint16;		/* Unsigned 16 bit quantity                           */
 typedef signed		short		sint16;		/* Signed   16 bit quantity                           */
 typedef unsigned 	long		uint32;		/* Unsigned 32 bit quantity                           */
 typedef signed		long		sint32;		/* Signed   32 bit quantity                           */
 typedef unsigned 	long long	uint64;		/* Unsigned 64 bit quantity                           */
 typedef signed		long long	sint64;		/* Signed   64 bit quantity                           */
 typedef float					float32;	/* Single precision floating point                    */
 typedef double					float64;	/* Double precision floating point                    */

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
