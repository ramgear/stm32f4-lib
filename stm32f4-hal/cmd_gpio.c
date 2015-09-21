/**
 ******************************************************************************
 * @file	cmd_gpio.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	18-Sep-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "cmd_gpio.h"
#include <ctype.h>

typedef void (*shell_gpio_config)(const gpio_pin_dev *dev, int value);

char	_port;
char	_pin_opt[5];
char	_mode_opt[4];
char	_otype_opt[3];
char	_speed_opt[2];
char	_pupd_opt[2];
int		_read_opt;
int		_write_opt;
int		_help;

const char	_short_option[]	= "hP:n:m:t:s:p:rw:";
const char	*_mode_table[]	= { "in", "out", "af", "an", 0 };
const char	*_otype_table[] = { "pp", "od", 0 };
const char	*_speed_table[] = { "l", "m", "f", "h", 0 };
const char	*_pupd_table[] 	= { "no", "pu", "pd", "na", 0 };

shell_option_t opt_param[] =
{
	{ 'h',  &_help, shell_arg2int, SHELL_NOT_FOUND },
	{ 'P',  &_port, shell_arg2char, SHELL_NOT_FOUND },
	{ 'n',  _pin_opt, shell_arg2str, SHELL_NOT_FOUND },
	{ 'm',  _mode_opt, shell_arg2str, SHELL_NOT_FOUND },
	{ 't',  _otype_opt, shell_arg2str, SHELL_NOT_FOUND },
	{ 's',  _speed_opt, shell_arg2str, SHELL_NOT_FOUND },
	{ 'p',  _pupd_opt, shell_arg2str, SHELL_NOT_FOUND },
	{ 'r',  &_read_opt, NULL, SHELL_NOT_FOUND },
	{ 'w',  &_write_opt, shell_arg2int, SHELL_NOT_FOUND },
	{ 0, 0, 0, 0 }
};

CPU_INL_FUNC
void
shell_gpio_print_header(void *caller)
{
	shell_puts(caller, shell_dash_line);
	shell_puts(caller, "  PIN  | MODE | OTYPE | SPEED | PUPD | VALUE");
	shell_puts(caller, shell_dash_line);
}

CPU_INL_FUNC
void
shell_gpio_print_footer(void *caller)
{
	shell_puts(caller, shell_dash_line);
}

CPU_INL_FUNC
void
shell_gpio_print_info(void *caller, const gpio_pin_dev *dev, int port, int pin)
{
	shell_printf(caller, "  P%c%02d   %-7s%-8s%-8s%-7s%-5d \r\n"
			, toupper(port)
			, pin
			, _mode_table[gpio_get_mode(dev)]
			, _otype_table[gpio_get_otype(dev)]
			, _speed_table[gpio_get_speed(dev)]
			, _pupd_table[gpio_get_pupd(dev)]
			, (int)gpio_read_bit(dev));
}

CPU_INL_FUNC
boolean
shell_gpio_config_check(const gpio_pin_dev *dev, const char *lookup_table[], const char *opt, shell_gpio_config p_func)
{
	int value = 0;
	while(*lookup_table[value] != 0)
	{
		if(!strcmp(lookup_table[value], opt))
		{
			(*p_func)(dev, value);
			return true;
		}
		value++;
	}

	return false;
}

SHELL_FUNC(gpio)
{
	/* Parse option to variables */
	if(!shell_parse_option(argc, argv, _short_option, opt_param))
	{
		shell_puts(caller, "Invalid format!");
		return;
	}

	if(shell_is_found(_help))
	{
		shell_puts(caller, "GPIO Command Help.");
		shell_puts(caller, shell_dash_line);
		shell_puts(caller, " !gpio [options]\r\n");
		shell_puts(caller, "   -P [a..i]\t\tTo print all pin status for specify port.\r\n");
		shell_puts(caller, "   -n p[a..i][0..15]\tTo specify pin.\r\n");
		shell_puts(caller, "   -m [in|out]\t\tTo set mode.\r\n");
		shell_puts(caller, "   -t [pp|od]\t\tTo set output type.");
		shell_puts(caller, "   where, pp = push pull, od = open drain\r\n");
		shell_puts(caller, "   -s [l|m|f|h]\t\tTo set output speed.");
		shell_puts(caller, "   where, l = low, m = medium, f = fast, h = high.\r\n");
		shell_puts(caller, "   -p [no|pu|pd]\tTo set pull-up pull-down.");
		shell_puts(caller, "   where, no = no pull-up/pull-down, pu = pull-up, pd = pull-down.\r\n");
		shell_puts(caller, "   -r \t\t\tTo read value.\r\n");
		shell_puts(caller, "   -w [0|1]\t\tTo write value.\r\n");
		shell_gpio_print_footer(caller);
		return;
	}

	int  pin_no;
	const gpio_pin_dev *dev = NULL;
	gpio_pin pin;
	int	port;

	if(shell_is_found((int)_port))
	{
		shell_gpio_print_header(caller);
		port = _port - 'a';
		for(int i = 0; i < GPIO_PIN_PER_PORT; ++i)
		{
			pin = (gpio_pin)(port * GPIO_PIN_PER_PORT + i);
			dev = gpio_get_dev(pin);

			shell_gpio_print_info(caller, dev, _port, i);
		}
		shell_gpio_print_footer(caller);

	}
	else if(shell_is_found(*(int *)_pin_opt))
	{
		//int value;

		sscanf(_pin_opt, "p%c%d",&_port, &pin_no);
		if(_port < 'a' || _port > 'i' || pin_no > 15)
		{
			shell_puts(caller, "Invalid pin input!");
			return;
		}

		port = _port - 'a';
		pin = (gpio_pin)(port * GPIO_PIN_PER_PORT + pin_no);
		dev = gpio_get_dev(pin);

		if(shell_is_found(_read_opt))
		{
			shell_printf(caller, "Pin %-4s [%3s]  = %d\r\n"
					, _pin_opt
					, _mode_table[gpio_get_mode(dev)]
					, gpio_read_bit(dev));

		}
		else if(shell_is_found(_write_opt))
		{
			gpio_mode mode = gpio_get_mode(dev);

			/* Write operation */
			if(mode == GPIO_MODE_OUTPUT)
			{
				if(_write_opt != 0)
					gpio_set_bit(dev);
				else
					gpio_clear_bit(dev);
			}
			else
			{
				shell_printf(caller, "Pin %-4s is \"%s\" mode! Only \"%s\" mode can write!\r\n"
						, _pin_opt
						, _mode_table[gpio_get_mode(dev)]
						, _mode_table[GPIO_MODE_OUTPUT]
						);
			}
		}
		else
		{
			/* Configure operation */

			/* Set Mode */
			if(shell_is_found(shell_is_found(*(int *)_mode_opt)))
			{
				/*if((value = shell_gpio_config_check(_mode_table, _mode_opt)) != SHELL_NOT_FOUND)
					gpio_set_mode(dev, (gpio_mode)value);
				else*/
				if(!shell_gpio_config_check(dev, _mode_table, _mode_opt, (shell_gpio_config)gpio_set_mode))
					shell_printf(caller, "Mode \"%s\" not available!", _mode_opt);
			}
			/* Set Output type */
			if(shell_is_found(shell_is_found(*(int *)_otype_opt)))
			{
				if(!shell_gpio_config_check(dev, _otype_table, _otype_opt, (shell_gpio_config)gpio_set_output))
					shell_printf(caller, "Output type \"%s\" not available!", _otype_opt);
			}
			/* Set Speed */
			if(shell_is_found(shell_is_found(*(int *)_speed_opt)))
			{
				if(!shell_gpio_config_check(dev, _speed_table, _speed_opt, (shell_gpio_config)gpio_set_speed))
					shell_printf(caller, "Speed \"%s\" not available!", _speed_opt);
			}
			/* Set Pull-up Pull-down */
			if(shell_is_found(shell_is_found(*(int *)_pupd_opt)))
			{
				if(!shell_gpio_config_check(dev, _pupd_table, _pupd_opt, (shell_gpio_config)gpio_set_pupd))
					shell_printf(caller, "Pull \"%s\" not available!", _pupd_opt);
			}

			/* Print current setting */
			shell_gpio_print_header(caller);
			shell_gpio_print_info(caller, dev, _port, pin_no);
			shell_gpio_print_footer(caller);
		}
	}
}

/*****************************END OF FILE**************************************/
