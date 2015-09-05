/**
 * @file	trace.h
 * @brief	Framework header file.
 * @details	Framework header file.
 * @version	1.0
 * @date	Sep 5, 2015
 * @author	Eakkasit L.
 * @bug		No known bug
 * @warning	Improper use can crash your application
 * @copyright	GNU Public License.
 */

#ifndef INCLUDE_TRACE_H_
#define INCLUDE_TRACE_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <semihosting.h>

 ssize_t
 trace_write(const char* buf, size_t nbyte);

 int
 trace_printf(const char* format, ...);

 int
 trace_puts(const char *s);

 int
 trace_putchar(int c);


#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_TRACE_H_ */
