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
__lookup_table
shell_t cmd_shell_table[] =
{
		SHELL_ENTRY(echo),
		SHELL_ENTRY(reset),
		SHELL_ENTRY(restart),
		SHELL_ENTRY(flash),
		{ NULL, NULL}
};

/* Implement command here */
SHELL_FUNC(echo)
{
	HC05Bluetooth *obj = (HC05Bluetooth *)caller;
	(void)argv;

	obj->Send("%s\r\n", SHELL_ARG(1));
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
	//uint32 idx = getopt(argc, argv, "");
}

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
	shell_exec(cmd_shell_table, cmd, this);
}
