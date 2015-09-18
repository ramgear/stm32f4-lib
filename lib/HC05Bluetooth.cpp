/**
 ******************************************************************************
 * @file	HC05Bluetooth.cpp
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	08-Sep-2015
 * @brief	Brief of file description
 ******************************************************************************
 */
#include <string.h>
#include <HC05Bluetooth.h>
#include "shell.h"
#include "cmd_gpio.h"

/* Define command here */
SHELL_FUNC(echo);
SHELL_FUNC(reset);
SHELL_FUNC(restart);
SHELL_FUNC(flash);

/* List command table here */
SHELL_TABLE_BEGIN
SHELL_ENTRY(echo,"Echo message.")
SHELL_ENTRY(reset,"Bluetooth re-configuration.")
SHELL_ENTRY(restart,"Restart software.")
SHELL_ENTRY(flash,"Flash firmware.")
SHELL_ENTRY(gpio,"GPIO read/write operation.")
SHELL_TABLE_END

/* Implement command here */
SHELL_FUNC(echo)
{
	HC05Bluetooth *obj = (HC05Bluetooth *)caller;

	char buf[USART_TX_BUFFER_SIZE];

	memset(buf, 0, sizeof(buf));

	for(int i = 1; i < argc; ++i)
	{
		strcat(buf, argv[i]);
		buf[strlen(buf)] = ' ';
	}
	buf[strlen(buf) - 1] = 0;
	obj->Send("%s\r\n", buf);
}

SHELL_FUNC(reset)
{
	HC05Bluetooth *obj = (HC05Bluetooth *)caller;

	obj->ConfigureDevice();
}

SHELL_FUNC(restart)
{
	scb_reset();
}

SHELL_FUNC(flash)
{
	static int address = 0;
	static int size = 0;

	static shell_option_t opt_param[] =
	{
			{ 'a',  &address, shell_strtol, SHELL_NOT_FOUND },
			{ 's',  &size, shell_strtol, SHELL_NOT_FOUND },
			{0, 0, 0, 0}
	};

	/* Parse option to variables */
	shell_parse_option(argc, argv, "as:", opt_param);

	if(address != 0 && size != 0)
	{
		trace("Flash address: 0x%08X size: %d\r\n", address, size);
	}
}

extern "C" void
hc05_stat_changed(void *owner)
{
	((HC05Bluetooth *)owner)->OnStatChanged();
}

void
shell_puts(void *caller, const char *str)
{
	HC05Bluetooth *obj = (HC05Bluetooth *)caller;

	obj->WaitTransmitReady();
	obj->Send("%s\r\n", str);

}

void
shell_printf(void *caller, const char *format, ...)
{

	static char buf[USART_TX_BUFFER_SIZE];

	int ret;
	va_list ap;

	va_start (ap, format);

	  // Print to the local buffer
	  ret = vsnprintf (buf, sizeof(buf), format, ap);
	  if (ret > 0)
	    {
			HC05Bluetooth *obj = (HC05Bluetooth *)caller;

			obj->WaitTransmitReady();
			obj->Send("%s", buf);
	    }

	  va_end (ap);
}

volatile bool HC05Bluetooth::m_bStat = false;

void
HC05Bluetooth::Begin(uint32 speed)
{
	/* Initial power pin as open drain output */
	//m_PwrPin = true;

	HardwareSerial::Begin(speed);

	m_StatPin.AttachInterrupt(hc05_stat_changed, EXTI_TRIGGER_CHANGE, true);

	trace("HC-05 speed at %d\r\n", speed);
}

void
HC05Bluetooth::ProcessCommand(char *cmd)
{
	shell_exec(this, cmd);
}
