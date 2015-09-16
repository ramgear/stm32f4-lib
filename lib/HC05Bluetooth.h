/**
 ******************************************************************************
 * @file	HC05Bluetooth.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	08-Sep-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HC05BLUETOOTH_H_
#define HC05BLUETOOTH_H_

/* Includes ------------------------------------------------------------------*/
#include <HardwareSerial.h>
#include <OutputPin.h>
#include <InputPin.h>
#include <OpenDrainPin.h>
#include <Delay.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
#define	HC05_DEFAULT_SPEED	1382400
#define	HC05_CMD_SPEED	38400

#define	HC05_DEFAULT_NAME	"RAM-BT"
#define	HC05_DEFAULT_PSWD	"1234"

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

class HC05Bluetooth: public HardwareSerial
{
protected:
	static volatile bool	m_bStat;

public:
	OutputPin	m_PwrPin;
	OutputPin	m_CmdPin;
	InputPin	m_StatPin;

	volatile bool mProcessCmd;
	char mMsgBuffer[USART_BUFFER_SIZE];

public:
	HC05Bluetooth() : mProcessCmd(false)
	{

	}
	virtual ~HC05Bluetooth()
	{
	}

	HC05Bluetooth& operator=(const usart_num serial)
	{
		*((HardwareSerial *)this) = serial;

		return *this;
	}

	virtual void
	Begin(uint32 speed = HC05_DEFAULT_SPEED);

	bool
	Connected(void)
	{
		return m_bStat;
	}

	void
	OnRxInterrupt(uint32 count)
	{
		HardwareSerial::OnRxInterrupt(count);

		if(rx_buffer[0] == '!')
		{
			mProcessCmd = true;
		}
	}

	void
	ProcessCommand(char *cmd);

	void
	OnStatChanged(void)
	{
		m_bStat = m_StatPin;
	}

	void
	ConfigureDevice(void)
	{
		EnterCmdMode(true);
		SetName(HC05_DEFAULT_NAME);
		SetPassword(HC05_DEFAULT_PSWD);
		SetSpeed(HC05_DEFAULT_SPEED);
		ExitCmdMode(true);
	}

	void
	SetName(const char *name)
	{
		trace("Set name to \"%s\"\n", name);
		Send("AT+NAME=%s\r\n", name);
		if(!WaitReceiveData(100))
		{
			trace("Timeout!\n");
		}
		else
		{
			trace("Response: %s", rx_buffer);
		}
	}

	void
	SetPassword(const char *pwd)
	{
		trace("Set password to \"%s\"\n", pwd);
		Send("AT+PSWD=%s\r\n", pwd);
		if(!WaitReceiveData(100))
		{
			trace("Timeout!\n");
		}
		else
		{
			trace("Response: %s", rx_buffer);
		}
	}

	void
	SetSpeed(uint32 speed)
	{
		trace("Set speed to \"%d\"\n", speed);
		Send("AT+UART=%d,0,0\r\n", speed);
		if(!WaitReceiveData(100))
		{
			trace("Timeout!\n");
		}
		else
		{
			trace("Response: %s", rx_buffer);
		}
	}

	void
	EnterCmdMode(boolean hard = false)
	{
		if(hard)
		{
			PowerOff();
			m_CmdPin = true;
			PowerOn();

			HardwareSerial::Begin(HC05_CMD_SPEED);
		}
		else
		{
			m_CmdPin = true;
			Delay::Milli(100);
		}
	}
	void
	ExitCmdMode(boolean reset = false)
	{
		m_CmdPin = false;
		Delay::Milli(100);

		if(reset)
			PowerReset();
	}

	void
	PowerOn(void)
	{
		m_PwrPin = false;
		Delay::Milli(100);
	}

	void
	PowerOff(void)
	{
		m_PwrPin = true;
		Delay::Milli(3000);
	}

	void
	PowerReset(void)
	{
		PowerOff();
		PowerOn();
	}
};

#ifdef __cplusplus
}
#endif

#endif /* HC05BLUETOOTH_H_ */

/*****************************END OF FILE**************************************/
