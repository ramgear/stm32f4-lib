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

extern "C" {

#define	CMD_FUNC(cmd)	void cmd_##cmd(void *caller, void *arg)
#define	CMD_ENTRY(cmd)	{#cmd, cmd_##cmd}

void
hc05_stat_changed(void *owner)
{
	((HC05Bluetooth *)owner)->OnStatChanged();
}

typedef	void	(*cmd_func_t)(void *caller, void *arg);

typedef struct cmd_shell_t
{
	const char		*cmd;
	cmd_func_t		func;
} cmd_shell_t;

/* Define command here */
CMD_FUNC(echo);
CMD_FUNC(reset);
CMD_FUNC(restart);

/* List command table here */
__lookup_table
cmd_shell_t cmd_shell_table[] =
{
		CMD_ENTRY(echo),
		CMD_ENTRY(reset),
		CMD_ENTRY(restart),
		{ NULL, NULL}
};

/* Implement command here */
CMD_FUNC(echo)
{
	HC05Bluetooth *obj = (HC05Bluetooth *)caller;
	(void)arg;

	obj->Send("%s\r\n", arg);
}

CMD_FUNC(reset)
{
	HC05Bluetooth *obj = (HC05Bluetooth *)caller;
	(void)arg;

	obj->ConfigureDevice();
}

CMD_FUNC(restart)
{
	(void)caller;
	(void)arg;

	scb_reset();
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
	char args[2][32];
	char *p_cmd = cmd + 1;
	char *ptr	= NULL;
	uint08	argc = 0;

	ptr = strtok(p_cmd, " \n");
	sscanf(ptr, "%s", args[argc]);
	argc++;
	ptr = strtok(NULL, "\n");
	if(ptr != NULL)
	{
		strcpy(args[argc], ptr);
	}

	if(argc == 0)
	{
		return;
	}

	const cmd_shell_t *pCmdShell = cmd_shell_table;
	while(pCmdShell->cmd != NULL)
	{
		if(!strcmp(pCmdShell->cmd, args[0]))
		{
			(*pCmdShell->func)(this, args[1]);
			break;
		}
		pCmdShell++;
	}
}
