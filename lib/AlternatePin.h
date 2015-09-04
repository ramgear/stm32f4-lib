/**
 ******************************************************************************
 * @file	AlternatePin.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	02-Sep-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef ALTERNATEPIN_H_
#define ALTERNATEPIN_H_

/* Includes ------------------------------------------------------------------*/

#include <IOPin.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

class AlternatePin : public IOPin
{
public:
	AlternatePin()
	{
		// TODO Auto-generated constructor stub

	}
	virtual ~AlternatePin()
	{
		// TODO Auto-generated destructor stub
	}

	AlternatePin& operator=(const gpio_pin pin)
	{
		/* Release current pin before initial new pin */
		Release();

		m_pin = pin;
		m_pDev = gpio_init(pin);
		if(m_pDev != NULL)
		{
			gpio_set_mode(m_pDev, GPIO_MODE_ALTERNATE);
			SetOutputType(GPIO_OUTPUT_PP);
			SetPullUpPullDown(GPIO_PUPD_NONE);
			SetSpeed(GPIO_SPEED_HIGH);
		}

		return *this;
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

#ifdef __cplusplus
}
#endif

#endif /* ALTERNATEPIN_H_ */

/*****************************END OF FILE**************************************/
