/**
 ******************************************************************************
 * @file	nvic.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	28-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INCLUDE_NVIC_H_
#define INCLUDE_NVIC_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <core/nvic.h>
#include <scb.h>

/* Exported types ------------------------------------------------------------*/
typedef IRQn_Type nvic_irq_num;

/* Exported constants --------------------------------------------------------*/

#define NVIC_REG			((nvic_t	*)NVIC_BASE      )   /*!< NVIC configuration struct           */

#define NVIC_IRQ_NUMBER		82

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

static inline void
nvic_irq_disable_all(void)
{
	NVIC_REG->ICER[0] = 0xFFFFFFFF;
	NVIC_REG->ICER[1] = 0xFFFFFFFF;
	NVIC_REG->ICER[2] = 0xFFFFFFFF;
}

static inline void
nvic_irq_enable(nvic_irq_num irq)
{
	NVIC_REG->ISER[irq >> 5] = (uint32)(1 << ((uint32)((sint32)irq) & (uint32)0x1F));
}

static inline void
nvic_irq_disable(nvic_irq_num irq)
{
	NVIC_REG->ICER[irq >> 5] = (1 << ((uint32)(irq) & 0x1F));
}

static inline void
nvic_set_priority_group(uint08 prigroup)
{
	uint32 reg_value;
	uint32 tmp = (prigroup & (uint32)0x07);               /* only values 0..7 are used          */

	reg_value  =  SCB_REG->AIRCR;                                                   /* read old register configuration    */
	reg_value &= ~(SCB_AIRCR_VECTKEY_MSK | SCB_AIRCR_PRIGROUP_MSK);             /* clear bits to change               */
	reg_value  =  (reg_value                                 |
	                ((uint32_t)0x5FA << SCB_AIRCR_VECTKEY_POS) |
	                (tmp << 8));                                     /* Insert write key and priorty group */
	SCB_REG->AIRCR =  reg_value;
}

static inline uint08
nvic_get_priority_group(void)
{
	return ((SCB_REG->AIRCR & SCB_AIRCR_PRIGROUP_MSK) >> SCB_AIRCR_PRIGROUP_POS);   /* read priority grouping field */
}

static inline void
nvic_set_vector_table(uint32 address, uint32 offset)
{
	SCB_REG->VTOR = address | offset;
}

static inline void
nvic_set_irq_priority(nvic_irq_num irq, uint08 priority)
{
    if (irq < 0) {
        /* This interrupt is in the system handler block */
        SCB_REG->SHP[((uint32)irq & 0xF) - 4] = (priority & 0xF) << 4;
    } else {
    	NVIC_REG->IP[irq] = (priority & 0xF) << 4;
    }
}

static inline void
nvic_reset(void)
{
    uint32 prigroup = SCB_REG->AIRCR & SCB_AIRCR_PRIGROUP_MSK;
    SCB_REG->AIRCR = SCB_AIRCR_VECTKEYSTAT_MSK | SCB_AIRCR_SYSRESETREQ_MSK | prigroup;

    asm volatile("dsb");
    while (1)
        ;
}

static inline void
nvic_init(uint32 address, uint32 offset)
{
    uint32 i;

    nvic_set_vector_table(address, offset);

    /* Lower priority level for all peripheral interrupts to lowest possible. */
    for (i = 0; i < NVIC_IRQ_NUMBER; i++) {
    	nvic_set_irq_priority((nvic_irq_num)i, 0xF);
    }

    /* Lower systick interrupt priority to lowest level */
    nvic_set_irq_priority(SysTick_IRQn, 0xF);
}

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_NVIC_H_ */

/*****************************END OF FILE**************************************/
