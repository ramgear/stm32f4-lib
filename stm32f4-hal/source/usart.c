/**
 ******************************************************************************
 * @file	usart.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	31-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

#include <usart.h>

#define	USART_DEV_ENTRY(NUM,AS)	\
	[SERIAL##NUM]	=	{ .reg = U##AS##RT##NUM##_BASE, .clk_id = RCC_U##AS##RT##NUM, .irq = U##AS##RT##NUM##_IRQn }

#define	USART_ISR(NUM,AS)	\
		void U##AS##RT##NUM##_IRQHandler(void)

typedef struct usart_dev
{
	const	uint32			reg;
	const	rcc_clk_id		clk_id;
	const	nvic_irq_num	irq;
} usart_dev;

typedef struct usart_driver
{
	const usart_dev		*p_dev;
	void 				*p_owner;
	usart_rx_handler	rx_handler;
	usart_tx_handler	tx_handler;
} usart_driver;

__lookup_table
usart_dev usart_dev_table[USART_NUM_MAX] =
{
		USART_DEV_ENTRY(1,SA),
		USART_DEV_ENTRY(2,SA),
		USART_DEV_ENTRY(3,SA),
		USART_DEV_ENTRY(4,A),
		USART_DEV_ENTRY(5,A),
		USART_DEV_ENTRY(6,SA),
};

usart_driver usart_drivers[USART_NUM_MAX];

char usart_rx_buffer;

static inline const usart_dev *
usart_get_dev(usart_num num)
{
	return &usart_dev_table[num];
}

static inline void
usart_set_used(usart_num num)
{
	usart_drivers[num].p_dev = usart_get_dev(num);
}

static inline void
usart_set_unused(usart_num num)
{
	usart_drivers[num].p_dev = NULL;
}

static inline bool
usart_get_available(usart_num num)
{
	return (usart_drivers[num].p_dev == NULL);
}

void
usart_init(usart_num num)
{
	if(!usart_available(num))
		return;

	const usart_dev	*dev = usart_get_dev(num);

	rcc_clk_enable(dev->clk_id);
	nvic_irq_enable(dev->irq);

	/* enable receive and transmit mode */
	usart_t *usart = (usart_t *)dev->reg;
	usart->CR1	= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
	usart->CR2	= 0;
	usart->CR3	= 0;

	usart_set_used(num);
}

void
usart_set_owner(usart_num num, void *owner)
{
	usart_drivers[num].p_owner = owner;
}

void
usart_release(usart_num num)
{
	const usart_dev	*dev = usart_get_dev(num);

	rcc_reset_dev(dev->clk_id);
	nvic_irq_disable(dev->irq);

	usart_set_unused(num);
}

boolean
usart_available(usart_num num)
{
	return usart_get_available(num);
}

void
usart_set_speed(usart_num num, uint32 baudrate)
{
	const usart_dev *dev = usart_get_dev(num);
	usart_t *usart = (usart_t *)dev->reg;
	float32 clk;
	float32 divider;
	uint16 	mantissa;
	uint08 	fraction;
	uint08	sampling;

	/*
	 * Formula:
	 * 		USARTDIV = FCLK / ( 8 * (2 - OVER8) * Baud rate)
	 *
	 * 		Baud rate = FCLK / ( 8 * (2 - OVER8) * USARTDIV)
	 *
	 * 	For 8 over sampling:
	 * 		Baud rate = FCLK / ( 8 * USARTDIV)
	 *
	 * 	For 16 over sampling:
	 * 		Baud rate = FCLK / ( 16 * USARTDIV)
	 */
	clk 		= rcc_get_clk_freq(dev->clk_id);
	sampling	= ((usart->CR1 & USART_CR1_OVER8) != 0) ? 8 : 16;
	divider 	= clk / (sampling * baudrate);

	mantissa 	= (uint16)divider;
	fraction 	= (uint08)((divider - mantissa) * sampling);
	usart->BRR 	= CPU_MOD_VAL(mantissa, USART_BRR_DIV_Mantissa) | CPU_MOD_VAL(fraction, USART_BRR_DIV_Fraction);
}

gpio_af
usart_get_af(usart_num num)
{
	switch(num)
	{
	case SERIAL1:
	case SERIAL2:
	case SERIAL3:
		return GPIO_AF_USART_1_2_3;
	case SERIAL4:
	case SERIAL5:
	case SERIAL6:
		return GPIO_AF_USART_1_2_3;
	default:
		return GPIO_AF_INVALID;
	}
}

void
usart_set_rx_handler(usart_num num, usart_rx_handler handler)
{
	usart_drivers[num].rx_handler = handler;
}

void
usart_set_tx_handler(usart_num num, usart_tx_handler handler)
{
	usart_drivers[num].tx_handler = handler;
}

static void
usart_irq_handler(usart_num num)
{
	CPU_SR_ALLOC
	usart_driver *driver = &usart_drivers[num];

	usart_t *usart = (usart_t *)driver->p_dev->reg;

	if (usart->SR & USART_SR_RXNE)
	{
		usart_rx_buffer = (char)((usart_t *)driver->p_dev->reg)->DR;
		(*driver->rx_handler)(driver->p_owner, usart_rx_buffer);
	}
	else if (usart->SR & USART_SR_TXE)
	{
		(*driver->tx_handler)(driver->p_owner);
	}

	CPU_ENTER_CRITICAL
	CPU_EXIT_CRITICAL
}

/**********************************************************************************
 * USART Interrupt Service Routines Handler
 *********************************************************************************/

USART_ISR(1,SA)
{
	usart_irq_handler(SERIAL1);
}

USART_ISR(2,SA)
{
	usart_irq_handler(SERIAL2);
}

USART_ISR(3,SA)
{
	usart_irq_handler(SERIAL3);
}

USART_ISR(4,A)
{
	usart_irq_handler(SERIAL4);
}

USART_ISR(5,A)
{
	usart_irq_handler(SERIAL5);
}

USART_ISR(6,SA)
{
	usart_irq_handler(SERIAL6);
}
