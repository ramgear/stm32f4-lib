/**
 * @file	isr_vectors.c
 * @brief	Framework header file.
 * @details	Framework header file.
 * @version	1.0
 * @date	Aug 23, 2015
 * @author	Eakkasit L.
 * @bug		No known bug
 * @warning	Improper use can crash your application
 * @copyright	GNU Public License.
 */

#include <isr.h>

extern unsigned int _estack;

typedef void
(* const pHandler)(void);

/**
 * ISR Vectors table.
 */
ISR_ATT_VECTOR
pHandler	isr_vector_table[] =
{
       /* ISR Core Level - Cortex-M4 */
       (pHandler) &_estack,                      // The initial stack pointer
       ISR_Reset_Handler,                 	// The reset handler
       ISR_NMI_Handler,                    	// The NMI handler
       ISR_HardFault_Handler,                // The hard fault handler
       ISR_MemManage_Handler,               	// The MPU fault handler
       ISR_BusFault_Handler,            		// The bus fault handler
       ISR_UsageFault_Handler,          		// The usage fault handler
	   0,                                        // Reserved
	   0,                                        // Reserved
	   0,                                        // Reserved
	   0,                                        // Reserved
	   ISR_SVC_Handler,                      // SVCall handler
	   ISR_DebugMon_Handler,             	// Debug monitor handler
	   0,                                        // Reserved
       ISR_PendSV_Handler,                  	// The PendSV handler
       ISR_SysTick_Handler,       			// The SysTick handler

       /* ISR Chip Level - STM32F4xx */
       ISR_WWDG_IRQHandler,        			// Window WatchDog
       ISR_PVD_IRQHandler, 					// PVD through EXTI Line detection
       ISR_TAMP_STAMP_IRQHandler,  			// Tamper and TimeStamps through the EXTI line
       ISR_RTC_WKUP_IRQHandler,    			// RTC Wakeup through the EXTI line
       ISR_FLASH_IRQHandler,       			// FLASH
       ISR_RCC_IRQHandler, 					// RCC
       ISR_EXTI0_IRQHandler,       			// EXTI Line0
       ISR_EXTI1_IRQHandler,       			// EXTI Line1
       ISR_EXTI2_IRQHandler,       			// EXTI Line2
       ISR_EXTI3_IRQHandler,       			// EXTI Line3
       ISR_EXTI4_IRQHandler,       			// EXTI Line4
       ISR_DMA1_Stream0_IRQHandler,        	// DMA1 Stream 0
       ISR_DMA1_Stream1_IRQHandler,        	// DMA1 Stream 1
       ISR_DMA1_Stream2_IRQHandler,        	// DMA1 Stream 2
       ISR_DMA1_Stream3_IRQHandler,        	// DMA1 Stream 3
       ISR_DMA1_Stream4_IRQHandler,        	// DMA1 Stream 4
       ISR_DMA1_Stream5_IRQHandler,        	// DMA1 Stream 5
       ISR_DMA1_Stream6_IRQHandler,        	// DMA1 Stream 6
       ISR_ADC_IRQHandler, 					// ADC1

       /* ISR Chip Level - STM32F407xx */
       ISR_CAN1_TX_IRQHandler,     			// CAN1 TX
       ISR_CAN1_RX0_IRQHandler,    			// CAN1 RX0
       ISR_CAN1_RX1_IRQHandler,    			// CAN1 RX1
       ISR_CAN1_SCE_IRQHandler,    			// CAN1 SCE
       ISR_EXTI9_5_IRQHandler,     			// External Line[9:5]s
       ISR_TIM1_BRK_TIM9_IRQHandler,       	// TIM1 Break and TIM9
       ISR_TIM1_UP_TIM10_IRQHandler,       	// TIM1 Update and TIM10
       ISR_TIM1_TRG_COM_TIM11_IRQHandler,  	// TIM1 Trigger and Commutation and TIM11
       ISR_TIM1_CC_IRQHandler,     			// TIM1 Capture Compare
       ISR_TIM2_IRQHandler,        			// TIM2
       ISR_TIM3_IRQHandler,        			// TIM3
       ISR_TIM4_IRQHandler,        			// TIM4
       ISR_I2C1_EV_IRQHandler,     			// I2C1 Event
       ISR_I2C1_ER_IRQHandler,     			// I2C1 Error
       ISR_I2C2_EV_IRQHandler,     			// I2C2 Event
       ISR_I2C2_ER_IRQHandler,     			// I2C2 Error
       ISR_SPI1_IRQHandler,        			// SPI1
       ISR_SPI2_IRQHandler,        			// SPI2
       ISR_USART1_IRQHandler,      			// USART1
       ISR_USART2_IRQHandler,      			// USART2
       ISR_USART3_IRQHandler,      			// USART3
       ISR_EXTI15_10_IRQHandler,   			// External Line[15:10]s
       ISR_RTC_Alarm_IRQHandler,   			// RTC Alarm (A and B) through EXTI Line
       ISR_OTG_FS_WKUP_IRQHandler, 			// USB OTG FS Wakeup through EXTI line
       ISR_TIM8_BRK_TIM12_IRQHandler,     	// TIM8 Break and TIM12
       ISR_TIM8_UP_TIM13_IRQHandler,       	// TIM8 Update and TIM13
       ISR_TIM8_TRG_COM_TIM14_IRQHandler,  	// TIM8 Trigger and Commutation and TIM14
       ISR_TIM8_CC_IRQHandler,     			// TIM8 Capture Compare
       ISR_DMA1_Stream7_IRQHandler,        	// DMA1 Stream7
       ISR_FSMC_IRQHandler,        			// FSMC
       ISR_SDIO_IRQHandler,        			// SDIO
       ISR_TIM5_IRQHandler,        			// TIM5
       ISR_SPI3_IRQHandler,        			// SPI3
       ISR_UART4_IRQHandler,      	 		// UART4
       ISR_UART5_IRQHandler,       			// UART5
       ISR_TIM6_DAC_IRQHandler,    			// TIM6 and DAC1&2 underrun errors
       ISR_TIM7_IRQHandler,        			// TIM7
       ISR_DMA2_Stream0_IRQHandler,        	// DMA2 Stream 0
       ISR_DMA2_Stream1_IRQHandler,        	// DMA2 Stream 1
       ISR_DMA2_Stream2_IRQHandler,        	// DMA2 Stream 2
       ISR_DMA2_Stream3_IRQHandler,        	// DMA2 Stream 3
       ISR_DMA2_Stream4_IRQHandler,        	// DMA2 Stream 4
       ISR_ETH_IRQHandler, 					// Ethernet
       ISR_ETH_WKUP_IRQHandler,    			// Ethernet Wakeup through EXTI line
       ISR_CAN2_TX_IRQHandler,     			// CAN2 TX
       ISR_CAN2_RX0_IRQHandler,    			// CAN2 RX0
       ISR_CAN2_RX1_IRQHandler,    			// CAN2 RX1
       ISR_CAN2_SCE_IRQHandler,    			// CAN2 SCE
       ISR_OTG_FS_IRQHandler,      			// USB OTG FS
       ISR_DMA2_Stream5_IRQHandler,        	// DMA2 Stream 5
       ISR_DMA2_Stream6_IRQHandler,        	// DMA2 Stream 6
       ISR_DMA2_Stream7_IRQHandler,        	// DMA2 Stream 7
       ISR_USART6_IRQHandler,      			// USART6
       ISR_I2C3_EV_IRQHandler,     			// I2C3 event
       ISR_I2C3_ER_IRQHandler,     			// I2C3 error
       ISR_OTG_HS_EP1_OUT_IRQHandler,      	// USB OTG HS End Point 1 Out
       ISR_OTG_HS_EP1_IN_IRQHandler,       	// USB OTG HS End Point 1 In
       ISR_OTG_HS_WKUP_IRQHandler, 			// USB OTG HS Wakeup through EXTI
       ISR_OTG_HS_IRQHandler,      			// USB OTG HS
       ISR_DCMI_IRQHandler,        			// DCMI
       ISR_CRYP_IRQHandler,      			// CRYP crypto
       ISR_HASH_RNG_IRQHandler,    			// Hash and Rng
       ISR_FPU_IRQHandler 					// FPU
};

ISR_IMP_ATT
void ISR_Default_Handler(void)
{
	trace_printf ("[ISR_Default_Handler]\n");

#if defined(DEBUG)
	asm volatile ("bkpt 0");
#endif

	while (1);
}
