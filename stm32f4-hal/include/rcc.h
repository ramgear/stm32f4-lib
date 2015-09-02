/**
 ******************************************************************************
 * @file	reg_rcc.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	28-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INCLUDE_REGISTERS_RCC_REG_H_
#define INCLUDE_REGISTERS_RCC_REG_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <cpu.h>

/* Exported types ------------------------------------------------------------*/
 /**
   * @brief Reset and Clock Control
   */
 typedef RCC_TypeDef rcc_t;

 /**
  * @brief STM32F2 clock sources.
  */
 typedef enum rcc_clk {
     RCC_CLK_PLLI2S = (uint16)((offsetof(rcc_t, CR) << 8) | RCC_CR_PLLI2SON), /**< Dedicated PLL for I2S. */
     RCC_CLK_PLL    = (uint16)((offsetof(rcc_t, CR) << 8) | RCC_CR_PLLON), /**< Main PLL, clocked by HSI or HSE. */
     RCC_CLK_HSE    = (uint16)((offsetof(rcc_t, CR) << 8) | RCC_CR_HSEON), /**< High speed external. */
     RCC_CLK_HSI    = (uint16)((offsetof(rcc_t, CR) << 8) | RCC_CR_HSION), /**< High speed internal. */
     RCC_CLK_LSE    = (uint16)((offsetof(rcc_t, BDCR) << 8) | RCC_BDCR_LSEON), /**< Low-speed external * (32.768 KHz). */
     RCC_CLK_LSI    = (uint16)((offsetof(rcc_t, CSR) << 8) | RCC_CSR_LSION), /**< Low-speed internal * (approximately 32 KHz). */
 } rcc_clk;

 /**
  * @brief STM32F4 rcc_clk_id.
  */
 typedef enum rcc_clk_id
 {
     RCC_ADC1,
     RCC_ADC2,
     RCC_ADC3,
     RCC_BKPSRAM,
     RCC_CAN1,
     RCC_CAN2,
     RCC_CRC,
     RCC_CRYP,
     RCC_DAC,
     RCC_DCMI,
     RCC_DMA1,
     RCC_DMA2,
     RCC_ETHMAC,
     RCC_ETHMACPTP,
     RCC_ETHMACRX,
     RCC_ETHMACTX,
     RCC_FSMC,
     RCC_GPIOA,
     RCC_GPIOB,
     RCC_GPIOC,
     RCC_GPIOD,
     RCC_GPIOE,
     RCC_GPIOF,
     RCC_GPIOG,
     RCC_GPIOH,
     RCC_GPIOI,
     RCC_HASH,
     RCC_I2C1,
     RCC_I2C2,
     RCC_I2C3,
     RCC_OTGFS,
     RCC_OTGHS,
     RCC_OTGHSULPI,
     RCC_PWR,
     RCC_RNG,
     RCC_SDIO,
     RCC_SPI1,
     RCC_SPI2,
     RCC_SPI3,
     RCC_SYSCFG,
     RCC_TIM1,
     RCC_TIM10,
     RCC_TIM11,
     RCC_TIM12,
     RCC_TIM13,
     RCC_TIM14,
     RCC_TIM2,
     RCC_TIM3,
     RCC_TIM4,
     RCC_TIM5,
     RCC_TIM6,
     RCC_TIM7,
     RCC_TIM8,
     RCC_TIM9,
     RCC_USART1,
     RCC_USART2,
     RCC_USART3,
     RCC_UART4,
     RCC_UART5,
     RCC_USART6,
     RCC_WWDG,
 } rcc_clk_id;


 /**
  * @brief STM32F4 PLL entry clock source
  * @see rcc_configure_pll()
  */
 typedef enum rcc_pllsrc
 {
     RCC_PLLSRC_HSI = 0,
     RCC_PLLSRC_HSE = RCC_PLLCFGR_PLLSRC,
 } rcc_pllsrc;

 /**
  * @brief STM32F4 Peripheral clock bus.
  */
 typedef enum rcc_clk_bus
 {
     RCC_APB1,
     RCC_APB2,
     RCC_AHB1,
     RCC_AHB2,
     RCC_AHB3,
 } rcc_clk_bus;

 /**
  * @brief STM32F4 Prescaler identifiers.
  */
 typedef enum rcc_prescaler
 {
     RCC_PRESCALER_MCO2,
     RCC_PRESCALER_MCO1,
     RCC_PRESCALER_RTC,
     RCC_PRESCALER_APB2,
     RCC_PRESCALER_APB1,
     RCC_PRESCALER_AHB
 } rcc_prescaler;

 /**
  * @brief STM32F4 MCO2 prescaler dividers.
  */
 typedef enum rcc_mco2_divider
 {
	RCC_MCO2_DIV_1 = 0,
	RCC_MCO2_DIV_2 = (4 << 27),
	RCC_MCO2_DIV_3 = (5 << 27),
	RCC_MCO2_DIV_4 = (6 << 27),
	RCC_MCO2_DIV_5 = (7 << 27),
 } rcc_mco2_divider;

 /**
  * @brief STM32F4 MCO1 prescaler dividers.
  */
 typedef enum rcc_mco1_divider
 {
	RCC_MCO1_DIV_1 = 0,
	RCC_MCO1_DIV_2 = (4 << 24),
	RCC_MCO1_DIV_3 = (5 << 24),
	RCC_MCO1_DIV_4 = (6 << 24),
	RCC_MCO1_DIV_5 = (7 << 24),
 } rcc_mco1_divider;

 /**
  * @brief STM32F4 RTC prescaler dividers.
  */
 typedef enum rcc_rtc_divider {
     RCC_RTC_DIV_DUMMY = 0xFFFFFFFF,
 } rcc_rtc_divider;

 /**
  * @brief STM32F4 AP2 prescaler dividers.
  */
 typedef enum rcc_apb2_divider
 {
     RCC_APB2_HCLK_DIV_1  = RCC_CFGR_PPRE2_DIV1,
     RCC_APB2_HCLK_DIV_2  = RCC_CFGR_PPRE2_DIV2,
     RCC_APB2_HCLK_DIV_4  = RCC_CFGR_PPRE2_DIV4,
     RCC_APB2_HCLK_DIV_8  = RCC_CFGR_PPRE2_DIV8,
     RCC_APB2_HCLK_DIV_16 = RCC_CFGR_PPRE2_DIV16,
 } rcc_apb2_divider;

 /**
  * @brief STM32F4 APB1 prescaler dividers.
  */
 typedef enum rcc_apb1_divider {
     RCC_APB1_HCLK_DIV_1  = RCC_CFGR_PPRE1_DIV1,
     RCC_APB1_HCLK_DIV_2  = RCC_CFGR_PPRE1_DIV2,
     RCC_APB1_HCLK_DIV_4  = RCC_CFGR_PPRE1_DIV4,
     RCC_APB1_HCLK_DIV_8  = RCC_CFGR_PPRE1_DIV8,
     RCC_APB1_HCLK_DIV_16 = RCC_CFGR_PPRE1_DIV16,
 } rcc_apb1_divider;

 /**
  * @brief STM32F4 AHB prescaler dividers.
  */
 typedef enum rcc_ahb_divider {
     RCC_AHB_SYSCLK_DIV_1   = RCC_CFGR_HPRE_DIV1,
     RCC_AHB_SYSCLK_DIV_2   = RCC_CFGR_HPRE_DIV2,
     RCC_AHB_SYSCLK_DIV_4   = RCC_CFGR_HPRE_DIV4,
     RCC_AHB_SYSCLK_DIV_8   = RCC_CFGR_HPRE_DIV8,
     RCC_AHB_SYSCLK_DIV_16  = RCC_CFGR_HPRE_DIV16,
     RCC_AHB_SYSCLK_DIV_64  = RCC_CFGR_HPRE_DIV64,
     RCC_AHB_SYSCLK_DIV_128 = RCC_CFGR_HPRE_DIV128,
     RCC_AHB_SYSCLK_DIV_256 = RCC_CFGR_HPRE_DIV256,
     RCC_AHB_SYSCLK_DIV_512 = RCC_CFGR_HPRE_DIV512,
 } rcc_ahb_divider;

 /**
  * @brief STM32F4 PLL configuration values.
  * Point to one of these with the "data" field in a struct rcc_pll_cfg.
  * @see struct rcc_pll_cfg.
  */
 typedef struct rcc_pll_data {
     uint08 pllq;      /**<
                       * @brief PLLQ value.
                       * Allowed values: 4, 5, ..., 15. */
     uint08 pllp;      /**<
                       * @brief PLLP value.
                       * Allowed values: 2, 4, 6, 8. */
     uint16 plln;     /**<
                       * @brief PLLN value.
                       * Allowed values: 192, 193, ..., 432. */
     uint08 pllm;      /**<
                       * @brief PLLM value.
                       * Allowed values: 2, 3, ..., 63. */
 } rcc_pll_data;

 typedef enum rcc_sysclk_src
 {
     RCC_CLKSRC_HSI = 0x0,
     RCC_CLKSRC_HSE = 0x1,
     RCC_CLKSRC_PLL = 0x2,
 } rcc_sysclk_src;

 typedef struct rcc_pll_cfg
 {
     rcc_pllsrc  	pllsrc;     /**< PLL source */

     rcc_pll_data	data;
 } rcc_pll_cfg;

