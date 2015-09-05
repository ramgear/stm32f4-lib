/**
 ******************************************************************************
 * @file	scb_reg.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	28-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INCLUDE_CORE_SCB_H_
#define INCLUDE_CORE_SCB_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <cpu.h>

/* Exported types ------------------------------------------------------------*/

 /**
  * @brief  Structure type to access the System Control Block (SCB).
  */
 typedef struct scb_t
 {
   __i  uint32 CPUID;                   /*!< Offset: 0x000 (R/ )  CPUID Base Register                                   */
   __io uint32 ICSR;                    /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register                  */
   __io uint32 VTOR;                    /*!< Offset: 0x008 (R/W)  Vector Table Offset Register                          */
   __io uint32 AIRCR;                   /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register      */
   __io uint32 SCR;                     /*!< Offset: 0x010 (R/W)  System Control Register                               */
   __io uint32 CCR;                     /*!< Offset: 0x014 (R/W)  Configuration Control Register                        */
   __io uint08 SHP[12];                 /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
   __io uint32 SHCSR;                   /*!< Offset: 0x024 (R/W)  System Handler Control and State Register             */
   __io uint32 CFSR;                    /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register                    */
   __io uint32 HFSR;                    /*!< Offset: 0x02C (R/W)  HardFault Status Register                             */
   __io uint32 DFSR;                    /*!< Offset: 0x030 (R/W)  Debug Fault Status Register                           */
   __io uint32 MMFAR;                   /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register                      */
   __io uint32 BFAR;                    /*!< Offset: 0x038 (R/W)  BusFault Address Register                             */
   __io uint32 AFSR;                    /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register                       */
   __i  uint32 PFR[2];                  /*!< Offset: 0x040 (R/ )  Processor Feature Register                            */
   __i  uint32 DFR;                     /*!< Offset: 0x048 (R/ )  Debug Feature Register                                */
   __i  uint32 ADR;                     /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register                            */
   __i  uint32 MMFR[4];                 /*!< Offset: 0x050 (R/ )  Memory Model Feature Register                         */
   __i  uint32 ISAR[5];                 /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register                   */
        uint32 RESERVED0[5];
   __io uint32 CPACR;                   /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register                   */
 } scb_t;

