/**
 * @file	gpio.c
 * @brief	Framework header file.
 * @details	Framework header file.
 * @version	1.0
 * @date	Aug 28, 2015
 * @author	Eakkasit L.
 * @bug		No known bug
 * @warning	Improper use can crash your application
 * @copyright	GNU Public License.
 */

#include <gpio.h>
#include <rcc.h>

#define PORT_DEV_ENTRY(__ALIAS)	\
	[PORT##__ALIAS] = {.reg = GPIO##__ALIAS##_BASE, .clk_id = RCC_GPIO##__ALIAS}

#define PIN_DEV_ENTRY(__ALIAS,__PIN)	\
	[P##__ALIAS##__PIN] = {PORT##__ALIAS, __PIN}


typedef GPIO_TypeDef gpio_reg;

typedef struct gpio_port_dev
{
	const	uint32		reg;
	const	rcc_clk_id	clk_id;
} gpio_port_dev;

__lookup_table
gpio_port_dev gpio_port_dev_table[] =
{
		PORT_DEV_ENTRY(A),
		PORT_DEV_ENTRY(B),
		PORT_DEV_ENTRY(C),
		PORT_DEV_ENTRY(D),
		PORT_DEV_ENTRY(E),
		PORT_DEV_ENTRY(F),
		PORT_DEV_ENTRY(G),
		PORT_DEV_ENTRY(H),
		PORT_DEV_ENTRY(I),
};

__lookup_table
gpio_pin_dev gpio_pin_dev_table[] =
{
		PIN_DEV_ENTRY(A,0),
		PIN_DEV_ENTRY(A,1),
		PIN_DEV_ENTRY(A,2),
		PIN_DEV_ENTRY(A,3),
		PIN_DEV_ENTRY(A,4),
		PIN_DEV_ENTRY(A,5),
		PIN_DEV_ENTRY(A,6),
		PIN_DEV_ENTRY(A,7),
		PIN_DEV_ENTRY(A,8),
		PIN_DEV_ENTRY(A,9),
		PIN_DEV_ENTRY(A,10),
		PIN_DEV_ENTRY(A,11),
		PIN_DEV_ENTRY(A,12),
		PIN_DEV_ENTRY(A,13),
		PIN_DEV_ENTRY(A,14),
		PIN_DEV_ENTRY(A,15),
		PIN_DEV_ENTRY(B,0),
		PIN_DEV_ENTRY(B,1),
		PIN_DEV_ENTRY(B,2),
		PIN_DEV_ENTRY(B,3),
		PIN_DEV_ENTRY(B,4),
		PIN_DEV_ENTRY(B,5),
		PIN_DEV_ENTRY(B,6),
		PIN_DEV_ENTRY(B,7),
		PIN_DEV_ENTRY(B,8),
		PIN_DEV_ENTRY(B,9),
		PIN_DEV_ENTRY(B,10),
		PIN_DEV_ENTRY(B,11),
		PIN_DEV_ENTRY(B,12),
		PIN_DEV_ENTRY(B,13),
		PIN_DEV_ENTRY(B,14),
		PIN_DEV_ENTRY(B,15),
		PIN_DEV_ENTRY(C,0),
		PIN_DEV_ENTRY(C,1),
		PIN_DEV_ENTRY(C,2),
		PIN_DEV_ENTRY(C,3),
		PIN_DEV_ENTRY(C,4),
		PIN_DEV_ENTRY(C,5),
		PIN_DEV_ENTRY(C,6),
		PIN_DEV_ENTRY(C,7),
		PIN_DEV_ENTRY(C,8),
		PIN_DEV_ENTRY(C,9),
		PIN_DEV_ENTRY(C,10),
		PIN_DEV_ENTRY(C,11),
		PIN_DEV_ENTRY(C,12),
		PIN_DEV_ENTRY(C,13),
		PIN_DEV_ENTRY(C,14),
		PIN_DEV_ENTRY(C,15),
		PIN_DEV_ENTRY(D,0),
		PIN_DEV_ENTRY(D,1),
		PIN_DEV_ENTRY(D,2),
		PIN_DEV_ENTRY(D,3),
		PIN_DEV_ENTRY(D,4),
		PIN_DEV_ENTRY(D,5),
		PIN_DEV_ENTRY(D,6),
		PIN_DEV_ENTRY(D,7),
		PIN_DEV_ENTRY(D,8),
		PIN_DEV_ENTRY(D,9),
		PIN_DEV_ENTRY(D,10),
		PIN_DEV_ENTRY(D,11),
		PIN_DEV_ENTRY(D,12),
		PIN_DEV_ENTRY(D,13),
		PIN_DEV_ENTRY(D,14),
		PIN_DEV_ENTRY(D,15),
		PIN_DEV_ENTRY(E,0),
		PIN_DEV_ENTRY(E,1),
		PIN_DEV_ENTRY(E,2),
		PIN_DEV_ENTRY(E,3),
		PIN_DEV_ENTRY(E,4),
		PIN_DEV_ENTRY(E,5),
		PIN_DEV_ENTRY(E,6),
		PIN_DEV_ENTRY(E,7),
		PIN_DEV_ENTRY(E,8),
		PIN_DEV_ENTRY(E,9),
		PIN_DEV_ENTRY(E,10),
		PIN_DEV_ENTRY(E,11),
		PIN_DEV_ENTRY(E,12),
		PIN_DEV_ENTRY(E,13),
		PIN_DEV_ENTRY(E,14),
		PIN_DEV_ENTRY(E,15),
		PIN_DEV_ENTRY(F,0),
		PIN_DEV_ENTRY(F,1),
		PIN_DEV_ENTRY(F,2),
		PIN_DEV_ENTRY(F,3),
		PIN_DEV_ENTRY(F,4),
		PIN_DEV_ENTRY(F,5),
		PIN_DEV_ENTRY(F,6),
		PIN_DEV_ENTRY(F,7),
		PIN_DEV_ENTRY(F,8),
		PIN_DEV_ENTRY(F,9),
		PIN_DEV_ENTRY(F,10),
		PIN_DEV_ENTRY(F,11),
		PIN_DEV_ENTRY(F,12),
		PIN_DEV_ENTRY(F,13),
		PIN_DEV_ENTRY(F,14),
		PIN_DEV_ENTRY(F,15),
		PIN_DEV_ENTRY(G,0),
		PIN_DEV_ENTRY(G,1),
		PIN_DEV_ENTRY(G,2),
		PIN_DEV_ENTRY(G,3),
		PIN_DEV_ENTRY(G,4),
		PIN_DEV_ENTRY(G,5),
		PIN_DEV_ENTRY(G,6),
		PIN_DEV_ENTRY(G,7),
		PIN_DEV_ENTRY(G,8),
		PIN_DEV_ENTRY(G,9),
		PIN_DEV_ENTRY(G,10),
		PIN_DEV_ENTRY(G,11),
		PIN_DEV_ENTRY(G,12),
		PIN_DEV_ENTRY(G,13),
		PIN_DEV_ENTRY(G,14),
		PIN_DEV_ENTRY(G,15),
		PIN_DEV_ENTRY(H,0),
		PIN_DEV_ENTRY(H,1),
		PIN_DEV_ENTRY(H,2),
		PIN_DEV_ENTRY(H,3),
		PIN_DEV_ENTRY(H,4),
		PIN_DEV_ENTRY(H,5),
		PIN_DEV_ENTRY(H,6),
		PIN_DEV_ENTRY(H,7),
		PIN_DEV_ENTRY(H,8),
		PIN_DEV_ENTRY(H,9),
		PIN_DEV_ENTRY(H,10),
		PIN_DEV_ENTRY(H,11),
		PIN_DEV_ENTRY(H,12),
		PIN_DEV_ENTRY(H,13),
		PIN_DEV_ENTRY(H,14),
		PIN_DEV_ENTRY(H,15),
		PIN_DEV_ENTRY(I,0),
		PIN_DEV_ENTRY(I,1),
		PIN_DEV_ENTRY(I,2),
		PIN_DEV_ENTRY(I,3),
		PIN_DEV_ENTRY(I,4),
		PIN_DEV_ENTRY(I,5),
		PIN_DEV_ENTRY(I,6),
		PIN_DEV_ENTRY(I,7),
		PIN_DEV_ENTRY(I,8),
		PIN_DEV_ENTRY(I,9),
		PIN_DEV_ENTRY(I,10),
		PIN_DEV_ENTRY(I,11),
		PIN_DEV_ENTRY(I,12),
		PIN_DEV_ENTRY(I,13),
		PIN_DEV_ENTRY(I,14),
		PIN_DEV_ENTRY(I,15),
};

const char port_alias_table[] = "ABCDEFGHI";

static uint16	_pin_used_mask[GPIO_PORT_NUM];

static inline
gpio_reg *
gpio_get_reg(gpio_port port)
{
	return (gpio_reg *)gpio_port_dev_table[port].reg;
}

static inline
void
gpio_clk_enable(gpio_port port)
{
	rcc_clk_enable(gpio_port_dev_table[port].clk_id);
}

const gpio_pin_dev *
gpio_init(gpio_pin pin)
{
	const gpio_pin_dev *dev = &gpio_pin_dev_table[pin];

	/* Check pin used */
	if((_pin_used_mask[dev->port] & (1 << dev->pin)) != 0)
	{
		trace("ERROR: pin P%c%d already initialized.\n", port_alias_table[dev->port], dev->pin);

		return NULL;
	}

	/* Enable clock */
	gpio_clk_enable(dev->port);

	/* Mask used pin */
	_pin_used_mask[dev->port] |= (1 << dev->pin);

	trace("Initialized pin P%c%d completed.\n", port_alias_table[dev->port], dev->pin);

	return dev;
}

const gpio_pin_dev *
gpio_get_dev(gpio_pin pin)
{
	return &gpio_pin_dev_table[pin];
}

boolean
gpio_available(gpio_pin pin)
{
	const gpio_pin_dev *dev = &gpio_pin_dev_table[pin];

	return ((_pin_used_mask[dev->port] &= (1 << dev->pin)) == 0);
}

void
gpio_release(gpio_pin pin)
{
	const gpio_pin_dev *dev = &gpio_pin_dev_table[pin];

	/* Mask unused pin */
	_pin_used_mask[dev->port] &= ~(1 << dev->pin);


	trace("Release pin P%c%d completed.\n", port_alias_table[dev->port], dev->pin);
}

void
gpio_set_mode(const gpio_pin_dev *dev, gpio_mode mode)
{
    gpio_reg *regs = gpio_get_reg(dev->port);

    __set_reg_val(&regs->MODER, dev->pin * 2, 3, mode);
}

void
gpio_set_output(const gpio_pin_dev *dev, gpio_output otype)
{
    gpio_reg *regs = gpio_get_reg(dev->port);

    __set_reg_val(&regs->OTYPER, dev->pin, 1, otype);
}

void
gpio_set_speed(const gpio_pin_dev *dev, gpio_speed speed)
{
    gpio_reg *regs = gpio_get_reg(dev->port);

    __set_reg_val(&regs->OSPEEDR, dev->pin * 2, 3, speed);
}

void
gpio_set_pupd(const gpio_pin_dev *dev, gpio_pupd pupd)
{
    gpio_reg *regs = gpio_get_reg(dev->port);

    __set_reg_val(&regs->PUPDR, dev->pin * 2, 3, pupd);
}

void
gpio_set_af(const gpio_pin_dev *dev, gpio_af af)
{
    gpio_reg *regs = gpio_get_reg(dev->port);

    __set_reg_val(&regs->AFR[dev->pin >> 3], dev->pin % 8, 0xF, af);
}

void
gpio_set_bit(const gpio_pin_dev *dev)
{
    gpio_get_reg(dev->port)->BSRR |= (1 << dev->pin);
}

void
gpio_clear_bit(const gpio_pin_dev *dev)
{
    gpio_get_reg(dev->port)->BSRR |= (0x010000 << dev->pin);
}

void
gpio_toggle_bit(const gpio_pin_dev *dev)
{
    gpio_get_reg(dev->port)->ODR ^= (1 << dev->pin);
}

boolean
gpio_read_bit(const gpio_pin_dev *dev)
{
    return (gpio_get_reg(dev->port)->IDR & (1 << dev->pin));
}

boolean
gpio_get_out_stat(const gpio_pin_dev *dev)
{
    return (gpio_get_reg(dev->port)->ODR & (1 << dev->pin));
}
