/**
 ******************************************************************************
 * @file	cpu.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	28-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INCLUDE_CPU_H_
#define INCLUDE_CPU_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <types.h>
#if defined(STM32F407xx)
#include <stm32f407xx.h>
#elif defined(STM32f401xx)
#include <stm32f401xx.h>
#elif defined(STM32f429xx)
#include <stm32f429xx.h>
#else
#error "Please define CPU to use this libraries!"
#endif

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
 /* Memory mapping of Cortex-M4 Hardware */
 #define SCS_BASE            (0xE000E000UL)                            /*!< System Control Space Base Address  */
 #define SYSTICK_BASE        (SCS_BASE +  0x0010UL)                    /*!< SysTick Base Address               */
 #define NVIC_BASE           (SCS_BASE +  0x0100UL)                    /*!< NVIC Base Address                  */
 #define SCB_BASE            (SCS_BASE +  0x0D00UL)                    /*!< System Control Block Base Address  */

/* Exported macro ------------------------------------------------------------*/
#define CPU_INL_FUNC	__attribute__((always_inline)) static inline

#define	CPU_POS_OF(mask)			(CPU_CTZ(mask))
#define	CPU_MOD_VAL(mask,val)		(((val) << CPU_POS_OF(mask)) & mask)
#define	CPU_MOD_REG(reg,mask,val)	((reg) = (((reg) & ~(mask)) | ((val) << CPU_POS_OF(mask))))
#define	CPU_GET_VAL(reg,mask)		(((reg) & (mask)) >> CPU_POS_OF(mask))

#define CPU_SET_BIT(reg,mask)		((reg) |= (mask))
#define CPU_CLR_BIT(reg,mask)		((reg) &= ~(mask))

#define	CPU_SR_ALLOC			uint32 __primask;
#define	CPU_ENTER_CRITICAL		\
	__primask = CPU_GetPRIMASK();	\
	CPU_DisableIRQ();

#define	CPU_EXIT_CRITICAL		CPU_SetPRIMASK(__primask);

