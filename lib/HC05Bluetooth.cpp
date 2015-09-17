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

extern "C" {

void
hc05_stat_changed(void *owner)
{
	((HC05Bluetooth *)owner)->OnStatChanged();
}

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
SHELL_TABLE_END

/* Implement command here */
SHELL_FUNC(echo)
{
	HC05Bluetooth *obj = (HC05Bluetooth *)caller;
	(void)argv;

	obj->Send("%s\r\n", argv[1]);
}

SHELL_FUNC(reset)
{
	HC05Bluetooth *obj = (HC05Bluetooth *)caller;
	(void)argv;

	obj->ConfigureDevice();
}

SHELL_FUNC(restart)
{
	(void)caller;
	(void)argv;

	scb_reset();
}

SHELL_FUNC(flash)
{
	static int address = 0;
	static int size = 0;
	static shell_option_t long_options[] =
	{
			{ "addr", required_argument, 0, 'a' },
			{ "size", required_argument, 0, 's' },
			{0, 0, 0, 0}
	};
	static shell_opt_param opt_param[] =
	{
			{ &long_options[0],  &address, shell_strtol },
			{ &long_options[1],  &size, shell_strtol },
			{0, 0, 0}
	};

	/* Parse option to variables */
	shell_parse_option(argc, argv, "as:", long_options, opt_param);

	if(address != 0 && size != 0)
	{
		trace("Flash address: 0x%08X size: %d\r\n", address, size);
	}
}

}

void
shell_puts(void *caller, const char *str)
{
	HC05Bluetooth *obj = (HC05Bluetooth *)caller;

	obj->WaitTransmitReady();
	obj->Send("%s\r\n", str);

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
