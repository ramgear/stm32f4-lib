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

#define	RCC_CLK_CHANGE_TIMEOUT	5000


#if !defined  (HSE_VALUE)
  #define HSE_VALUE    ((uint32_t)8000000) /*!< Default value of the External oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined  (HSI_VALUE)
  #define HSI_VALUE    ((uint32_t)16000000) /*!< Value of the Internal oscillator in Hz*/
#endif /* HSI_VALUE */

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

uint32	rcc_sys_clk_freq = 168000000;

const uint8_t RCC_APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};

/*
 * **********************************************************
 * Internal functions
 * **********************************************************
 */
static inline __io uint32*
rcc_clk_reg(rcc_clk clock)
{
    return (__io uint32*)(RCC_BASE + (clock >> RCC_CLK_BASE_OFF));
}

static inline uint32
rcc_clk_on_mask(rcc_clk clock)
{
    return (1 << (clock & 0xFF));
}

static inline uint32
rcc_clk_ready_mask(rcc_clk clock)
{
    return (rcc_clk_on_mask(clock) << 1);
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

static inline boolean
rcc_wait_clk_change(rcc_clk clock, boolean ready)
{
	uint32 counter = 0;
	while(rcc_is_clk_ready(clock) != ready)
	{
		if(++counter > RCC_CLK_CHANGE_TIMEOUT)
			return false;
	}

	return true;
}

/*
 * **********************************************************
 * Global functions
 * **********************************************************
 */
rcc_clk_bus
rcc_dev_clk(rcc_clk_id id)
{
    return rcc_dev_table[id].clk_bus;
}

boolean
rcc_turn_on_clk(rcc_clk clock)
{
	/* Turn on clock */
	*rcc_clk_reg(clock) |= rcc_clk_on_mask(clock);

	/* Wait till clock ready */
	return rcc_wait_clk_change(clock, true);
}

boolean
rcc_turn_off_clk(rcc_clk clock)
{
	/* Turn off clock */
	*rcc_clk_reg(clock) &= ~rcc_clk_on_mask(clock);

	/* Wait till clock reset */
	return rcc_wait_clk_change(clock, false);
}

boolean
rcc_is_clk_on(rcc_clk clock)
{
    return !!(*rcc_clk_reg(clock) & rcc_clk_on_mask(clock));
}

boolean
rcc_is_clk_ready(rcc_clk clock)
{
    return !!(*rcc_clk_reg(clock) & rcc_clk_ready_mask(clock));
}

void
rcc_set_pllsrc(rcc_pllsrc pllsrc)
{
	CPU_MOD_REG(RCC_REG->PLLCFGR, RCC_PLLCFGR_PLLSRC, pllsrc);
}

void
rcc_configure_pll(uint32 plln, uint32 pllm, uint32 pllp, uint32 pllq)
{
    uint32 pllcfgr;

    /* Update RCC_PLLCFGR to reflect new values. */
    pllcfgr = RCC_REG->PLLCFGR;
    pllcfgr &= ~(RCC_PLLCFGR_PLLQ |
                 RCC_PLLCFGR_PLLP |
                 RCC_PLLCFGR_PLLN |
                 RCC_PLLCFGR_PLLM );
    pllcfgr |= ((pllq << CPU_POS_OF(RCC_PLLCFGR_PLLQ)) |
    		(((pllp >> 1) - 1) << CPU_POS_OF(RCC_PLLCFGR_PLLP)) |
			(plln << CPU_POS_OF(RCC_PLLCFGR_PLLN)) |
			pllm);
    RCC_REG->PLLCFGR = pllcfgr;
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

boolean
rcc_switch_sysclk(rcc_sysclk_src sysclk_src)
{
	uint32 counter = 0;

	CPU_MOD_REG(RCC_REG->CFGR, RCC_CFGR_SW, sysclk_src);

    /* Wait for new source to come into use. */
    while (((RCC_REG->CFGR & RCC_CFGR_SWS) >> CPU_POS_OF(RCC_CFGR_SWS)) != sysclk_src)
    {
		if(++counter > RCC_CLK_CHANGE_TIMEOUT)
			return false;
    }

	return true;
}

inline uint32
rcc_get_sys_clk_freq(void)
{
	return rcc_sys_clk_freq;
}

uint32
rcc_get_clk_freq(rcc_clk_id id)
{
	rcc_clk_bus clk_bus = rcc_dev_clk(id);
	uint32	sys_clk = RCC_SYSTEM_CLOCK;
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

void
rcc_clk_update(void)
{
	  uint32_t tmp = 0, pllvco = 0, pllp = 2, pllsource = 0, pllm = 2;

	  /* Get SYSCLK source -------------------------------------------------------*/
	  tmp = RCC_REG->CFGR & RCC_CFGR_SWS;

	  switch (tmp)
	  {
	    case 0x00:  /* HSI used as system clock source */
	    	rcc_sys_clk_freq = HSI_VALUE;
	      break;
	    case 0x04:  /* HSE used as system clock source */
	    	rcc_sys_clk_freq = HSE_VALUE;
	      break;
	    case 0x08:  /* PLL used as system clock source */

	      /* PLL_VCO = (HSE_VALUE or HSI_VALUE / PLL_M) * PLL_N
	         SYSCLK = PLL_VCO / PLL_P
	         */
	      pllsource = (RCC_REG->PLLCFGR & RCC_PLLCFGR_PLLSRC) >> 22;
	      pllm = RCC_REG->PLLCFGR & RCC_PLLCFGR_PLLM;

	      if (pllsource != 0)
	      {
	        /* HSE used as PLL clock source */
	        pllvco = (HSE_VALUE / pllm) * ((RCC_REG->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
	      }
	      else
	      {
	        /* HSI used as PLL clock source */
	        pllvco = (HSI_VALUE / pllm) * ((RCC_REG->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
	      }

	      pllp = (((RCC_REG->PLLCFGR & RCC_PLLCFGR_PLLP) >>16) + 1 ) *2;
	      rcc_sys_clk_freq = pllvco/pllp;
	      break;
	    default:
	    	rcc_sys_clk_freq = HSI_VALUE;
	      break;
	  }
	  /* Compute HCLK frequency --------------------------------------------------*/
	  /* Get HCLK prescaler */
	  tmp = RCC_APBAHBPrescTable[((RCC_REG->CFGR & RCC_CFGR_HPRE) >> 4)];
	  /* HCLK frequency */
	  rcc_sys_clk_freq >>= tmp;
}

void
rcc_reset(void)
{
	/* Reset the RCC clock configuration to the default reset state */

	/* turn on HSI*/
	rcc_turn_on_clk(RCC_CLK_HSI);

	/* Reset CFGR register */
	RCC_REG->CFGR = 0x00000000;

	/* Reset HSEON, CSSON and PLLON bits */
	RCC_REG->CR &= (uint32_t)0xFEF6FFFF;

	/* Reset PLLCFGR register */
	RCC_REG->PLLCFGR = 0x24003010;

	/* Reset HSEBYP bit */
	RCC_REG->CR &= (uint32_t)0xFFFBFFFF;

	/* Disable all interrupts */
	RCC_REG->CIR = 0x00000000;
}
