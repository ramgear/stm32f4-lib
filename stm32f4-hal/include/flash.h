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

 typedef enum flash_sectors
 {
	 FLASH_SECTOR_0,
	 FLASH_SECTOR_1,
	 FLASH_SECTOR_2,
	 FLASH_SECTOR_3,
	 FLASH_SECTOR_4,
	 FLASH_SECTOR_5,
	 FLASH_SECTOR_6,
	 FLASH_SECTOR_7,
	 FLASH_SECTOR_8,
	 FLASH_SECTOR_9,
	 FLASH_SECTOR_10,
	 FLASH_SECTOR_11,
 } flash_sectors;

 typedef enum flash_psize
 {
	 FLASH_PSIZE_8,
	 FLASH_PSIZE_16,
	 FLASH_PSIZE_32,
	 FLASH_PSIZE_64,
 } flash_psize;

/* Exported constants --------------------------------------------------------*/
#define FLASH_REG			((flash_t	*)FLASH_R_BASE)

#define FLASH_KEY1			((uint32)0x45670123)
#define FLASH_KEY2			((uint32)0xCDEF89AB)
#define FLASH_OPT_KEY1		((uint32)0x08192A3B)
#define FLASH_OPT_KEY2		((uint32)0x4C5D6E7F)

#define FLASH_PSIZE_BYTE           ((uint32_t)0x00000000)
#define FLASH_PSIZE_HALF_WORD      ((uint32_t)0x00000100)
#define FLASH_PSIZE_WORD           ((uint32_t)0x00000200)
#define FLASH_PSIZE_DOUBLE_WORD    ((uint32_t)0x00000300)

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void
flash_opt_enable(flash_opt opt);

void
flash_opt_disable(flash_opt opt);

void
flash_set_latency(uint32 latency);

CPU_INL_FUNC boolean
flash_is_busy(void)
{
	return ((FLASH_REG->SR & FLASH_SR_BSY) != RESET);
}

CPU_INL_FUNC void
flash_wait_ready(void)
{
	while(flash_is_busy());
}

void
flash_lock(void);

void
flash_unlock(void);

uint32
flash_get_sector_address(flash_sectors sector);

void
flash_erase_sector(flash_sectors sector);

boolean
flash_write_block(uint32 address, uint32 *ptr, uint32 count);

#ifdef __cplusplus
}
#endif

#endif /* FLASH_H_ */

/*****************************END OF FILE**************************************/
