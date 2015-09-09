/**
 ******************************************************************************
 * @file	OpenDrainPin.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	09-Sep-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef OPENDRAINPIN_H_
#define OPENDRAINPIN_H_

/* Includes ------------------------------------------------------------------*/
#include <OutputPin.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

class OpenDrainPin: public OutputPin
{
public:
	OpenDrainPin() = default;

	virtual ~OpenDrainPin() = default;

	OpenDrainPin& operator=(const gpio_pin pin)
	{
		/* Release current pin before initial new pin */
		Release();

		m_pin = pin;
		m_pDev = gpio_init(pin);
		if(m_pDev != NULL)
		{
			SetOutputType(GPIO_OUTPUT_OD);
			SetPullUpPullDown(GPIO_PUPD_NONE);
			SetSpeed(GPIO_SPEED_HIGH);
			gpio_set_mode(m_pDev, GPIO_MODE_OUTPUT);
		}

		return *this;
	}

	OpenDrainPin& operator=(const bool val)
	{
		if(val)
			this->On();
		else
			this->Off();

		return *this;
	}
};

#ifdef __cplusplus
}
#endif

#endif /* OPENDRAINPIN_H_ */

/*****************************END OF FILE**************************************/