/* Exported constants --------------------------------------------------------*/
#define RCC_REG			((rcc_t	*)RCC_BASE)

#if !defined  (HSE_VALUE)
  #define HSE_VALUE    ((uint32_t)8000000) /*!< Default value of the External oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined  (HSI_VALUE)
  #define HSI_VALUE    ((uint32_t)16000000) /*!< Value of the Internal oscillator in Hz*/
#endif /* HSI_VALUE */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void
rcc_configure_pll(rcc_pll_cfg *pll_cfg);

void
rcc_turn_on_clk(rcc_clk clock);
void
rcc_turn_off_clk(rcc_clk clock);
boolean
rcc_is_clk_on(rcc_clk clock);
boolean
rcc_is_clk_ready(rcc_clk clock);

void
rcc_clk_enable(rcc_clk_id id);
void
rcc_reset_dev(rcc_clk_id id);

rcc_clk_bus
rcc_dev_clk(rcc_clk_id id);

uint32
rcc_get_clk_freq(rcc_clk_id id);


/**
 * @brief Enable the clock security system (CSS).
 */
static inline void
rcc_enable_css(void)
{
    RCC_REG->CR |= RCC_CR_CSSON;
}

/**
 * @brief Disable the clock security system (CSS).
 */
static inline void
rcc_disable_css(void)
{
	RCC_REG->CR &= ~RCC_CR_CSSON;
}

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_REGISTERS_RCC_REG_H_ */

/*****************************END OF FILE**************************************/