/* Exported constants --------------------------------------------------------*/

 /* SCB CPUID Register Definitions */
 #define SCB_CPUID_IMPLEMENTER_POS          24                                             /*!< SCB CPUID: IMPLEMENTER Position */
 #define SCB_CPUID_IMPLEMENTER_MSK          (0xFFUL << SCB_CPUID_IMPLEMENTER_POS)          /*!< SCB CPUID: IMPLEMENTER Mask */

 #define SCB_CPUID_VARIANT_POS              20                                             /*!< SCB CPUID: VARIANT Position */
 #define SCB_CPUID_VARIANT_MSK              (0xFUL << SCB_CPUID_VARIANT_POS)               /*!< SCB CPUID: VARIANT Mask */

 #define SCB_CPUID_ARCHITECTURE_POS         16                                             /*!< SCB CPUID: ARCHITECTURE Position */
 #define SCB_CPUID_ARCHITECTURE_MSK         (0xFUL << SCB_CPUID_ARCHITECTURE_POS)          /*!< SCB CPUID: ARCHITECTURE Mask */

 #define SCB_CPUID_PARTNO_POS                4                                             /*!< SCB CPUID: PARTNO Position */
 #define SCB_CPUID_PARTNO_MSK               (0xFFFUL << SCB_CPUID_PARTNO_POS)              /*!< SCB CPUID: PARTNO Mask */

 #define SCB_CPUID_REVISION_POS              0                                             /*!< SCB CPUID: REVISION Position */
 #define SCB_CPUID_REVISION_MSK             (0xFUL << SCB_CPUID_REVISION_POS)              /*!< SCB CPUID: REVISION Mask */

 /* SCB Interrupt Control State Register Definitions */
 #define SCB_ICSR_NMIPENDSET_POS            31                                             /*!< SCB ICSR: NMIPENDSET Position */
 #define SCB_ICSR_NMIPENDSET_MSK            (1UL << SCB_ICSR_NMIPENDSET_POS)               /*!< SCB ICSR: NMIPENDSET Mask */

 #define SCB_ICSR_PENDSVSET_POS             28                                             /*!< SCB ICSR: PENDSVSET Position */
 #define SCB_ICSR_PENDSVSET_MSK             (1UL << SCB_ICSR_PENDSVSET_POS)                /*!< SCB ICSR: PENDSVSET Mask */

 #define SCB_ICSR_PENDSVCLR_POS             27                                             /*!< SCB ICSR: PENDSVCLR Position */
 #define SCB_ICSR_PENDSVCLR_MSK             (1UL << SCB_ICSR_PENDSVCLR_POS)                /*!< SCB ICSR: PENDSVCLR Mask */

 #define SCB_ICSR_PENDSTSET_POS             26                                             /*!< SCB ICSR: PENDSTSET Position */
 #define SCB_ICSR_PENDSTSET_MSK             (1UL << SCB_ICSR_PENDSTSET_POS)                /*!< SCB ICSR: PENDSTSET Mask */

 #define SCB_ICSR_PENDSTCLR_POS             25                                             /*!< SCB ICSR: PENDSTCLR Position */
 #define SCB_ICSR_PENDSTCLR_MSK             (1UL << SCB_ICSR_PENDSTCLR_POS)                /*!< SCB ICSR: PENDSTCLR Mask */

 #define SCB_ICSR_ISRPREEMPT_POS            23                                             /*!< SCB ICSR: ISRPREEMPT Position */
 #define SCB_ICSR_ISRPREEMPT_MSK            (1UL << SCB_ICSR_ISRPREEMPT_POS)               /*!< SCB ICSR: ISRPREEMPT Mask */

 #define SCB_ICSR_ISRPENDING_POS            22                                             /*!< SCB ICSR: ISRPENDING Position */
 #define SCB_ICSR_ISRPENDING_MSK            (1UL << SCB_ICSR_ISRPENDING_POS)               /*!< SCB ICSR: ISRPENDING Mask */

 #define SCB_ICSR_VECTPENDING_POS           12                                             /*!< SCB ICSR: VECTPENDING Position */
 #define SCB_ICSR_VECTPENDING_MSK           (0x1FFUL << SCB_ICSR_VECTPENDING_POS)          /*!< SCB ICSR: VECTPENDING Mask */

 #define SCB_ICSR_RETTOBASE_POS             11                                             /*!< SCB ICSR: RETTOBASE Position */
 #define SCB_ICSR_RETTOBASE_MSK             (1UL << SCB_ICSR_RETTOBASE_POS)                /*!< SCB ICSR: RETTOBASE Mask */

 #define SCB_ICSR_VECTACTIVE_POS             0                                             /*!< SCB ICSR: VECTACTIVE Position */
 #define SCB_ICSR_VECTACTIVE_MSK            (0x1FFUL << SCB_ICSR_VECTACTIVE_POS)           /*!< SCB ICSR: VECTACTIVE Mask */

 /* SCB Vector Table Offset Register Definitions */
 #define SCB_VTOR_TBLOFF_POS                 7                                             /*!< SCB VTOR: TBLOFF Position */
 #define SCB_VTOR_TBLOFF_MSK                (0x1FFFFFFUL << SCB_VTOR_TBLOFF_POS)           /*!< SCB VTOR: TBLOFF Mask */

 /* SCB Application Interrupt and Reset Control Register Definitions */
 #define SCB_AIRCR_VECTKEY_POS              16                                             /*!< SCB AIRCR: VECTKEY Position */
 #define SCB_AIRCR_VECTKEY_MSK              (0xFFFFUL << SCB_AIRCR_VECTKEY_POS)            /*!< SCB AIRCR: VECTKEY Mask */

 #define SCB_AIRCR_VECTKEYSTAT_POS          16                                             /*!< SCB AIRCR: VECTKEYSTAT Position */
 #define SCB_AIRCR_VECTKEYSTAT_MSK          (0xFFFFUL << SCB_AIRCR_VECTKEYSTAT_POS)        /*!< SCB AIRCR: VECTKEYSTAT Mask */

 #define SCB_AIRCR_ENDIANESS_POS            15                                             /*!< SCB AIRCR: ENDIANESS Position */
 #define SCB_AIRCR_ENDIANESS_MSK            (1UL << SCB_AIRCR_ENDIANESS_POS)               /*!< SCB AIRCR: ENDIANESS Mask */

 #define SCB_AIRCR_PRIGROUP_POS              8                                             /*!< SCB AIRCR: PRIGROUP Position */
 #define SCB_AIRCR_PRIGROUP_MSK             (7UL << SCB_AIRCR_PRIGROUP_POS)                /*!< SCB AIRCR: PRIGROUP Mask */

 #define SCB_AIRCR_SYSRESETREQ_POS           2                                             /*!< SCB AIRCR: SYSRESETREQ Position */
 #define SCB_AIRCR_SYSRESETREQ_MSK          (1UL << SCB_AIRCR_SYSRESETREQ_POS)             /*!< SCB AIRCR: SYSRESETREQ Mask */

 #define SCB_AIRCR_VECTCLRACTIVE_POS         1                                             /*!< SCB AIRCR: VECTCLRACTIVE Position */
 #define SCB_AIRCR_VECTCLRACTIVE_MSK        (1UL << SCB_AIRCR_VECTCLRACTIVE_POS)           /*!< SCB AIRCR: VECTCLRACTIVE Mask */

 #define SCB_AIRCR_VECTRESET_POS             0                                             /*!< SCB AIRCR: VECTRESET Position */
 #define SCB_AIRCR_VECTRESET_MSK            (1UL << SCB_AIRCR_VECTRESET_POS)               /*!< SCB AIRCR: VECTRESET Mask */

 /* SCB System Control Register Definitions */
 #define SCB_SCR_SEVONPEND_POS               4                                             /*!< SCB SCR: SEVONPEND Position */
 #define SCB_SCR_SEVONPEND_MSK              (1UL << SCB_SCR_SEVONPEND_POS)                 /*!< SCB SCR: SEVONPEND Mask */

 #define SCB_SCR_SLEEPDEEP_POS               2                                             /*!< SCB SCR: SLEEPDEEP Position */
 #define SCB_SCR_SLEEPDEEP_MSK              (1UL << SCB_SCR_SLEEPDEEP_POS)                 /*!< SCB SCR: SLEEPDEEP Mask */

 #define SCB_SCR_SLEEPONEXIT_POS             1                                             /*!< SCB SCR: SLEEPONEXIT Position */
 #define SCB_SCR_SLEEPONEXIT_MSK            (1UL << SCB_SCR_SLEEPONEXIT_POS)               /*!< SCB SCR: SLEEPONEXIT Mask */

 /* SCB Configuration Control Register Definitions */
 #define SCB_CCR_STKALIGN_POS                9                                             /*!< SCB CCR: STKALIGN Position */
 #define SCB_CCR_STKALIGN_MSK               (1UL << SCB_CCR_STKALIGN_POS)                  /*!< SCB CCR: STKALIGN Mask */

 #define SCB_CCR_BFHFNMIGN_POS               8                                             /*!< SCB CCR: BFHFNMIGN Position */
 #define SCB_CCR_BFHFNMIGN_MSK              (1UL << SCB_CCR_BFHFNMIGN_POS)                 /*!< SCB CCR: BFHFNMIGN Mask */

 #define SCB_CCR_DIV_0_TRP_POS               4                                             /*!< SCB CCR: DIV_0_TRP Position */
 #define SCB_CCR_DIV_0_TRP_MSK              (1UL << SCB_CCR_DIV_0_TRP_POS)                 /*!< SCB CCR: DIV_0_TRP Mask */

 #define SCB_CCR_UNALIGN_TRP_POS             3                                             /*!< SCB CCR: UNALIGN_TRP Position */
 #define SCB_CCR_UNALIGN_TRP_MSK            (1UL << SCB_CCR_UNALIGN_TRP_POS)               /*!< SCB CCR: UNALIGN_TRP Mask */

 #define SCB_CCR_USERSETMPEND_POS            1                                             /*!< SCB CCR: USERSETMPEND Position */
 #define SCB_CCR_USERSETMPEND_MSK           (1UL << SCB_CCR_USERSETMPEND_POS)              /*!< SCB CCR: USERSETMPEND Mask */

 #define SCB_CCR_NONBASETHRDENA_POS          0                                             /*!< SCB CCR: NONBASETHRDENA Position */
 #define SCB_CCR_NONBASETHRDENA_MSK         (1UL << SCB_CCR_NONBASETHRDENA_POS)            /*!< SCB CCR: NONBASETHRDENA Mask */

 /* SCB System Handler Control and State Register Definitions */
 #define SCB_SHCSR_USGFAULTENA_POS          18                                             /*!< SCB SHCSR: USGFAULTENA Position */
 #define SCB_SHCSR_USGFAULTENA_MSK          (1UL << SCB_SHCSR_USGFAULTENA_POS)             /*!< SCB SHCSR: USGFAULTENA Mask */

 #define SCB_SHCSR_BUSFAULTENA_POS          17                                             /*!< SCB SHCSR: BUSFAULTENA Position */
 #define SCB_SHCSR_BUSFAULTENA_MSK          (1UL << SCB_SHCSR_BUSFAULTENA_POS)             /*!< SCB SHCSR: BUSFAULTENA Mask */

 #define SCB_SHCSR_MEMFAULTENA_POS          16                                             /*!< SCB SHCSR: MEMFAULTENA Position */
 #define SCB_SHCSR_MEMFAULTENA_MSK          (1UL << SCB_SHCSR_MEMFAULTENA_POS)             /*!< SCB SHCSR: MEMFAULTENA Mask */

 #define SCB_SHCSR_SVCALLPENDED_POS         15                                             /*!< SCB SHCSR: SVCALLPENDED Position */
 #define SCB_SHCSR_SVCALLPENDED_MSK         (1UL << SCB_SHCSR_SVCALLPENDED_POS)            /*!< SCB SHCSR: SVCALLPENDED Mask */

 #define SCB_SHCSR_BUSFAULTPENDED_POS       14                                             /*!< SCB SHCSR: BUSFAULTPENDED Position */
 #define SCB_SHCSR_BUSFAULTPENDED_MSK       (1UL << SCB_SHCSR_BUSFAULTPENDED_POS)          /*!< SCB SHCSR: BUSFAULTPENDED Mask */

 #define SCB_SHCSR_MEMFAULTPENDED_POS       13                                             /*!< SCB SHCSR: MEMFAULTPENDED Position */
 #define SCB_SHCSR_MEMFAULTPENDED_MSK       (1UL << SCB_SHCSR_MEMFAULTPENDED_POS)          /*!< SCB SHCSR: MEMFAULTPENDED Mask */

 #define SCB_SHCSR_USGFAULTPENDED_POS       12                                             /*!< SCB SHCSR: USGFAULTPENDED Position */
 #define SCB_SHCSR_USGFAULTPENDED_MSK       (1UL << SCB_SHCSR_USGFAULTPENDED_POS)          /*!< SCB SHCSR: USGFAULTPENDED Mask */

 #define SCB_SHCSR_SYSTICKACT_POS           11                                             /*!< SCB SHCSR: SYSTICKACT Position */
 #define SCB_SHCSR_SYSTICKACT_MSK           (1UL << SCB_SHCSR_SYSTICKACT_POS)              /*!< SCB SHCSR: SYSTICKACT Mask */

 #define SCB_SHCSR_PENDSVACT_POS            10                                             /*!< SCB SHCSR: PENDSVACT Position */
 #define SCB_SHCSR_PENDSVACT_MSK            (1UL << SCB_SHCSR_PENDSVACT_POS)               /*!< SCB SHCSR: PENDSVACT Mask */

 #define SCB_SHCSR_MONITORACT_POS            8                                             /*!< SCB SHCSR: MONITORACT Position */
 #define SCB_SHCSR_MONITORACT_MSK           (1UL << SCB_SHCSR_MONITORACT_POS)              /*!< SCB SHCSR: MONITORACT Mask */

 #define SCB_SHCSR_SVCALLACT_POS             7                                             /*!< SCB SHCSR: SVCALLACT Position */
 #define SCB_SHCSR_SVCALLACT_MSK            (1UL << SCB_SHCSR_SVCALLACT_POS)               /*!< SCB SHCSR: SVCALLACT Mask */

 #define SCB_SHCSR_USGFAULTACT_POS           3                                             /*!< SCB SHCSR: USGFAULTACT Position */
 #define SCB_SHCSR_USGFAULTACT_MSK          (1UL << SCB_SHCSR_USGFAULTACT_POS)             /*!< SCB SHCSR: USGFAULTACT Mask */

 #define SCB_SHCSR_BUSFAULTACT_POS           1                                             /*!< SCB SHCSR: BUSFAULTACT Position */
 #define SCB_SHCSR_BUSFAULTACT_MSK          (1UL << SCB_SHCSR_BUSFAULTACT_POS)             /*!< SCB SHCSR: BUSFAULTACT Mask */

 #define SCB_SHCSR_MEMFAULTACT_POS           0                                             /*!< SCB SHCSR: MEMFAULTACT Position */
 #define SCB_SHCSR_MEMFAULTACT_MSK          (1UL << SCB_SHCSR_MEMFAULTACT_POS)             /*!< SCB SHCSR: MEMFAULTACT Mask */

 /* SCB Configurable Fault Status Registers Definitions */
 #define SCB_CFSR_USGFAULTSR_POS            16                                             /*!< SCB CFSR: Usage Fault Status Register Position */
 #define SCB_CFSR_USGFAULTSR_MSK            (0xFFFFUL << SCB_CFSR_USGFAULTSR_POS)          /*!< SCB CFSR: Usage Fault Status Register Mask */

 #define SCB_CFSR_BUSFAULTSR_POS             8                                             /*!< SCB CFSR: Bus Fault Status Register Position */
 #define SCB_CFSR_BUSFAULTSR_MSK            (0xFFUL << SCB_CFSR_BUSFAULTSR_POS)            /*!< SCB CFSR: Bus Fault Status Register Mask */

 #define SCB_CFSR_MEMFAULTSR_POS             0                                             /*!< SCB CFSR: Memory Manage Fault Status Register Position */
 #define SCB_CFSR_MEMFAULTSR_MSK            (0xFFUL << SCB_CFSR_MEMFAULTSR_POS)            /*!< SCB CFSR: Memory Manage Fault Status Register Mask */

 /* SCB Hard Fault Status Registers Definitions */
 #define SCB_HFSR_DEBUGEVT_POS              31                                             /*!< SCB HFSR: DEBUGEVT Position */
 #define SCB_HFSR_DEBUGEVT_MSK              (1UL << SCB_HFSR_DEBUGEVT_POS)                 /*!< SCB HFSR: DEBUGEVT Mask */

 #define SCB_HFSR_FORCED_POS                30                                             /*!< SCB HFSR: FORCED Position */
 #define SCB_HFSR_FORCED_MSK                (1UL << SCB_HFSR_FORCED_POS)                   /*!< SCB HFSR: FORCED Mask */

 #define SCB_HFSR_VECTTBL_POS                1                                             /*!< SCB HFSR: VECTTBL Position */
 #define SCB_HFSR_VECTTBL_MSK               (1UL << SCB_HFSR_VECTTBL_POS)                  /*!< SCB HFSR: VECTTBL Mask */

 /* SCB Debug Fault Status Register Definitions */
 #define SCB_DFSR_EXTERNAL_POS               4                                             /*!< SCB DFSR: EXTERNAL Position */
 #define SCB_DFSR_EXTERNAL_MSK              (1UL << SCB_DFSR_EXTERNAL_POS)                 /*!< SCB DFSR: EXTERNAL Mask */

 #define SCB_DFSR_VCATCH_POS                 3                                             /*!< SCB DFSR: VCATCH Position */
 #define SCB_DFSR_VCATCH_MSK                (1UL << SCB_DFSR_VCATCH_POS)                   /*!< SCB DFSR: VCATCH Mask */

 #define SCB_DFSR_DWTTRAP_POS                2                                             /*!< SCB DFSR: DWTTRAP Position */
 #define SCB_DFSR_DWTTRAP_MSK               (1UL << SCB_DFSR_DWTTRAP_POS)                  /*!< SCB DFSR: DWTTRAP Mask */

 #define SCB_DFSR_BKPT_POS                   1                                             /*!< SCB DFSR: BKPT Position */
 #define SCB_DFSR_BKPT_MSK                  (1UL << SCB_DFSR_BKPT_POS)                     /*!< SCB DFSR: BKPT Mask */

 #define SCB_DFSR_HALTED_POS                 0                                             /*!< SCB DFSR: HALTED Position */
 #define SCB_DFSR_HALTED_MSK                (1UL << SCB_DFSR_HALTED_POS)                   /*!< SCB DFSR: HALTED Mask */

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

#endif /* INCLUDE_CORE_SCB_H_ */

/*****************************END OF FILE**************************************/
