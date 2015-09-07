/**
 * @file	scb.c
 * @brief	Framework header file.
 * @details	Framework header file.
 * @version	1.0
 * @date	Sep 5, 2015
 * @author	Eakkasit L.
 * @bug		No known bug
 * @warning	Improper use can crash your application
 * @copyright	GNU Public License.
 */

#include <scb.h>
#include <bkpsram.h>

void
scb_init(void)
{
	/* FPU settings ------------------------------------------------------------*/
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
	SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */
#endif
}

void
scb_set_vector(uint32 addr)
{
	SCB_REG->VTOR = addr;
}


void
scb_reset(void)
{
	CPU_DSB();
	SCB_REG->AIRCR =	((0x5FA << SCB_AIRCR_VECTKEY_POS)      |
            			(SCB_REG->AIRCR & SCB_AIRCR_PRIGROUP_MSK) |
						SCB_AIRCR_SYSRESETREQ_MSK);                   /* Keep priority group unchanged */
	CPU_DSB();

	/* wait until reset */
	while(1);
}

