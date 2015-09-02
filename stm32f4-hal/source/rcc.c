/**
 ******************************************************************************
 * @file	rcc.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	28-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

#include <rcc.h>

#define RCC_DEV_ENTRY(bus, dev) \
    [RCC_##dev] = {.clk_bus = RCC_##bus, .mask = RCC_##bus##ENR_##dev##EN}

typedef struct rcc_dev_info
{
    const rcc_clk_bus	clk_bus;
    const uint32 		mask;
} rcc_dev_info;

__lookup_table
rcc_dev_info rcc_dev_table[] =
{
	    RCC_DEV_ENTRY(AHB1, OTGHSULPI),
	    RCC_DEV_ENTRY(AHB1, OTGHS),
	    RCC_DEV_ENTRY(AHB1, ETHMACPTP),
	    RCC_DEV_ENTRY(AHB1, ETHMACRX),
	    RCC_DEV_ENTRY(AHB1, ETHMACTX),
	    RCC_DEV_ENTRY(AHB1, ETHMAC),
	    RCC_DEV_ENTRY(AHB1, DMA2),
	    RCC_DEV_ENTRY(AHB1, DMA1),
	    RCC_DEV_ENTRY(AHB1, BKPSRAM),
	    RCC_DEV_ENTRY(AHB1, CRC),
	    RCC_DEV_ENTRY(AHB1, GPIOI),
	    RCC_DEV_ENTRY(AHB1, GPIOH),
	    RCC_DEV_ENTRY(AHB1, GPIOG),
	    RCC_DEV_ENTRY(AHB1, GPIOF),
	    RCC_DEV_ENTRY(AHB1, GPIOE),
	    RCC_DEV_ENTRY(AHB1, GPIOD),
	    RCC_DEV_ENTRY(AHB1, GPIOC),
	    RCC_DEV_ENTRY(AHB1, GPIOB),
	    RCC_DEV_ENTRY(AHB1, GPIOA),

	    RCC_DEV_ENTRY(AHB2, OTGFS),
	    RCC_DEV_ENTRY(AHB2, RNG),
	    RCC_DEV_ENTRY(AHB2, DCMI),

	    RCC_DEV_ENTRY(AHB3, FSMC),

	    RCC_DEV_ENTRY(APB1, DAC),
	    RCC_DEV_ENTRY(APB1, PWR),
	    RCC_DEV_ENTRY(APB1, CAN2),
	    RCC_DEV_ENTRY(APB1, CAN1),
	    RCC_DEV_ENTRY(APB1, I2C3),
	    RCC_DEV_ENTRY(APB1, I2C2),
	    RCC_DEV_ENTRY(APB1, I2C1),
	    RCC_DEV_ENTRY(APB1, UART5),
	    RCC_DEV_ENTRY(APB1, UART4),
	    RCC_DEV_ENTRY(APB1, USART3),
	    RCC_DEV_ENTRY(APB1, USART2),
	    RCC_DEV_ENTRY(APB1, SPI3),
	    RCC_DEV_ENTRY(APB1, SPI2),
	    RCC_DEV_ENTRY(APB1, WWDG),
	    RCC_DEV_ENTRY(APB1, TIM14),
	    RCC_DEV_ENTRY(APB1, TIM13),
	    RCC_DEV_ENTRY(APB1, TIM12),
	    RCC_DEV_ENTRY(APB1, TIM7),
	    RCC_DEV_ENTRY(APB1, TIM6),
	    RCC_DEV_ENTRY(APB1, TIM5),
	    RCC_DEV_ENTRY(APB1, TIM4),
	    RCC_DEV_ENTRY(APB1, TIM3),
	    RCC_DEV_ENTRY(APB1, TIM2),

	    RCC_DEV_ENTRY(APB2, TIM11),
	    RCC_DEV_ENTRY(APB2, TIM10),
	    RCC_DEV_ENTRY(APB2, TIM9),
	    RCC_DEV_ENTRY(APB2, SYSCFG),
	    RCC_DEV_ENTRY(APB2, SPI1),
	    RCC_DEV_ENTRY(APB2, SDIO),
	    RCC_DEV_ENTRY(APB2, ADC3),
	    RCC_DEV_ENTRY(APB2, ADC2),
	    RCC_DEV_ENTRY(APB2, ADC1),
	    RCC_DEV_ENTRY(APB2, USART6),
	    RCC_DEV_ENTRY(APB2, USART1),
	    RCC_DEV_ENTRY(APB2, TIM8),
	    RCC_DEV_ENTRY(APB2, TIM1),
};

static volatile uint32	RCC_SysClock = 168000000;

const uint8_t RCC_APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};

rcc_clk_bus
rcc_dev_clk(rcc_clk_id id) {
    return rcc_dev_table[id].clk_bus;
}

static inline void
rcc_do_clk_enable(reg32 **enable_regs, rcc_clk_id id)
{
	reg32 *reg = enable_regs[rcc_dev_clk(id)];
    uint32 mask = rcc_dev_table[id].mask;

    *reg	|= mask;
}

static inline void
rcc_do_reset_dev(reg32 **reset_regs, rcc_clk_id id)
{
	reg32 *reg = reset_regs[rcc_dev_clk(id)];
    uint32 mask = rcc_dev_table[id].mask;

    *reg	&= ~mask;
}

static inline void
rcc_do_set_prescaler(const uint32 *masks, rcc_prescaler prescaler, uint32 divider)
{
    uint32 cfgr = RCC_REG->CFGR;
    cfgr &= ~masks[prescaler];
    cfgr |= divider;
    RCC_REG->CFGR = cfgr;
}

void rcc_clk_enable(rcc_clk_id id)
{
    static reg32 *enable_regs[] =
    {
        [RCC_AHB1] = &RCC_REG->AHB1ENR,
        [RCC_AHB2] = &RCC_REG->AHB2ENR,
        [RCC_APB1] = &RCC_REG->APB1ENR,
        [RCC_APB2] = &RCC_REG->APB2ENR,
    };

    rcc_do_clk_enable(enable_regs, id);
}

void
rcc_reset_dev(rcc_clk_id id)
{
    static reg32 *reset_regs[] =
    {
        [RCC_AHB1] = &RCC_REG->AHB1RSTR,
        [RCC_AHB2] = &RCC_REG->AHB2RSTR,
        [RCC_APB1] = &RCC_REG->AHB3RSTR,
        [RCC_APB2] = &RCC_REG->AHB3RSTR,
    };

    rcc_do_reset_dev(reset_regs, id);
}

void
rcc_set_prescaler(rcc_prescaler prescaler, uint32 divider)
{
    static const uint32 masks[] =
    {
        [RCC_PRESCALER_MCO2] = RCC_CFGR_MCO2PRE,
        [RCC_PRESCALER_MCO1] = RCC_CFGR_MCO1PRE,
        [RCC_PRESCALER_RTC] = RCC_CFGR_RTCPRE,
        [RCC_PRESCALER_APB2] = RCC_CFGR_PPRE2,
        [RCC_PRESCALER_APB1] = RCC_CFGR_PPRE1,
        [RCC_PRESCALER_AHB] = RCC_CFGR_HPRE,
    };

    rcc_do_set_prescaler(masks, prescaler, divider);
}

/* pll_cfg->data must point to a struct stm32f2_rcc_pll_data. */
void
rcc_configure_pll(rcc_pll_cfg *pll_cfg)
{
    rcc_pll_data *data = &pll_cfg->data;
    uint32 pllcfgr;

    /* Check that the PLL is disabled. */
    ASSERT_FAULT(!rcc_is_clk_on(RCC_CLK_PLL));

    /* Sanity-check all the parameters */
    ASSERT_FAULT((data->pllq >= 4) && (data->pllq <= 15));
    ASSERT_FAULT((data->pllp >= 2) && (data->pllp <= 8));
    ASSERT_FAULT(!(data->pllp & 1));
    ASSERT_FAULT((data->plln >= 192) && (data->plln <= 432));
    ASSERT_FAULT((data->pllm >= 2) && (data->pllm <= 63));

    /* Update RCC_PLLCFGR to reflect new values. */
    pllcfgr = RCC_REG->PLLCFGR;
    pllcfgr &= ~(RCC_PLLCFGR_PLLQ |
                 RCC_PLLCFGR_PLLP |
                 RCC_PLLCFGR_PLLN |
                 RCC_PLLCFGR_PLLM |
                 RCC_PLLCFGR_PLLSRC);
    pllcfgr |= (pll_cfg->pllsrc |
                (data->pllq << 24) |
                (((data->pllp >> 1) - 1) << 16) |
                (data->plln << 6) |
                data->pllm);
    RCC_REG->PLLCFGR = pllcfgr;

    /* Update clocks setting value */
    RCC_SysClock	= (HSE_VALUE / data->pllm) * data->plln / data->pllp;
}

static inline uint32
rcc_get_sys_clk_freq(void)
{
	RCC_SysClock = SystemCoreClock;

	return RCC_SysClock;
}

uint32
rcc_get_clk_freq(rcc_clk_id id)
{
	rcc_clk_bus clk_bus = rcc_dev_clk(id);
	uint32	sys_clk = rcc_get_sys_clk_freq();
	uint32	pre = 0;

	switch(clk_bus)
	{
	case RCC_APB1:
		pre = RCC_APBAHBPrescTable[(RCC_REG->CFGR & RCC_CFGR_PPRE1) >> CPU_POS_OF(RCC_CFGR_PPRE1)];
		break;
	case RCC_APB2:
		pre = RCC_APBAHBPrescTable[(RCC_REG->CFGR & RCC_CFGR_PPRE2) >> CPU_POS_OF(RCC_CFGR_PPRE2)];
		break;
	default:
		pre = RCC_APBAHBPrescTable[(RCC_REG->CFGR & RCC_CFGR_HPRE) >> CPU_POS_OF(RCC_CFGR_HPRE)];
		break;
	}

	return (sys_clk >> pre);
}