/* Exported functions --------------------------------------------------------*/

 /**
  * @brief	Disable IRQ Interrupts
  * 		This function disables IRQ interrupts by setting the I-bit in the CPSR.
  * 		Can only be executed in Privileged modes.
  */
 CPU_INL_FUNC
 void CPU_DisableIRQ(void)
 {
	 __asm volatile ("CPSID I");
 }

 /**
  * @brief	Enable IRQ Interrupts.
  * 		This function enables IRQ interrupts by clearing the I-bit in the CPSR.
  * 		Can only be executed in Privileged modes.
  */
 CPU_INL_FUNC
 void CPU_EnableIRQ(void)
 {
	 __asm volatile ("CPSIE I");
 }

 /**
  * @brief	Wait for interrupt.
  */
 CPU_INL_FUNC
 void CPU_WFI(void)
 {
	 __asm volatile ("WFI");
 }

 /**
  * @brief	Wait for event.
  */
 CPU_INL_FUNC
 void CPU_WFE(void)
 {
	 __asm volatile ("WFE");
 }

 /**
  * @brief	Send Event.
  */
 CPU_INL_FUNC
 void CPU_SEV(void)
 {
	 __asm volatile ("SEV");
 }

 /**
  * @brief	Instruction Synchronization Barrier.
  */
 CPU_INL_FUNC
 void CPU_ISB(void)
 {
	 __asm volatile ("DSB");
 }

 /**
  * @brief	Data Synchronization Barrier.
  */
 CPU_INL_FUNC
 void CPU_DSB(void)
 {
	 __asm volatile ("DSB");
 }

 /**
  * @brief	Data Memory Barrier.
  */
 CPU_INL_FUNC
 void CPU_DMB(void)
 {
	 __asm volatile ("DMB");
 }

 /**
  * @brief	Supervisor call.
  */
 CPU_INL_FUNC
 void CPU_SVC(void)
 {
	 __asm volatile ("SVC 0x01");
 }

 /**
  * @brief	Get Control Register.
  * 		This function returns the content of the Control Register.
  * @retval	Control Register value.
  */
 CPU_INL_FUNC
 uint32 CPU_GetCONTROL(void)
 {
	 register uint32 result;

	__asm volatile ("MRS %0, control" : "+r" (result) );

	return result;
 }

 /**
  * @brief	Set CONTROL register.
  * 		This function writes the given value to the Control Register.
  * @param [in]    control  Control Register value to set
  */
 CPU_INL_FUNC
 void CPU_SetCONTROL(register uint32 control)
 {
 	__asm volatile ("MSR control, %0" : : "r" (control) );
 }

 /**
  * @brief	Get Process Stack Pointer (PSP).
  * 		This function returns the current value of the Process Stack Pointer (PSP).
  * @retval	Return top of process stack pointer.
  */
 CPU_INL_FUNC
 uint32 CPU_GetPSP(void)
 {
	  register uint32 result;

	  __asm volatile ("MRS %0, psp"  : "=r" (result) );

	  return(result);
 }

 /**
  * @brief	Set Process Stack Pointer (PSP).
  * 		This function assigns the given value to the Process Stack Pointer (PSP).
  * @param [in]    topOfProcStack  Process Stack Pointer value to set
  */
 CPU_INL_FUNC
 void CPU_SetPSP(register uint32 topOfProcStack)
 {
 	__asm volatile ("MSR psp, %0" : : "r" (topOfProcStack) );
 }

 /**
  * @brief	Get Process Stack Pointer (MSP).
  * 		This function returns the current value of the Main Stack Pointer (MSP).
  *
  * @retval	MSP Register value.
  */
 CPU_INL_FUNC
 uint32 CPU_GetMSP(void)
 {
	  register uint32 result;

	  __asm volatile ("MRS %0, msp"  : "=r" (result) );

	  return(result);
 }

 /**
  * @brief	Set Process Stack Pointer (MSP).
  * 		This function assigns the given value to the Main Stack Pointer (MSP).
  * @param [in]    topOfProcStack  Main Stack Pointer value to set
  */
 CPU_INL_FUNC
 void CPU_SetMSP(register uint32 topOfProcStack)
 {
 	__asm volatile ("MSR msp, %0" : : "r" (topOfProcStack) );
 }

 /**
  * @brief	Get IPSR Register.
  * 		This function returns the content of the IPSR Register.
  *
  * @retval	IPSR Register value.
  */
 CPU_INL_FUNC
 uint32 CPU_GetIPSR(void)
 {
	  register uint32 result;

	  __asm volatile ("MRS %0, ipsr"  : "=r" (result) );

	  return(result);
 }

 /**
  * @brief	Get APSR Register.
  * 		This function returns the content of the APSR Register.
  *
  * @retval	APSR Register value.
  */
 CPU_INL_FUNC
 uint32 CPU_GetAPSR(void)
 {
	  register uint32 result;

	  __asm volatile ("MRS %0, apsr"  : "=r" (result) );

	  return(result);
 }

 /**
  * @brief	Get xPSR Register.
  * 		This function returns the content of the xPSR Register.
  *
  * @retval	xPSR Register value.
  */
 CPU_INL_FUNC
 uint32 CPU_GetxPSR(void)
 {
	  register uint32 result;

	  __asm volatile ("MRS %0, xpsr"  : "=r" (result) );

	  return(result);
 }

 /**
  * @brief	Get Priority Mask (PRIMASK).
  * 		This function returns the current state of the priority mask bit from the Priority Mask Register (PRIMASK).
  *
  * @retval	Priority Mask value.
  */
 CPU_INL_FUNC
 uint32 CPU_GetPRIMASK(void)
 {
	  register uint32 result;

	  __asm volatile ("MRS %0, primask"  : "=r" (result) );

	  return(result);
 }

 /**
  * @brief	Set Priority Mask Register (PRIMASK).
  * 		This function assigns the given value to the Priority Mask Register (PRIMASK).
  *
  * @param [in]    priMask  Priority Mask value
  */
 CPU_INL_FUNC
 void CPU_SetPRIMASK(register uint32 priMask)
 {
 	__asm volatile ("MSR primask, %0" : : "r" (priMask) );
 }

 /**
  * @brief	Set Priority Mask Register (PRIMASK).
  * 		This function assigns the given value to the Priority Mask Register (PRIMASK).
  *
  * @param [in]    priMask  Priority Mask value
  */
 CPU_INL_FUNC
 void CPU_BX(register uint32 addr)
 {
 	__asm volatile ("BX %0" : : "r" (addr) );
 }

 CPU_INL_FUNC
 uint32 CPU_CLZ(register uint32 data)
 {
	  __asm volatile ("CLZ %0, %0"  : "+r" (data) );

	  return(data);
 }

 CPU_INL_FUNC
 uint32 CPU_CTZ(register uint32 data)
 {
	  __asm volatile (
			  "RBIT	%0, %0	\n"
			  "CLZ	%0, %0	\n"
			  : "+r" (data)
				);

	  return(data);
 }

 void
 cpu_init_early(void);

 void
 cpu_init(void);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_CPU_H_ */

/*****************************END OF FILE**************************************/
