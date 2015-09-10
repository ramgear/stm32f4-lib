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

#define	USART_DMA_ENTRY(SNUM,DNUM,DSRX,DCRX,DSTX,DCTX)	\
	[SERIAL##SNUM]	=	{ .dma = DMA_##DNUM, .dma_stream_rx = DMA_STREAM_##DSRX, .dma_channel_rx = DMA_CHANNEL_##DCRX, \
			.dma_stream_tx = DMA_STREAM_##DSTX, .dma_channel_tx = DMA_CHANNEL_##DCTX}

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

typedef struct usart_driver
{
	const usart_dev		*p_dev;
	void 				*p_owner;
	usart_rx_handler	rx_handler;
	usart_tx_handler	tx_handler;
	uint08				rx_buffer[USART_BUFFER_SIZE];
	uint08				tx_buffer[USART_BUFFER_SIZE];
} usart_driver;

typedef struct usart_dma
{
	dma_num			dma;
	dma_stream		dma_stream_rx;
	dma_channel		dma_channel_rx;
	dma_stream		dma_stream_tx;
	dma_channel		dma_channel_tx;
} usart_dma;

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
usart_dma_rx_handler(dma_num num, dma_stream stream);
void
usart_dma_tx_handler(dma_num num, dma_stream stream);

void
usart_dma_init(usart_num num)
{
	usart_driver	*driver = &usart_drivers[num];
	const usart_dma *dma = &usart_dma_table[num];
	usart_t *usart = (usart_t *)driver->p_dev->reg;

	/* Initial RX DMA */
	dma_stream_t	*rx_stream = dma_get_stream_reg(dma->dma, dma->dma_stream_rx);
	dma_set_channel(rx_stream, dma->dma_channel_rx);
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
	dma_set_direct_mode(rx_stream, DISABLE);
	dma_set_fifo_threshold(rx_stream, DMA_FIFO_TH_FULL);
	dma_set_mburst(rx_stream, DMA_BURST_1);
	dma_set_pburst(rx_stream, DMA_BURST_1);

	dma_set_handler(dma->dma, dma->dma_stream_rx, usart_dma_rx_handler);
	dma_set_it(rx_stream, DMA_IT_TC, ENABLE);
	dma_set_stream(rx_stream, ENABLE);

	/* Initial TX DMA */
	dma_stream_t	*tx_stream = dma_get_stream_reg(dma->dma, dma->dma_stream_tx);
	dma_set_channel(tx_stream, dma->dma_channel_tx);
	dma_set_paddr(tx_stream, (uint32)&usart->DR);
	dma_set_m0addr(tx_stream, (uint32)driver->tx_buffer);
	dma_set_direction(tx_stream, DMA_DIR_MEM_TO_PER);
	dma_set_data_size(tx_stream, USART_BUFFER_SIZE);
	dma_set_pinc_mode(tx_stream, DISABLE);
	dma_set_minc_mode(tx_stream, ENABLE);
	dma_set_minc_size(tx_stream, DMA_DATA_SIZE_8);
	dma_set_pinc_size(tx_stream, DMA_DATA_SIZE_8);
	dma_set_circular_mode(tx_stream, ENABLE);
	dma_set_priority(tx_stream, DMA_PRIO_HIGH);
	dma_set_direct_mode(tx_stream, DISABLE);
	dma_set_fifo_threshold(tx_stream, DMA_FIFO_TH_FULL);
	dma_set_mburst(tx_stream, DMA_BURST_1);
	dma_set_pburst(tx_stream, DMA_BURST_1);

	dma_set_handler(dma->dma, dma->dma_stream_tx, usart_dma_tx_handler);
	dma_set_it(tx_stream, DMA_IT_TC, ENABLE);
	dma_set_stream(tx_stream, ENABLE);
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
	usart->CR1	= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE | USART_CR1_IDLEIE;

	/* Parity: none, stop bit: 0, flow control: none */
	usart->CR2	= 0;

	/* Enable TX/RX DMA */
	usart->CR3	= USART_CR3_DMAT | USART_CR3_DMAR;

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

static void
usart_irq_handler(usart_num num)
{
	usart_driver *driver = &usart_drivers[num];
	usart_t *usart = (usart_t *)driver->p_dev->reg;

	if (usart->SR & USART_SR_IDLE)
	{
		//usart->CR1	&= ~USART_CR1_IDLEIE;
		char data = (char)((usart_t *)driver->p_dev->reg)->DR;
		(void)data;

		/* framing is end then callback to handler with rx buffer data */
		(*driver->rx_handler)(driver->p_owner, driver->rx_buffer, 0);

		/* Clear received buffer */
		memset(driver->rx_buffer, 0, USART_BUFFER_SIZE);
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
usart_dma_rx_handler(dma_num num, dma_stream stream)
{

}

void
usart_dma_tx_handler(dma_num num, dma_stream stream)
{

}
