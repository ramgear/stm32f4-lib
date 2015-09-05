/**
 * @file	scb.h
 * @brief	Framework header file.
 * @details	Framework header file.
 * @version	1.0
 * @date	Sep 5, 2015
 * @author	Eakkasit L.
 * @bug		No known bug
 * @warning	Improper use can crash your application
 * @copyright	GNU Public License.
 */

#ifndef INCLUDE_SCB_H_
#define INCLUDE_SCB_H_

#ifdef __cplusplus
 extern "C" {
#endif


#include <core/scb.h>

#define SCB_REG			((scb_t	*)SCB_BASE)		/*!< SCB configuration struct           */

void
scb_init(void);

void
scb_set_vector(uint32 addr);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_SCB_H_ */
