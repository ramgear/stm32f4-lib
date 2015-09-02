/**
 * @file	IOPin.h
 * @brief	Framework header file.
 * @details	Framework header file.
 * @version	1.0
 * @date	Aug 30, 2015
 * @author	Eakkasit L.
 * @bug		No known bug
 * @warning	Improper use can crash your application
 * @copyright	GNU Public License.
 */

#ifndef LIB_IOPIN_H_
#define LIB_IOPIN_H_

#include <gpio.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief	
 */
class IOPin
{
protected:
	gpio_pin			m_pin;
	const gpio_pin_dev 	*m_pDev;

public:
	IOPin() : m_pin(INVALID_PIN), m_pDev(NULL)
	{

	}

	virtual ~IOPin()
	{
		Release();
	}

	/**
	 * @brief	Release current GPIO Pin from used.
	 */
	virtual void
	Release(void)
	{
		if(m_pin != INVALID_PIN)
			gpio_release(m_pin);

		m_pDev = NULL;
	}

	/**
	 * @brief	Equal Compare to boolean operator.
	 */
	bool operator==(const bool val) const
	{
		return (val == gpio_read_bit(m_pDev));
	}

	/**
	 * @brief	Not Equal Compare to boolean operator.
	 */
	bool operator!=(const bool val) const
	{
		return (val != gpio_read_bit(m_pDev));
	}

	/**
	 * @brief	Equal Compare to GPIO Pin operator.
	 */
	bool operator==(const gpio_pin pin) const
	{
		return (pin == m_pin);
	}

	/**
	 * @brief	Not Equal Compare to GPIO Pin operator.
	 */
	bool operator!=(const gpio_pin pin) const
	{
		return (pin != m_pin);
	}

	/**
	 * @brief	Implicit cast to GPIO devices pointer.
	 */
	operator const gpio_pin_dev *()
	{
		return m_pDev;
	}

	/**
	 * @brief	Check GPIO Pin available.
	 */
	static boolean
	Available(gpio_pin pin)
	{
		return gpio_available(pin);
	}
};

#ifdef __cplusplus
}
#endif

#endif /* LIB_IOPIN_H_ */
