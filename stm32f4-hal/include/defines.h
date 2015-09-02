/**
 ******************************************************************************
 * @file	defines.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	28-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INCLUDE_DEFINES_H_
#define INCLUDE_DEFINES_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#ifdef __cplusplus
#define	__i		volatile			/*!< Defines 'read only' permissions                 */
#else
#define	__i		volatile const		/*!< Defines 'read only' permissions                 */
#endif
#define	__o     volatile			/*!< Defines 'write only' permissions                */
#define __io 	volatile			/*!< Defines 'read / write' permissions              */

#ifndef __attr_flash
#define __attr_flash __attribute__((section (".flash_data")))
#endif
#ifndef __lookup_table
#define __lookup_table	const
#endif
#ifndef __packed
#define __packed __attribute__((__packed__))
#endif
#ifndef __deprecated
#define __deprecated __attribute__((__deprecated__))
#endif
#ifndef __weak
#define __weak __attribute__((weak))
#endif
#ifndef __always_inline
#define __always_inline inline __attribute__((always_inline))
#endif
#ifndef __unused
#define __unused __attribute__((unused))
#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef offsetof
#define offsetof(type, member) __builtin_offsetof(type, member)
#endif

#if 1
#define ASSERT_FAULT(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
extern void assert_failed(uint8_t* file, uint32_t line);
#else
#define ASSERT_FAULT(expr) ((void)0)
#endif

#define trace	trace_printf
extern int trace_printf(const char *format, ... );

static inline void
__set_reg_val(__io uint32_t *reg, uint32_t offset, uint32_t val_mask, uint32_t val)
{
	uint32_t tmp;

    tmp = *reg;
    tmp &= ~(val_mask << offset);
    tmp |= val << offset;
    *reg = tmp;
}

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_DEFINES_H_ */

/*****************************END OF FILE**************************************/
