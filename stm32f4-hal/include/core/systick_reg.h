/**
 ******************************************************************************
 * @file	SYSTICK_reg.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	28-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INCLUDE_CORE_SYSTICK_REG_H_
#define INCLUDE_CORE_SYSTICK_REG_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <cpu.h>

/* Exported types ------------------------------------------------------------*/

 /**
  * @brief  Structure type to access the System Timer (SysTick).
  */
 typedef struct
 {
   __io uint32 CTRL;                    /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
   __io uint32 LOAD;                    /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register       */
   __io uint32 VAL;                     /*!< Offset: 0x008 (R/W)  SysTick Current Value Register      */
   __i  uint32 CALIB;                   /*!< Offset: 0x00C (R/ )  SysTick Calibration Register        */
 } systick_reg_t;

/* Exported constants --------------------------------------------------------*/

#define SYSTICK_REG			((systick_reg_t	*)SYSTICK_BASE)		/*!< SysTick configuration struct           */

 /* SysTick Control / Status Register Definitions */
 #define SYSTICK_CTRL_COUNTFLAG_POS         16                                             /*!< SysTick CTRL: COUNTFLAG Position */
 #define SYSTICK_CTRL_COUNTFLAG_MSK         (1UL << SYSTICK_CTRL_COUNTFLAG_POS)            /*!< SysTick CTRL: COUNTFLAG Mask */

 #define SYSTICK_CTRL_CLKSOURCE_POS          2                                             /*!< SysTick CTRL: CLKSOURCE Position */
 #define SYSTICK_CTRL_CLKSOURCE_MSK         (1UL << SYSTICK_CTRL_CLKSOURCE_POS)            /*!< SysTick CTRL: CLKSOURCE Mask */

 #define SYSTICK_CTRL_TICKINT_POS            1                                             /*!< SysTick CTRL: TICKINT Position */
 #define SYSTICK_CTRL_TICKINT_MSK           (1UL << SYSTICK_CTRL_TICKINT_POS)              /*!< SysTick CTRL: TICKINT Mask */

 #define SYSTICK_CTRL_ENABLE_POS             0                                             /*!< SysTick CTRL: ENABLE Position */
 #define SYSTICK_CTRL_ENABLE_MSK            (1UL << SYSTICK_CTRL_ENABLE_POS)               /*!< SysTick CTRL: ENABLE Mask */

 /* SysTick Reload Register Definitions */
 #define SYSTICK_LOAD_RELOAD_POS             0                                             /*!< SysTick LOAD: RELOAD Position */
 #define SYSTICK_LOAD_RELOAD_MSK            (0xFFFFFFUL << SYSTICK_LOAD_RELOAD_POS)        /*!< SysTick LOAD: RELOAD Mask */

 /* SysTick Current Register Definitions */
 #define SYSTICK_VAL_CURRENT_POS             0                                             /*!< SysTick VAL: CURRENT Position */
 #define SYSTICK_VAL_CURRENT_MSK            (0xFFFFFFUL << SYSTICK_VAL_CURRENT_POS)        /*!< SysTick VAL: CURRENT Mask */

 /* SysTick Calibration Register Definitions */
 #define SYSTICK_CALIB_NOREF_POS            31                                             /*!< SysTick CALIB: NOREF Position */
 #define SYSTICK_CALIB_NOREF_MSK            (1UL << SYSTICK_CALIB_NOREF_POS)               /*!< SysTick CALIB: NOREF Mask */

 #define SYSTICK_CALIB_SKEW_POS             30                                             /*!< SysTick CALIB: SKEW Position */
 #define SYSTICK_CALIB_SKEW_MSK             (1UL << SYSTICK_CALIB_SKEW_POS)                /*!< SysTick CALIB: SKEW Mask */

 #define SYSTICK_CALIB_TENMS_POS             0                                             /*!< SysTick CALIB: TENMS Position */
 #define SYSTICK_CALIB_TENMS_MSK            (0xFFFFFFUL << SYSTICK_VAL_CURRENT_POS)        /*!< SysTick CALIB: TENMS Mask */

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

#endif /* INCLUDE_CORE_SYSTICK_REG_H_ */

/*****************************END OF FILE**************************************/
