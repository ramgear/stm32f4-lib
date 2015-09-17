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

static void
shell_get_argv(char *p_cmd, int *p_argc, char *const argv[])
{
	char *ptr = NULL;
	uint32	argc = 0;

	/* Check command format */
	if(*p_cmd != '!')
		return;

	p_cmd++;

	ptr = strtok(p_cmd, " ");
	while(ptr != NULL)
	{
		sscanf(ptr, "%s", argv[argc]);
		++argc;
		ptr = strtok(NULL, " ");
	}

	*p_argc = argc;
}

sint32
shell_exec(void *caller, char *p_cmd)
{
	static char args[SHELL_MAX_ARG_COUNT][SHELL_MAX_ARG_LEN];
	static int	argc = 0;
	static char *argv[SHELL_MAX_ARG_COUNT];

	int	arg_init = 0;


	memset(argv, 0, sizeof(argv));
	while(arg_init < SHELL_MAX_ARG_COUNT)
	{
		argv[arg_init] = args[arg_init];
		arg_init++;
	}

	shell_get_argv(p_cmd, &argc, argv);
	if(argc == 0)
		return -1;

	const shell_t *shell = shell_tables;
	while(shell->cmd != NULL)
	{
		if(!strcmp(shell->cmd, argv[0]))
		{
			(*shell->func)(caller, argc, argv);
			return 0;
		}
		shell++;
	}

	return -2;
}

void
shell_parse_option(int argc, char *const *argv, const char *shortopts, const shell_option_t *longopts, shell_opt_param *p_opt)
{
	int c;
	int option_index = 0;
	shell_opt_param *param;

	optind = 0;
	c = getopt_long(argc, argv, shortopts, longopts, &option_index);

	while(c != -1)
	{
		switch (c)
		{
	        case '?':
	          /* getopt_long already printed an error message. */
	          break;
	        default:
	        	param = p_opt;
	        	while(param->p_option != NULL)
	        	{
	        		if(param->p_option->val == c)
	        		{
	        			(*param->get_opt)(optarg, param->p_val);
	        			break;
	        		}
	        		param++;
	        	}
		}

		c = getopt_long(argc, argv, shortopts, longopts, &option_index);
	}

}

SHELL_FUNC(help)
{
	const shell_t *p_shell = shell_tables;
	char buffer[64];

	shell_puts(caller, "Command List:");
	while(p_shell->cmd != NULL)
	{
		sprintf(buffer, "  %-8s -> %s", p_shell->cmd, p_shell->description);
		shell_puts(caller, buffer);
		p_shell++;
	}
}

/*****************************END OF FILE**************************************/
