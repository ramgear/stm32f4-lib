/**
 ******************************************************************************
 * @file	flash.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	04-Sep-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

#include <flash.h>

void
flash_opt_enable(flash_opt opt)
{
	CPU_MOD_REG(FLASH_REG->ACR, opt, 1);
}

void
flash_opt_disable(flash_opt opt)
{
	CPU_MOD_REG(FLASH_REG->ACR, opt, 0);
}

void
flash_set_latency(uint32 latency)
{
	CPU_MOD_REG(FLASH_REG->ACR, FLASH_ACR_LATENCY, latency);
}

void
flash_lock(void)
{
	FLASH_REG->CR	|= FLASH_CR_LOCK;
}

void
flash_unlock(void)
{
	if((FLASH_REG->CR & FLASH_CR_LOCK) != RESET)
	{
	    /* Authorize the FLASH Registers access */
	    FLASH->KEYR = FLASH_KEY1;
	    FLASH->KEYR = FLASH_KEY2;
	}
}

uint32
flash_get_sector_address(flash_sectors sector)
{
	switch(sector)
	{
	case FLASH_SECTOR_0:
	case FLASH_SECTOR_1:
	case FLASH_SECTOR_2:
	case FLASH_SECTOR_3:
		return (FLASH_BASE + (sector * 0x4000));
	case FLASH_SECTOR_4:
		return (FLASH_BASE + 0x10000);
	case FLASH_SECTOR_5:
	case FLASH_SECTOR_6:
	case FLASH_SECTOR_7:
	case FLASH_SECTOR_8:
	case FLASH_SECTOR_9:
	case FLASH_SECTOR_10:
	case FLASH_SECTOR_11:
		return (FLASH_BASE + ((sector - 4) * 0x20000));
	default:
		return 0;
	}
}

void
flash_erase_sector(flash_sectors sector)
{
	/* Wait till ready */
	flash_wait_ready();

	CPU_MOD_REG(FLASH->CR, FLASH_CR_PSIZE, FLASH_PSIZE_WORD);

	FLASH->CR &= FLASH_CR_SER;
	FLASH->CR |= FLASH_CR_SER | (sector << CPU_POS_OF(FLASH_CR_SNB));
	FLASH->CR |= FLASH_CR_STRT;

	/* Wait till ready */
	flash_wait_ready();
}

boolean
flash_write_block(uint32 address, uint32 *ptr, uint32 count)
{
	/* Unlock */
	flash_unlock();

	/* Set program in word size */
	CPU_MOD_REG(FLASH->CR, FLASH_CR_PSIZE, FLASH_PSIZE_32);
	FLASH->CR	|= FLASH_CR_PG;

	while(count--)
	{
		*(__io uint32*)address = *ptr;

		/* Wait till ready */
		flash_wait_ready();

		/* Verify value */
		if(*(__io uint32*)address != *ptr)
		{
			/*Lock */
			flash_lock();

			return false;
		}
		++ptr;
		address += 4;
	}

	/*Lock */
	flash_lock();

	return true;
}

