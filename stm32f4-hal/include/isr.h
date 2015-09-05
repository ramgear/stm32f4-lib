/**
 * @file	isr.h
 * @brief	Framework header file.
 * @details	Framework header file.
 * @version	1.0
 * @date	Sep 5, 2015
 * @author	Eakkasit L.
 * @bug		No known bug
 * @warning	Improper use can crash your application
 * @copyright	GNU Public License.
 */

#ifndef INCLUDE_ISR_H_
#define INCLUDE_ISR_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <cpu.h>

 #define	ISR_DEF_ATT			__attribute__ ((weak, alias ("ISR_Default_Handler")))
 #define	ISR_IMP_ATT		__attribute__ ((section(".after_vectors"),used))
 #define	ISR_ATT_VECTOR	__attribute__ ((section(".isr_vector"),used))


 /*
  * ************************************************************************************************
  * Define weak ISR function
  * ************************************************************************************************
  */
 ISR_DEF_ATT void ISR_Reset_Handler 			(void);
 ISR_DEF_ATT void ISR_NMI_Handler 				(void);
 ISR_DEF_ATT void ISR_HardFault_Handler 		(void);
 ISR_DEF_ATT void ISR_MemManage_Handler 		(void);
 ISR_DEF_ATT void ISR_BusFault_Handler 			(void);
 ISR_DEF_ATT void ISR_UsageFault_Handler 		(void);
 ISR_DEF_ATT void ISR_SVC_Handler 				(void);
 ISR_DEF_ATT void ISR_DebugMon_Handler 			(void);
 ISR_DEF_ATT void ISR_PendSV_Handler 			(void);
 ISR_DEF_ATT void ISR_SysTick_Handler 			(void);
 ISR_DEF_ATT void ISR_WWDG_IRQHandler 			(void);
 ISR_DEF_ATT void ISR_PVD_IRQHandler 			(void);
 ISR_DEF_ATT void ISR_TAMP_STAMP_IRQHandler 	(void);
 ISR_DEF_ATT void ISR_RTC_WKUP_IRQHandler 		(void);
 ISR_DEF_ATT void ISR_FLASH_IRQHandler 			(void);
 ISR_DEF_ATT void ISR_RCC_IRQHandler 			(void);
 ISR_DEF_ATT void ISR_EXTI0_IRQHandler 			(void);
 ISR_DEF_ATT void ISR_EXTI1_IRQHandler 			(void);
 ISR_DEF_ATT void ISR_EXTI2_IRQHandler 			(void);
 ISR_DEF_ATT void ISR_EXTI3_IRQHandler 			(void);
 ISR_DEF_ATT void ISR_EXTI4_IRQHandler 			(void);
 ISR_DEF_ATT void ISR_DMA1_Stream0_IRQHandler 	(void);
 ISR_DEF_ATT void ISR_DMA1_Stream1_IRQHandler 	(void);
 ISR_DEF_ATT void ISR_DMA1_Stream2_IRQHandler 	(void);
 ISR_DEF_ATT void ISR_DMA1_Stream3_IRQHandler 	(void);
 ISR_DEF_ATT void ISR_DMA1_Stream4_IRQHandler 	(void);
 ISR_DEF_ATT void ISR_DMA1_Stream5_IRQHandler 	(void);
 ISR_DEF_ATT void ISR_DMA1_Stream6_IRQHandler 	(void);
 ISR_DEF_ATT void ISR_ADC_IRQHandler 			(void);
 ISR_DEF_ATT void ISR_CAN1_TX_IRQHandler 		(void);
 ISR_DEF_ATT void ISR_CAN1_RX0_IRQHandler 		(void);
 ISR_DEF_ATT void ISR_CAN1_RX1_IRQHandler 		(void);
 ISR_DEF_ATT void ISR_CAN1_SCE_IRQHandler 		(void);
 ISR_DEF_ATT void ISR_EXTI9_5_IRQHandler 		(void);
 ISR_DEF_ATT void ISR_TIM1_BRK_TIM9_IRQHandler 	(void);
 ISR_DEF_ATT void ISR_TIM1_UP_TIM10_IRQHandler 	(void);
 ISR_DEF_ATT void ISR_TIM1_TRG_COM_TIM11_IRQHandler (void);
 ISR_DEF_ATT void ISR_TIM1_CC_IRQHandler 		(void);
 ISR_DEF_ATT void ISR_TIM2_IRQHandler 			(void);
 ISR_DEF_ATT void ISR_TIM3_IRQHandler 			(void);
 ISR_DEF_ATT void ISR_TIM4_IRQHandler 			(void);
 ISR_DEF_ATT void ISR_I2C1_EV_IRQHandler 		(void);
 ISR_DEF_ATT void ISR_I2C1_ER_IRQHandler 		(void);
 ISR_DEF_ATT void ISR_I2C2_EV_IRQHandler 		(void);
 ISR_DEF_ATT void ISR_I2C2_ER_IRQHandler 		(void);
 ISR_DEF_ATT void ISR_SPI1_IRQHandler 			(void);
 ISR_DEF_ATT void ISR_SPI2_IRQHandler 			(void);
 ISR_DEF_ATT void ISR_USART1_IRQHandler 		(void);
 ISR_DEF_ATT void ISR_USART2_IRQHandler 		(void);
 ISR_DEF_ATT void ISR_USART3_IRQHandler 		(void);
 ISR_DEF_ATT void ISR_EXTI15_10_IRQHandler 		(void);
 ISR_DEF_ATT void ISR_RTC_Alarm_IRQHandler 		(void);
 ISR_DEF_ATT void ISR_OTG_FS_WKUP_IRQHandler 	(void);
 ISR_DEF_ATT void ISR_TIM8_BRK_TIM12_IRQHandler (void);
 ISR_DEF_ATT void ISR_TIM8_UP_TIM13_IRQHandler 	(void);
 ISR_DEF_ATT void ISR_TIM8_TRG_COM_TIM14_IRQHandler (void);
 ISR_DEF_ATT void ISR_TIM8_CC_IRQHandler 		(void);
 ISR_DEF_ATT void ISR_DMA1_Stream7_IRQHandler 	(void);
 ISR_DEF_ATT void ISR_FSMC_IRQHandler 			(void);
 ISR_DEF_ATT void ISR_SDIO_IRQHandler 			(void);
 ISR_DEF_ATT void ISR_TIM5_IRQHandler 			(void);
 ISR_DEF_ATT void ISR_SPI3_IRQHandler 			(void);
 ISR_DEF_ATT void ISR_UART4_IRQHandler 			(void);
 ISR_DEF_ATT void ISR_UART5_IRQHandler 			(void);
 ISR_DEF_ATT void ISR_TIM6_DAC_IRQHandler 		(void);
 ISR_DEF_ATT void ISR_TIM7_IRQHandler 			(void);
 ISR_DEF_ATT void ISR_DMA2_Stream0_IRQHandler 	(void);
 ISR_DEF_ATT void ISR_DMA2_Stream1_IRQHandler 	(void);
 ISR_DEF_ATT void ISR_DMA2_Stream2_IRQHandler 	(void);
 ISR_DEF_ATT void ISR_DMA2_Stream3_IRQHandler 	(void);
 ISR_DEF_ATT void ISR_DMA2_Stream4_IRQHandler 	(void);
 ISR_DEF_ATT void ISR_ETH_IRQHandler 			(void);
 ISR_DEF_ATT void ISR_ETH_WKUP_IRQHandler 		(void);
 ISR_DEF_ATT void ISR_CAN2_TX_IRQHandler 		(void);
 ISR_DEF_ATT void ISR_CAN2_RX0_IRQHandler 		(void);
 ISR_DEF_ATT void ISR_CAN2_RX1_IRQHandler 		(void);
 ISR_DEF_ATT void ISR_CAN2_SCE_IRQHandler 		(void);
 ISR_DEF_ATT void ISR_OTG_FS_IRQHandler 		(void);
 ISR_DEF_ATT void ISR_DMA2_Stream5_IRQHandler 	(void);
 ISR_DEF_ATT void ISR_DMA2_Stream6_IRQHandler 	(void);
 ISR_DEF_ATT void ISR_DMA2_Stream7_IRQHandler 	(void);
 ISR_DEF_ATT void ISR_USART6_IRQHandler 		(void);
 ISR_DEF_ATT void ISR_I2C3_EV_IRQHandler 		(void);
 ISR_DEF_ATT void ISR_I2C3_ER_IRQHandler 		(void);
 ISR_DEF_ATT void ISR_OTG_HS_EP1_OUT_IRQHandler (void);
 ISR_DEF_ATT void ISR_OTG_HS_EP1_IN_IRQHandler 	(void);
 ISR_DEF_ATT void ISR_OTG_HS_WKUP_IRQHandler 	(void);
 ISR_DEF_ATT void ISR_OTG_HS_IRQHandler 		(void);
 ISR_DEF_ATT void ISR_DCMI_IRQHandler 			(void);
 ISR_DEF_ATT void ISR_CRYP_IRQHandler 			(void);
 ISR_DEF_ATT void ISR_HASH_RNG_IRQHandler		(void);
 ISR_DEF_ATT void ISR_FPU_IRQHandler 			(void);


 void
 __attribute__((weak))
 ISR_Default_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_ISR_H_ */
