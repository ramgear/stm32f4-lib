/**
 ******************************************************************************
 * @file	bkpsram.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	07-Sep-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INCLUDE_BKPSRAM_H_
#define INCLUDE_BKPSRAM_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <cpu.h>

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
#define	BKPSRAM_SIZE		0x00001000
#define	BKPSRAM_BASE_ADDR	BKPSRAM_BASE

/* Exported macro ------------------------------------------------------------*/

#define	bkpsram_read_08(address)			(*(__io uint08 *) (BKPSRAM_BASE_ADDR + (address)))
#define	bkpsram_write_08(address, value)	(*(__io uint08 *) (BKPSRAM_BASE_ADDR + (address)) = (value))

#define	bkpsram_read_16(address)			(*(__io uint16 *) (BKPSRAM_BASE_ADDR + (address)))
#define	bkpsram_write_16(address, value)	(*(__io uint16 *) (BKPSRAM_BASE_ADDR + (address)) = (value))

#define	bkpsram_read_32(address)			(*(__io uint32 *) (BKPSRAM_BASE_ADDR + (address)))
#define	bkpsram_write_32(address, value)	(*(__io uint32 *) (BKPSRAM_BASE_ADDR + (address)) = (value))

#define	bkpsram_read_64(address)			(*(__io uint64 *) (BKPSRAM_BASE_ADDR + (address)))
#define	bkpsram_write_64(address, value)	(*(__io uint64 *) (BKPSRAM_BASE_ADDR + (address)) = (value))

#define	bkpsram_read_fp32(address)			(*(__io float32 *) (BKPSRAM_BASE_ADDR + (address)))
#define	bkpsram_write_fp32(address, value)	(*(__io float32 *) (BKPSRAM_BASE_ADDR + (address)) = (value))

#define	bkpsram_read_fp64(address)			(*(__io float64 *) (BKPSRAM_BASE_ADDR + (address)))
#define	bkpsram_write_fp64(address, value)	(*(__io float64 *) (BKPSRAM_BASE_ADDR + (address)) = (value))

/* Exported functions --------------------------------------------------------*/
void
bkpsram_init(void);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_BKPSRAM_H_ */

/*****************************END OF FILE**************************************/
