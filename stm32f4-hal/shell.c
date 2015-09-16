/**
 ******************************************************************************
 * @file	shell.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	16-Sep-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "shell.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

void
shell_get_argv(char *p_cmd, uint32 *p_argc, char **argv)
{
	char *ptr = NULL;
	char *p_arg = (char *)argv;
	uint32	argc = 0;

	/* Check command format */
	if(*p_cmd != '!')
		return;

	p_cmd++;

	ptr = strtok(p_cmd, " ");
	while(ptr != NULL)
	{
		sscanf(ptr, "%s", p_arg);
		++argc;
		p_arg += SHELL_MAX_ARG_LEN * argc;
		ptr = strtok(NULL, " ");
	}

	*p_argc = argc;
}

sint32
shell_exec(const shell_t *p_table, char *p_cmd, void *caller)
{
	static char args[SHELL_MAX_ARG_COUNT][SHELL_MAX_ARG_LEN];
	static uint32	argc = 0;

	shell_get_argv(p_cmd, &argc, (char **)args);
	if(argc == 0)
		return -1;

	const shell_t *shell = p_table;
	while(shell->cmd != NULL)
	{
		if(!strcmp(shell->cmd, args[0]))
		{
			(*shell->func)(caller, argc, (char **)args);
			return 0;
		}
		shell++;
	}

	return -2;
}

/*****************************END OF FILE**************************************/
