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
#include <unistd.h>

/* Exported types ------------------------------------------------------------*/
 typedef	void	(*shell_func_t)(void *caller, uint32 argc, char **argv);

 typedef struct shell_t
 {
 	const char		*cmd;
 	shell_func_t	func;
 } shell_t;

/* Exported constants --------------------------------------------------------*/
#define	SHELL_MAX_ARG_COUNT		8
#define	SHELL_MAX_ARG_LEN		16

/* Exported macro ------------------------------------------------------------*/
#define	SHELL_FUNC(name)	void shell_##name(void *caller, uint32 argc, char **argv)
#define	SHELL_ENTRY(name)	{#name, shell_##name}

#define	SHELL_ARG(index)	(char *)((uint32)argv + index * SHELL_MAX_ARG_LEN)

/* Exported functions --------------------------------------------------------*/
sint32
shell_exec(const shell_t *p_table, char *p_cmd, void *caller);

#ifdef __cplusplus
}
#endif

#endif /* SHELL_H_ */

/*****************************END OF FILE**************************************/
