/**
 ******************************************************************************
 * @file	dma.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	07-Sep-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INCLUDE_DMA_H_
#define INCLUDE_DMA_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <cpu.h>

/* Exported types ------------------------------------------------------------*/
typedef DMA_TypeDef				dma_t;
typedef DMA_Stream_TypeDef		dma_stream_t;

typedef enum dma_direction
{
	DMA_DIR_PER_TO_MEM		= 0x0,
	DMA_DIR_MEM_TO_PER		= 0x1,
	DMA_DIR_MEM_TO_MEM		= 0x2,
} dma_direction;

typedef enum dma_num
{
	DMA_1,
	DMA_2,
} dma_num;

typedef enum dma_stream
{
	DMA_STREAM_0,
	DMA_STREAM_1,
	DMA_STREAM_2,
	DMA_STREAM_3,
	DMA_STREAM_4,
	DMA_STREAM_5,
	DMA_STREAM_6,
	DMA_STREAM_7,
} dma_stream;

typedef enum dma_channel
{
	DMA_CHANNEL_0,
	DMA_CHANNEL_1,
	DMA_CHANNEL_2,
	DMA_CHANNEL_3,
	DMA_CHANNEL_4,
	DMA_CHANNEL_5,
	DMA_CHANNEL_6,
	DMA_CHANNEL_7,
} dma_channel;

typedef enum dma_it
{
	DMA_IT_DME	= 0x00000002,
	DMA_IT_TE	= 0x00000004,
	DMA_IT_HT	= 0x00000008,
	DMA_IT_TC	= 0x00000010,
	DMA_IT_FE	= 0x00000080,
} dma_it;

typedef enum dma_fifo_threshold
{
	DMA_FIFO_TH_1_4,
	DMA_FIFO_TH_2_4,
	DMA_FIFO_TH_3_4,
	DMA_FIFO_TH_FULL,
} dma_fifo_threshold;

typedef enum dma_burst
{
	DMA_BURST_1,
	DMA_BURST_4,
	DMA_BURST_8,
	DMA_BURST_16,
} dma_burst;

typedef enum dma_buffer
{
	DMA_BUFFER_0,
	DMA_BUFFER_1,
} dma_buffer;

typedef enum dma_priority
{
	DMA_PRIO_LOW,
	DMA_PRIO_MEDIUM,
	DMA_PRIO_HIGH,
	DMA_PRIO_VERY_HIGN,
} dma_priority;

typedef enum dma_data_size
{
	DMA_DATA_SIZE_8,
	DMA_DATA_SIZE_16,
	DMA_DATA_SIZE_32,
} dma_data_size;

typedef	void (*dma_irq_handler_t)(dma_num num, dma_stream stream);

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
dma_stream_t *
dma_get_stream_reg(dma_num num, dma_stream stream);

void
dma_set_it(dma_stream_t *stream, dma_it flag, uint32 stat);

void
dma_set_stream(dma_stream_t *stream, uint32 stat);

void
dma_set_direct_mode(dma_stream_t *stream, uint32 stat);

void
dma_set_paddr(dma_stream_t *stream, uint32 addr);

void
dma_set_m0addr(dma_stream_t *stream, uint32 addr);

void
dma_set_m1addr(dma_stream_t *stream, uint32 addr);

void
dma_set_fifo_threshold(dma_stream_t *stream, dma_fifo_threshold threshold);

void
dma_set_channel(dma_stream_t *stream, dma_channel channel);

void
dma_set_mburst(dma_stream_t *stream, dma_burst burst);

void
dma_set_pburst(dma_stream_t *stream, dma_burst burst);

void
dma_set_current_buffer(dma_stream_t *stream, dma_buffer buffer);

void
dma_set_double_buffer(dma_stream_t *stream, uint32 stat);

void
dma_set_priority(dma_stream_t *stream, dma_priority piority);

void
dma_set_pinc_offset(dma_stream_t *stream, uint32 offset);

void
dma_set_pinc_size(dma_stream_t *stream, dma_data_size size);

void
dma_set_minc_size(dma_stream_t *stream, dma_data_size size);

void
dma_set_minc_mode(dma_stream_t *stream, uint32 stat);

void
dma_set_pinc_mode(dma_stream_t *stream, uint32 stat);

void
dma_set_circular_mode(dma_stream_t *stream, uint32 stat);

void
dma_set_direction(dma_stream_t *stream, dma_direction direction);

void
dma_set_flow_ctrl(dma_stream_t *stream, uint32 stat);

void
dma_set_data_size(dma_stream_t *stream, uint32 size);

boolean
dma_set_handler(dma_num num, dma_stream stream, dma_irq_handler_t handler);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_DMA_H_ */

/*****************************END OF FILE**************************************/
