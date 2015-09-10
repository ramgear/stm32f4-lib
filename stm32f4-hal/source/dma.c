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

#define	DMA_ISR(DNUM,SNUM)	\
	void ISR_DMA##DNUM##_Stream##SNUM##_IRQHandler(void) {	\
		dma_irq_handler(DMA_##DNUM, DMA_STREAM_##SNUM);		\
	}

__lookup_table
uint32	dma_dev_table[] =
{
		[DMA_1] = (uint32)DMA1_BASE,
		[DMA_2] = (uint32)DMA2_BASE,
};

dma_irq_handler_t	dma_irq_handlers[2][8];

dma_stream_t *
dma_get_stream_reg(dma_num num, dma_stream stream)
{
	return (dma_stream_t *)(dma_dev_table[num] + 0x10 + 0x18 * stream);
}

void
dma_set_it(dma_stream_t *stream, dma_it flag, uint32 stat)
{
	if(flag & DMA_IT_FE)
	{
		if(stat != DISABLE)
			stream->FCR	|= flag;
		else
			stream->FCR	&= ~flag;
	}
	else
	{
		if(stat != DISABLE)
			stream->CR	|= flag;
		else
			stream->CR	&= ~flag;
	}
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
		stream->FCR	|= DMA_SxFCR_DMDIS;
	else
		stream->FCR	&= ~DMA_SxFCR_DMDIS;
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
dma_set_handler(dma_num num, dma_stream stream, dma_irq_handler_t handler)
{
	if(dma_irq_handlers[num][stream] != NULL)
	{
		return false;
	}

	dma_irq_handlers[num][stream] = handler;

	return true;
}


/**********************************************************************************
 * USART Interrupt Service Routines Handler
 *********************************************************************************/
static void
dma_irq_handler(dma_num num, dma_stream stream)
{
	dma_irq_handler_t handler = dma_irq_handlers[num][stream];

	/* Check call back handler */
	if(handler != NULL)
	{
		(*handler)(num, stream);
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
