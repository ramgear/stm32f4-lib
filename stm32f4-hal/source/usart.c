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
#include <dma.h>

#define	USART_DEV_ENTRY(NUM,AS)	\
	[SERIAL##NUM]	=	{ .reg = U##AS##RT##NUM##_BASE, .clk_id = RCC_U##AS##RT##NUM, .irq = U##AS##RT##NUM##_IRQn }

#define	USART_DMA_ENTRY(SNUM,DNUM,DCRX,DSRX,DCTX,DSTX)	\
	[SERIAL##SNUM]	=	{ .dma = (uint08)DMA_##DNUM, \
			.rx_stream = (uint08)DMA_STREAM_##DSRX, .rx_stream_base = DMA_STREAM_BASE(DNUM,DSRX), .rx_channel = (uint08)DMA_CHANNEL_##DCRX, \
			.tx_stream = (uint08)DMA_STREAM_##DSTX, .tx_stream_base = DMA_STREAM_BASE(DNUM,DSTX), .tx_channel = (uint08)DMA_CHANNEL_##DCTX}

#define	USART_ISR(NUM,AS)	\
		void ISR_U##AS##RT##NUM##_IRQHandler(void)

#define	USART_FLAG_SET			1
#define	USART_FLAG_RESET		0

typedef struct usart_dev
{
	const	uint32			reg;
	const	rcc_clk_id		clk_id;
	const	nvic_irq_num	irq;
} usart_dev;

typedef struct usart_dma
{
	uint08			dma;
	uint08			rx_stream;
	uint08			rx_channel;
	uint08			reserved1;
	uint32			rx_stream_base;
	uint08			tx_stream;
	uint08			tx_channel;
	uint08			reserved2;
	uint08			reserved3;
	uint32			tx_stream_base;
} usart_dma;

typedef struct usart_driver
{
	const usart_dev		*p_dev;
	void 				*p_owner;
	usart_rx_handler	rx_handler;
	usart_tx_handler	tx_handler;
	uint08				rx_buffer[USART_BUFFER_SIZE];
	uint08				tx_buffer[USART_BUFFER_SIZE];
	uint08				rx_head;
	uint08				rx_tail;
	const usart_dma		*p_usart_dma;
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

__lookup_table
usart_dma usart_dma_table[USART_NUM_MAX] =
{
		USART_DMA_ENTRY(1,2,4,2,4,7),
		USART_DMA_ENTRY(2,1,4,5,4,6),
		USART_DMA_ENTRY(3,1,4,1,4,3),
		USART_DMA_ENTRY(4,1,4,2,4,4),
		USART_DMA_ENTRY(5,1,4,0,4,7),
		USART_DMA_ENTRY(6,2,5,2,5,7),
};

usart_driver usart_drivers[USART_NUM_MAX];

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
usart_dma_rx_handler(void *owner, dma_num num, dma_stream stream);
void
usart_dma_tx_handler(void *owner, dma_num num, dma_stream stream);

void
usart_set_rx_dma_enable(usart_t *usart, uint32 stat);
void
usart_set_tx_dma_enable(usart_t *usart, uint32 stat);

void
usart_dma_init_rx(usart_num num)
{
	usart_driver	*driver = &usart_drivers[num];
	const usart_dma *dma = &usart_dma_table[num];
	usart_t *usart = (usart_t *)driver->p_dev->reg;

	/* Initial RX DMA */
	dma_stream_t	*rx_stream = (dma_stream_t *)dma->rx_stream_base;
	dma_set_channel(rx_stream, dma->rx_channel);
	dma_set_paddr(rx_stream, (uint32)&usart->DR);
	dma_set_m0addr(rx_stream, (uint32)driver->rx_buffer);
	dma_set_direction(rx_stream, DMA_DIR_PER_TO_MEM);
	dma_set_data_size(rx_stream, USART_BUFFER_SIZE);
	dma_set_pinc_mode(rx_stream, DISABLE);
	dma_set_minc_mode(rx_stream, ENABLE);
	dma_set_minc_size(rx_stream, DMA_DATA_SIZE_8);
	dma_set_pinc_size(rx_stream, DMA_DATA_SIZE_8);
	dma_set_circular_mode(rx_stream, ENABLE);
	dma_set_priority(rx_stream, DMA_PRIO_HIGH);
	dma_set_direct_mode(rx_stream, ENABLE);
	dma_set_fifo_threshold(rx_stream, DMA_FIFO_TH_FULL);
	dma_set_mburst(rx_stream, DMA_BURST_1);
	dma_set_pburst(rx_stream, DMA_BURST_1);

	dma_set_handler(dma->dma, dma->rx_stream, dma->rx_channel, usart_dma_rx_handler, (void *)driver);
	dma_set_it(rx_stream, DMA_IT_TC, ENABLE);
	dma_set_irq_enable(dma->dma, dma->rx_stream, ENABLE);
	dma_clear_stream_flags(dma->dma, dma->rx_stream);
	usart_set_rx_dma_enable(usart, ENABLE);
	dma_set_stream(rx_stream, ENABLE);
}

void
usart_dma_init_tx(usart_num num)
{
	usart_driver	*driver = &usart_drivers[num];
	const usart_dma *dma = &usart_dma_table[num];
	usart_t *usart = (usart_t *)driver->p_dev->reg;

	/* Initial TX DMA */
	dma_stream_t	*tx_stream = (dma_stream_t *)dma->tx_stream_base;
	dma_set_channel(tx_stream, dma->tx_channel);
	dma_set_paddr(tx_stream, (uint32)&usart->DR);
	dma_set_m0addr(tx_stream, (uint32)driver->tx_buffer);
	dma_set_direction(tx_stream, DMA_DIR_MEM_TO_PER);
	dma_set_data_size(tx_stream, USART_BUFFER_SIZE);
	dma_set_pinc_mode(tx_stream, DISABLE);
	dma_set_minc_mode(tx_stream, ENABLE);
	dma_set_minc_size(tx_stream, DMA_DATA_SIZE_8);
	dma_set_pinc_size(tx_stream, DMA_DATA_SIZE_8);
	dma_set_circular_mode(tx_stream, DISABLE);
	dma_set_priority(tx_stream, DMA_PRIO_HIGH);
	dma_set_direct_mode(tx_stream, ENABLE);
	dma_set_fifo_threshold(tx_stream, DMA_FIFO_TH_FULL);
	dma_set_mburst(tx_stream, DMA_BURST_1);
	dma_set_pburst(tx_stream, DMA_BURST_1);

	dma_set_handler(dma->dma, dma->tx_stream, dma->tx_channel, usart_dma_tx_handler, (void *)driver);
	dma_set_it(tx_stream, DMA_IT_TC, ENABLE);
	dma_set_irq_enable(dma->dma, dma->tx_stream, ENABLE);
	usart_set_tx_dma_enable(usart, ENABLE);
}

void
usart_dma_init(usart_num num)
{
	usart_driver	*driver = &usart_drivers[num];
	const usart_dma *dma = &usart_dma_table[num];
	driver->p_usart_dma = dma;

	/* Enable DMA Clock */
	dma_clk_enable(dma->dma);

	usart_dma_init_tx(num);
	usart_dma_init_rx(num);
}

void
usart_set_rx_dma_enable(usart_t *usart, uint32 stat)
{
	if(stat != DISABLE)
		usart->CR3 |= USART_CR3_DMAR;
	else
		usart->CR3 &= ~USART_CR3_DMAR;
}

void
usart_set_tx_dma_enable(usart_t *usart, uint32 stat)
{
	if(stat != DISABLE)
		usart->CR3 |= USART_CR3_DMAT;
	else
		usart->CR3 &= ~USART_CR3_DMAT;
}

void
usart_init(usart_num num)
{
	if(!usart_available(num))
		return;

	usart_driver	*driver = &usart_drivers[num];
	const usart_dev	*dev = usart_get_dev(num);

	rcc_clk_enable(dev->clk_id);
	nvic_irq_enable(dev->irq);

	/* initial driver */
	driver->p_dev 					= dev;

	/* enable receive and transmit mode */
	usart_t *usart = (usart_t *)dev->reg;
	usart->CR1	= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE | USART_CR1_IDLEIE;

	/* Parity: none, stop bit: 0, flow control: none */
	usart->CR2	= 0;

	/* Enable TX/RX DMA */
	usart->CR3	= 0;

	(void)usart->SR;
	(void)usart->DR;

	/* Initial DMA */
	usart_dma_init(num);

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
	usart->BRR 	= CPU_MOD_VAL(USART_BRR_DIV_Mantissa, mantissa) | CPU_MOD_VAL(USART_BRR_DIV_Fraction, fraction);
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
		return GPIO_AF_USART_4_5_6;
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

void
usart_send(usart_num num, const uint08 data)
{
	usart_driver *driver = &usart_drivers[num];
	usart_t		*reg = (usart_t *)driver->p_dev->reg;

	/* Wait till tx is empty */
	while(!(reg->SR & USART_SR_TXE));

	reg->DR = data;
}

void
usart_send_dma(usart_num num, const uint08 *data, uint32 count)
{
	usart_driver *driver = &usart_drivers[num];
	dma_stream_t *stream = (dma_stream_t *)driver->p_usart_dma->tx_stream_base;

	memcpy(driver->tx_buffer, data, count);

	dma_set_data_size((dma_stream_t *)driver->p_usart_dma->tx_stream_base, count);
	dma_set_stream(stream, ENABLE);
}

void
usart_read(usart_num num, uint08 *data, uint32 count)
{
	usart_driver *driver = &usart_drivers[num];
	uint32	len;
	uint08	*ptr;

	/* Copy received data */
	if(driver->rx_head + count < USART_BUFFER_SIZE)
	{
		memcpy(data, driver->rx_buffer + driver->rx_head, count);

		/* update current head */
		driver->rx_head += count;
	}
	else
	{
		ptr = data;
		len = USART_BUFFER_SIZE - driver->rx_head;
		memcpy(ptr, driver->rx_buffer + driver->rx_head, len);
		ptr += len;
		len = count - len;
		memcpy(ptr, driver->rx_buffer, len);

		driver->rx_head = len;
	}
}

static void
usart_irq_handler(usart_num num)
{
	usart_driver *driver = &usart_drivers[num];
	usart_t *usart = (usart_t *)driver->p_dev->reg;
	dma_stream_t *stream = (dma_stream_t *)driver->p_usart_dma->rx_stream_base;
	uint32 count;

	if (usart->SR & USART_SR_IDLE)
	{
		(void)((usart_t *)driver->p_dev->reg)->DR;

		driver->rx_tail = USART_BUFFER_SIZE - stream->NDTR;

		if(driver->rx_head > driver->rx_tail)
		{
			count = (USART_BUFFER_SIZE - driver->rx_head) + driver->rx_tail;
		}
		else
		{
			count = driver->rx_tail - driver->rx_head;
		}

		/* framing is end then callback to handler with rx buffer data */
		(*driver->rx_handler)(driver->p_owner, count);
	}
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


/**********************************************************************************
 * DMA Interrupt Service Routines Handler
 *********************************************************************************/

void
usart_dma_rx_handler(void *owner, dma_num num, dma_stream stream)
{
	usart_driver *driver = (usart_driver *)owner;
	//dma_stream_t *p_stream = (dma_stream_t *)driver->p_usart_dma->rx_stream_base;

	/* Check complete transfer interrupt flag */
	if(dma_get_it(num, stream, DMA_IT_TC) != RESET)
	{
		/* Clear pending */
		dma_clear_it_pending(num, stream, DMA_IT_TC);

		/* Reset tail of buffer */
		driver->rx_tail = 0;
	}

	/* Clear error flag */
	dma_clear_it_pending(num, stream, DMA_IT_TE);
}

void
usart_dma_tx_handler(void *owner, dma_num num, dma_stream stream)
{
	//usart_driver *driver = (usart_driver *)owner;
	//dma_stream_t *p_stream = (dma_stream_t *)driver->p_usart_dma->tx_stream_base;

	/* Check complete transfer interrupt flag */
	if(dma_get_it(num, stream, DMA_IT_TC) != RESET)
	{
		/* Clear pending */
		dma_clear_it_pending(num, stream, DMA_IT_TC);
	}
}
