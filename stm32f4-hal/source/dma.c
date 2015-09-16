/**
 ******************************************************************************
 * @file	dma.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	10-Sep-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

#include <dma.h>
#include <rcc.h>
#include <nvic.h>

#define DMA_FLAG_MASK	0x3F

#define	DMA_ISR(DNUM,SNUM)	\
	void ISR_DMA##DNUM##_Stream##SNUM##_IRQHandler(void) {	\
		dma_irq_handler(DMA_##DNUM, DMA_STREAM_##SNUM);		\
	}

#define	DMA_STREAM_DEV_ENTRY(DNUM,SNUM)	\
		[DMA_##DNUM][DMA_STREAM_##SNUM]	=	{ .irq = DMA##DNUM##_Stream##SNUM##_IRQn }

typedef struct dma_stream_dev
{
	nvic_irq_num	irq;
} dma_stream_dev;

__lookup_table
uint32	dma_dev_table[] =
{
		[DMA_1] = (uint32)DMA1_BASE,
		[DMA_2] = (uint32)DMA2_BASE,
};

__lookup_table
dma_stream_dev	dma_stream_dev_table[DMA_NUM_MAX][DMA_STREAM_MAX] =
{
		DMA_STREAM_DEV_ENTRY(1,0),
		DMA_STREAM_DEV_ENTRY(1,1),
		DMA_STREAM_DEV_ENTRY(1,2),
		DMA_STREAM_DEV_ENTRY(1,3),
		DMA_STREAM_DEV_ENTRY(1,4),
		DMA_STREAM_DEV_ENTRY(1,5),
		DMA_STREAM_DEV_ENTRY(1,6),
		DMA_STREAM_DEV_ENTRY(1,7),
		DMA_STREAM_DEV_ENTRY(2,0),
		DMA_STREAM_DEV_ENTRY(2,1),
		DMA_STREAM_DEV_ENTRY(2,2),
		DMA_STREAM_DEV_ENTRY(2,3),
		DMA_STREAM_DEV_ENTRY(2,4),
		DMA_STREAM_DEV_ENTRY(2,5),
		DMA_STREAM_DEV_ENTRY(2,6),
		DMA_STREAM_DEV_ENTRY(2,7),
};

__lookup_table
uint32	dma_stream_flag_table[] =
{
		[DMA_STREAM_0] = 0xF << 1,
		[DMA_STREAM_1] = 0xF << 7,
		[DMA_STREAM_2] = 0xF << 17,
		[DMA_STREAM_3] = 0xF << 23,
		[DMA_STREAM_4] = 0xF << 1,
		[DMA_STREAM_5] = 0xF << 7,
		[DMA_STREAM_6] = 0xF << 17,
		[DMA_STREAM_7] = 0xF << 23,
};

uint32				dma_irq_owners[DMA_NUM_MAX][DMA_STREAM_MAX][DMA_CHANNEL_MAX];
dma_irq_handler_t	dma_irq_handlers[DMA_NUM_MAX][DMA_STREAM_MAX][DMA_CHANNEL_MAX];

void
dma_clk_enable(dma_num num)
{
	rcc_clk_enable(num == DMA_1 ? RCC_DMA1 : RCC_DMA2);
}

void
dma_set_irq_enable(dma_num num, dma_stream stream, uint32 stat)
{
	const dma_stream_dev *dev = &dma_stream_dev_table[num][stream];

	if(stat != DISABLE)
	{
		nvic_irq_enable(dev->irq);
	}
	else
	{
		nvic_irq_disable(dev->irq);
	}
}

void
dma_set_it(dma_stream_t *stream, dma_it flag, uint32 stat)
{
	if(stat != DISABLE)
		stream->CR	|= flag;
	else
		stream->CR	&= ~flag;
}

uint32
dma_get_it(dma_num num, dma_stream stream, dma_it flag)
{
	dma_t *dma = (dma_t *)dma_dev_table[num];
	uint32 tmp;

	if(stream < DMA_STREAM_4)
	{
		tmp =  dma->LISR;
	}
	else
	{
		tmp =  dma->HISR;
	}

	tmp >>= CPU_POS_OF(dma_stream_flag_table[stream]);
	if((tmp & flag) != RESET)
		return SET;
	else
		return RESET;
}

void
dma_clear_it_pending(dma_num num, dma_stream stream, dma_it flag)
{
	dma_t *dma = (dma_t *)dma_dev_table[num];

	if(stream < DMA_STREAM_4)
	{
		dma->LIFCR |= (flag << CPU_POS_OF(dma_stream_flag_table[stream]));
	}
	else
	{
		dma->HIFCR |= (flag << CPU_POS_OF(dma_stream_flag_table[stream]));
	}
}

void
dma_clear_stream_flags(dma_num num, dma_stream stream)
{
	dma_t *dma = (dma_t *)dma_dev_table[num];

	if(stream < DMA_STREAM_4)
	{
		dma->LIFCR |= (DMA_FLAG_MASK << (6 * stream + 1));
	}
	else
	{
		dma->HIFCR |= (DMA_FLAG_MASK << (6 * (stream % 4) + 1));
	}
}

dma_stream_t *
dma_get_stream(dma_num num, dma_stream stream)
{
	return (dma_stream_t *)(dma_dev_table[num] + 0x10 + 0x18 * stream);
}

void
dma_set_stream(dma_stream_t *stream, uint32 stat)
{
	if(stat != DISABLE)
		stream->CR	|= DMA_SxCR_EN;
	else
		stream->CR	&= ~DMA_SxCR_EN;
}

void
dma_set_direct_mode(dma_stream_t *stream, uint32 stat)
{
	if(stat != DISABLE)
		stream->FCR	&= ~DMA_SxFCR_DMDIS;
	else
		stream->FCR	|= DMA_SxFCR_DMDIS;
}

void
dma_set_paddr(dma_stream_t *stream, uint32 addr)
{
	stream->PAR = addr;
}

void
dma_set_m0addr(dma_stream_t *stream, uint32 addr)
{
	stream->M0AR = addr;
}

void
dma_set_m1addr(dma_stream_t *stream, uint32 addr)
{
	stream->M1AR = addr;
}

void
dma_set_fifo_threshold(dma_stream_t *stream, dma_fifo_threshold threshold)
{
	CPU_MOD_REG(stream->FCR, DMA_SxFCR_FTH, threshold);
}

void
dma_set_channel(dma_stream_t *stream, dma_channel channel)
{
	CPU_MOD_REG(stream->CR, DMA_SxCR_CHSEL, channel);
}

void
dma_set_mburst(dma_stream_t *stream, dma_burst burst)
{
	CPU_MOD_REG(stream->CR, DMA_SxCR_MBURST, burst);
}

void
dma_set_pburst(dma_stream_t *stream, dma_burst burst)
{
	CPU_MOD_REG(stream->CR, DMA_SxCR_PBURST, burst);
}

void
dma_set_current_buffer(dma_stream_t *stream, dma_buffer buffer)
{
	CPU_MOD_REG(stream->CR, DMA_SxCR_CT, buffer);
}

void
dma_set_double_buffer(dma_stream_t *stream, uint32 stat)
{
	CPU_MOD_REG(stream->CR, DMA_SxCR_DBM, stat);
}

void
dma_set_priority(dma_stream_t *stream, dma_priority piority)
{
	CPU_MOD_REG(stream->CR, DMA_SxCR_PL, piority);
}

void
dma_set_pinc_offset(dma_stream_t *stream, uint32 offset)
{
	CPU_MOD_REG(stream->CR, DMA_SxCR_PINCOS, offset);
}

void
dma_set_pinc_size(dma_stream_t *stream, dma_data_size size)
{
	CPU_MOD_REG(stream->CR, DMA_SxCR_PSIZE, size);
}

void
dma_set_minc_size(dma_stream_t *stream, dma_data_size size)
{
	CPU_MOD_REG(stream->CR, DMA_SxCR_MSIZE, size);
}

void
dma_set_minc_mode(dma_stream_t *stream, uint32 stat)
{
	CPU_MOD_REG(stream->CR, DMA_SxCR_MINC, stat);
}

void
dma_set_pinc_mode(dma_stream_t *stream, uint32 stat)
{
	CPU_MOD_REG(stream->CR, DMA_SxCR_PINC, stat);
}

void
dma_set_circular_mode(dma_stream_t *stream, uint32 stat)
{
	CPU_MOD_REG(stream->CR, DMA_SxCR_CIRC, stat);
}

void
dma_set_direction(dma_stream_t *stream, dma_direction direction)
{
	CPU_MOD_REG(stream->CR, DMA_SxCR_DIR, direction);
}

void
dma_set_flow_ctrl(dma_stream_t *stream, uint32 stat)
{
	CPU_MOD_REG(stream->CR, DMA_SxCR_PFCTRL, stat);
}

void
dma_set_data_size(dma_stream_t *stream, uint32 size)
{
	CPU_MOD_REG(stream->NDTR, DMA_SxNDT, size);
}

boolean
dma_set_handler(dma_num num, dma_stream stream, dma_channel channel, dma_irq_handler_t handler, void *owner)
{
	if(dma_irq_owners[num][stream][channel] != 0)
	{
		return false;
	}

	dma_irq_owners[num][stream][channel] = (uint32)owner;
	dma_irq_handlers[num][stream][channel] = handler;

	return true;
}


/**********************************************************************************
 * USART Interrupt Service Routines Handler
 *********************************************************************************/
static void
dma_irq_handler(dma_num num, dma_stream stream)
{
	const dma_stream_dev *dev = &dma_stream_dev_table[num][stream];
	dma_stream_t *p_stream = dma_get_stream(num, stream);
	dma_irq_handler_t handler;
	uint32 channel;

	/* Get current channel */
	channel = CPU_GET_VAL(p_stream->CR, DMA_SxCR_CHSEL);

	/* Check call back handler */
	handler = dma_irq_handlers[num][stream][channel];
	if(handler != NULL)
	{
		(*handler)((void *)dma_irq_owners[num][stream][channel], num, stream);
	}
}

DMA_ISR(1,0)
DMA_ISR(1,1)
DMA_ISR(1,2)
DMA_ISR(1,3)
DMA_ISR(1,4)
DMA_ISR(1,5)
DMA_ISR(1,6)
DMA_ISR(1,7)
DMA_ISR(2,0)
DMA_ISR(2,1)
DMA_ISR(2,2)
DMA_ISR(2,3)
DMA_ISR(2,4)
DMA_ISR(2,5)
DMA_ISR(2,6)
DMA_ISR(2,7)
