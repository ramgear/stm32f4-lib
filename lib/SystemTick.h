/**
 * @file	SystemTick.h
 * @brief	Framework header file.
 * @details	Framework header file.
 * @version	1.0
 * @date	Aug 30, 2015
 * @author	Eakkasit L.
 * @bug		No known bug
 * @warning	Improper use can crash your application
 * @copyright	GNU Public License.
 */

#ifndef SYSTEMTICK_H_
#define SYSTEMTICK_H_

#include <systick.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief	
 */
class SystemTick
{
public:
	static inline void
	SetFrequency(uint32 freq_hz)
	{
		systick_init(freq_hz);
	}

	static inline void
	Start(void)
	{
		systick_irq_enable();
	}

	static inline void
	Stop(void)
	{
		systick_irq_disable();
	}

	static inline void
	AttachInterrupt(irq_callback_t cb, boolean enable = true)
	{
		systick_set_callback(cb);

		if(enable)
			Start();
	}
};

#ifdef __cplusplus
}
#endif

#endif /* SYSTEMTICK_H_ */
