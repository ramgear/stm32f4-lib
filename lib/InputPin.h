/**
 * @file	InputPin.h
 * @brief	Framework header file.
 * @details	Framework header file.
 * @version	1.0
 * @date	Aug 29, 2015
 * @author	Eakkasit L.
 * @bug		No known bug
 * @warning	Improper use can crash your application
 * @copyright	GNU Public License.
 */

#ifndef LIB_INPUTPIN_H_
#define LIB_INPUTPIN_H_

#include <IOPin.h>
#include <exti.h>

/**
 * @brief	
 */
class InputPin : public IOPin
{
public:
	InputPin(void) = default;

	virtual ~InputPin(void)
	{
		if(m_pDev != NULL)
			exti_release((exti_num)m_pDev->pin);
	}

	InputPin& operator=(const gpio_pin pin)
	{
		/* Release current pin before initial new pin */
		Release();

		m_pin = pin;
		m_pDev = gpio_init(pin);
		if(m_pDev != NULL)
		{
			gpio_set_mode(m_pDev, GPIO_MODE_INPUT);
			SetPuPd(GPIO_PUPD_UP);
		}

		return *this;
	}

	void
	Release(void)
	{
		if(m_pin != INVALID_PIN)
		{
			gpio_release(m_pin);
			exti_release((exti_num)m_pDev->pin);
		}

		m_pDev = NULL;
	}


	operator bool ()
	{
		return gpio_read_bit(m_pDev);
	}

	void
	SetPuPd(gpio_pupd pupd)
	{
		gpio_set_pupd(m_pDev, pupd);
	}

	void
	AttachInterrupt(
			irq_callback_t cb
			, exti_trigger trigger = EXTI_TRIGGER_CHANGE
			, boolean enable = true
			)
	{
		if(cb == NULL)
		{
			trace("WARNING: Cannot set interrupt callback to null function!\n");
			return;
		}

		exti_num exti = (exti_num)m_pDev->pin;
		if(!exti_available(exti))
		{
			trace("WARNING: Interrupt already used by other pin!\n");
			return;
		}

		exti_set_owner(exti, m_pDev, this);
		exti_set_trigger(exti, trigger);
		exti_set_callback(exti, cb);
		if(enable)
			exti_enable(exti);
	}

	void
	EnableInterrupt(void)
	{
		exti_enable((exti_num)m_pDev->pin);
	}

	void
	DisableInterrupt(void)
	{
		exti_disable((exti_num)m_pDev->pin);
	}
};

#endif /* LIB_INPUTPIN_H_ */
