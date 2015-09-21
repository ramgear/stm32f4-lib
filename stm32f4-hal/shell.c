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
#include "usart.h"

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

static void
shell_clear_opt(shell_option_t *p_opt)
{
	shell_option_t *opt = p_opt;
	opt = p_opt;
	while(opt->opt_char != 0)
	{
		*((int *)opt->p_val) = opt->reset_val;

		opt++;
	}
}

boolean
shell_parse_option(int argc, char *const *argv, const char *shortopts, shell_option_t *p_opt)
{
	int c;
	shell_option_t *opt;

	/* Clear parameter */
	shell_clear_opt(p_opt);

	optind = 0;
	opterr = 0;
	c = getopt(argc, argv, shortopts);

	while(c != -1)
	{
		switch (c)
		{
	        case '?':
	          /* getopt_long already printed an error message. */
	        	return false;
	        default:
	        	opt = p_opt;
	        	while(opt->opt_char != 0)
	        	{
	        		if(opt->opt_char == c)
	        		{
	        			if(opt->get_val != NULL && optarg != NULL)
	        				(*opt->get_val)(optarg, opt->p_val);
	        			else
	        				*((int *)opt->p_val) = c;

	        			break;
	        		}
	        		opt++;
	        	}
		}

		c = getopt(argc, argv, shortopts);
	}

	return true;
}

SHELL_FUNC(help)
{
	const shell_t *p_shell = shell_tables;
	char buffer[USART_TX_BUFFER_SIZE];

	shell_puts(caller, "Command List:");
	shell_puts(caller, shell_dash_line);
	shell_puts(caller, "  Command Name | Description");
	shell_puts(caller, shell_dash_line);
	while(p_shell->cmd != NULL)
	{
		sprintf(buffer, "  %-12s   %s", p_shell->cmd, p_shell->description);
		shell_puts(caller, buffer);
		p_shell++;
	}
	shell_puts(caller, shell_dash_line);
}

/*****************************END OF FILE**************************************/
