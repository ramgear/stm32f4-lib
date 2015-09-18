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

char	_pin_opt[5];
char	_mode_opt[4];
char	_otype_opt[3];
char	_speed_opt[2];
char	_pupd_opt[2];
int		_read_opt;
int		_write_opt;

const char	_short_option[] = "n:m:t:s:p:rw:";

shell_option_t opt_param[] =
{
	{ 'n',  _pin_opt, shell_strcpy, SHELL_NOT_FOUND },
	{ 'm',  _mode_opt, shell_strcpy, SHELL_NOT_FOUND },
	{ 't',  _otype_opt, shell_strcpy, SHELL_NOT_FOUND },
	{ 's',  _speed_opt, shell_strcpy, SHELL_NOT_FOUND },
	{ 'p',  _pupd_opt, shell_strcpy, SHELL_NOT_FOUND },
	{ 'r',  &_read_opt, NULL, SHELL_NOT_FOUND },
	{ 'w',  &_write_opt, shell_strtol, SHELL_NOT_FOUND },
	{ 0, 0, 0, 0 }
};

SHELL_FUNC(gpio)
{
	/* Parse option to variables */
	if(!shell_parse_option(argc, argv, _short_option, opt_param))
	{
		shell_puts(caller, "Invalid format!");
		return;
	}

	char  port;
	int  pin_no;
	int	value;

	sscanf(_pin_opt, "p%c%d",&port, &pin_no);
	if(port < 'a' || port > 'i' || pin_no > 15)
	{
		shell_puts(caller, "Invalid pin input!");
		return;
	}

	gpio_pin pin = (gpio_pin)((port - 'a') * GPIO_PIN_PER_PORT + pin_no);
	const gpio_pin_dev *dev = gpio_get_dev(pin);
	gpio_mode mode = gpio_get_mode(dev);

	if(_read_opt != SHELL_NOT_FOUND)
	{
		/* Read operation */
		value = gpio_read_bit(dev);

		shell_printf(caller, "Pin %-4s [%s]  = %d\r\n"
				, _pin_opt
				, (mode == GPIO_MODE_INPUT) ? "in" : "out"
				, value);

	}
	else if(_write_opt != SHELL_NOT_FOUND)
	{
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
			shell_printf(caller, "Pin %-4s isn't output mode!\r\n" , _pin_opt);
		}
	}
	else
	{
		/* Configure operation */
	}
}

/*****************************END OF FILE**************************************/
