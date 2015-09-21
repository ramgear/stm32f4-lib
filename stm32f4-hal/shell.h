/**
 ******************************************************************************
 * @file	shell.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	16-Sep-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SHELL_H_
#define SHELL_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <cpu.h>
#include <getopt.h>

/* Exported types ------------------------------------------------------------*/
 typedef	void	(*shell_func_t)(void *caller, int argc, char *const argv[]);
 typedef	void	(*shell_get_opt)(const char *str, void *val);

 typedef struct shell_t
 {
 	const char		*cmd;
 	shell_func_t	func;
 	const char		*description;
 } shell_t;

 typedef struct shell_option_t
 {
	 char				opt_char;
	 void				*p_val;
	 shell_get_opt		get_val;
	 int				reset_val;
 } shell_option_t;

/* Exported constants --------------------------------------------------------*/
#define	SHELL_MAX_ARG_COUNT		16
#define	SHELL_MAX_ARG_LEN		16

#define	SHELL_NOT_FOUND			-1

__attribute__ ((unused))
static const
char *shell_dash_line = "------------------------------------------------------------";

/* Exported macro ------------------------------------------------------------*/

#define	SHELL_FUNC(name)	\
	void shell_##name(	\
			__attribute__ ((unused)) void *caller,	\
			__attribute__ ((unused)) int argc, 		\
			__attribute__ ((unused)) char *const argv[])

#define	SHELL_ENTRY(name,desc)	\
	{.cmd = #name, .func = shell_##name, .description = desc},

#define	SHELL_TABLE_BEGIN		\
		const shell_t shell_tables[] = {
#define	SHELL_TABLE_END				\
			SHELL_ENTRY(help,"Print command list.")		\
			{ NULL, NULL, NULL }	\
		};


CPU_INL_FUNC
void
shell_arg2int(const char *str, void *val)
{
	int *ptr = (int *)val;

 	if(!strncmp(str, "0x", 2))
 		sscanf(str, "%x", ptr);
 	else
 		sscanf(str, "%d", ptr);
}

CPU_INL_FUNC
void
shell_arg2str(const char *str, void *val)
{
	strcpy((char *)val, str);
}

CPU_INL_FUNC
void
shell_arg2char(const char *str, void *val)
{
	*(char *)val = *str;
}

CPU_INL_FUNC
boolean
shell_is_found(int val)
{
	return (val != SHELL_NOT_FOUND);
}

/* Exported functions --------------------------------------------------------*/
sint32
shell_exec(void *caller, char *p_cmd);

boolean
shell_parse_option(int argc, char *const *argv, const char *shortopts, shell_option_t *p_opt);

void
shell_puts(void *caller, const char *str);

void
shell_printf(void *caller, const char *format, ...);

SHELL_FUNC(help);

extern const shell_t shell_tables[];

#ifdef __cplusplus
}
#endif

#endif /* SHELL_H_ */

/*****************************END OF FILE**************************************/
