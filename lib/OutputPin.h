/**
 * @file	OutputPin.h
 * @brief	Framework header file.
 * @details	Framework header file.
 * @version	1.0
 * @date	Aug 29, 2015
 * @author	Eakkasit L.
 * @bug		No known bug
 * @warning	Improper use can crash your application
 * @copyright	GNU Public License.
 */

#ifndef LIB_OUTPUTPIN_H_
#define LIB_OUTPUTPIN_H_

#include <IOPin.h>

/**
 * @brief	
 */
class OutputPin : public IOPin
{
public:
	OutputPin(void) = default;

	virtual ~OutputPin() = default;

	OutputPin& operator=(const gpio_pin pin)
	{
		/* Release current pin before initial new pin */
		Release();

		m_pin = pin;
		m_pDev = gpio_init(pin);
		if(m_pDev != NULL)
		{
			gpio_set_mode(m_pDev, GPIO_MODE_OUTPUT);
			SetOutputType(GPIO_OUTPUT_PP);
			SetPullUpPullDown(GPIO_PUPD_UP);
			SetSpeed(GPIO_SPEED_HIGH);
		}

		return *this;
	}

	OutputPin& operator=(const bool val)
	{
		if(val)
			this->On();
		else
			this->Off();

		return *this;
	}

	bool operator!(void) const
	{
		return !gpio_get_out_stat(m_pDev);
	}

	void
	On(void)
	{
		gpio_set_bit(m_pDev);
	}

	void
	Off(void)
	{
		gpio_clear_bit(m_pDev);
	}

	void
	Toggle(void)
	{
		gpio_toggle_bit(m_pDev);
	}

	void
	SetOutputType(gpio_output otype)
	{
		gpio_set_output(m_pDev, otype);
	}

	void
	SetPullUpPullDown(gpio_pupd pupd)
	{
		gpio_set_pupd(m_pDev, pupd);
	}

	void
	SetSpeed(gpio_speed speed)
	{
		gpio_set_speed(m_pDev, speed);
	}
};

#endif /* LIB_OUTPUTPIN_H_ */
