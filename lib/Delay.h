/**
 * @file	Delay.h
 * @brief	Framework header file.
 * @details	Framework header file.
 * @version	1.0
 * @date	Sep 5, 2015
 * @author	Eakkasit L.
 * @bug		No known bug
 * @warning	Improper use can crash your application
 * @copyright	GNU Public License.
 */

#ifndef DELAY_H_
#define DELAY_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <systick.h>

/**
 * @brief	
 */
class Delay
{
public:
	static void
	Milli(uint32 ms)
	{
		systick_delay_ms(ms);
	}

	static void
	Micro(uint32 us)
	{
		systick_delay_us(us);
	}
};

#ifdef __cplusplus
}
#endif

#endif /* DELAY_H_ */
