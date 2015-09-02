/**
 * @file	exti.c
 * @brief	Framework header file.
 * @details	Framework header file.
 * @version	1.0
 * @date	Aug 29, 2015
 * @author	Eakkasit L.
 * @bug		No known bug
 * @warning	Improper use can crash your application
 * @copyright	GNU Public License.
 */


#include <exti.h>
#include <nvic.h>

typedef struct exti_dev
{
	nvic_irq_num	irq;
} exti_dev;

typedef struct exti_driver
{
	const gpio_pin_dev	*p_dev;
	void 				*p_owner;
	irq_callback_t		irq_handler;
} exti_driver;

__lookup_table
exti_dev exti_dev_table[] =
{
		[EXTI_0]	= { EXTI0_IRQn },
		[EXTI_1]	= { EXTI1_IRQn },
		[EXTI_2]	= { EXTI2_IRQn },
		[EXTI_3]	= { EXTI3_IRQn },
		[EXTI_4]	= { EXTI4_IRQn },
		[EXTI_5]	= { EXTI9_5_IRQn },
		[EXTI_6]	= { EXTI9_5_IRQn },
		[EXTI_7]	= { EXTI9_5_IRQn },
		[EXTI_8]	= { EXTI9_5_IRQn },
		[EXTI_9]	= { EXTI9_5_IRQn },
		[EXTI_10]	= { EXTI15_10_IRQn },
		[EXTI_11]	= { EXTI15_10_IRQn },
		[EXTI_12]	= { EXTI15_10_IRQn },
		[EXTI_13]	= { EXTI15_10_IRQn },
		[EXTI_14]	= { EXTI15_10_IRQn },
		[EXTI_15]	= { EXTI15_10_IRQn },
};

exti_driver	exti_handlers[EXTI_NUM];

void
exti_set_owner(exti_num num, void *owner)
{
	exti_handlers[num].p_owner = owner;
}

boolean
exti_available(exti_num num)
{
	return (exti_handlers[num].p_dev == NULL);
}

void
exti_release(exti_num num)
{
	exti_disable(num);
	exti_handlers[num].irq_handler = NULL;
	exti_handlers[num].p_dev = NULL;
	exti_handlers[num].p_owner = NULL;
}

void
exti_enable(exti_num num)
{
	EXTI_REG->IMR |= (1 << num);

	nvic_irq_enable(exti_dev_table[num].irq);
}

void
exti_disable(exti_num num)
{
	EXTI_REG->IMR &= ~(1 << num);

	if(num < EXTI_5)
	{
		nvic_irq_enable(exti_dev_table[num].irq);
	}
	else if(num < EXTI_10)
	{
		if((EXTI_REG->IMR & (0x1F << 5)) == 0)
			nvic_irq_enable(exti_dev_table[num].irq);
	}
	else
	{
		if((EXTI_REG->IMR & (0x3F << 10)) == 0)
			nvic_irq_enable(exti_dev_table[num].irq);
	}
}

void
exti_set_trigger(exti_num num, exti_trigger trigger)
{
	EXTI_REG->RTSR |= (((trigger & EXTI_TRIGGER_RISING) & 1) << num);
	EXTI_REG->FTSR |= (((trigger & EXTI_TRIGGER_FALLING) >> 1) << num);
}

void
exti_set_callback(exti_num num, irq_callback_t cb)
{
	exti_handlers[num].irq_handler = cb;
}

static void
exti_irq_handler(exti_num num)
{
	exti_driver *driver = &exti_handlers[num];

	if(driver != NULL && driver->irq_handler != NULL)
		(*(driver->irq_handler))(driver->p_owner);

	/* Clear pending flag by write 1 to pending flag*/
	EXTI_REG->PR |= (1 << num);
}

void EXTI0_IRQHandler(void)
{
	exti_irq_handler(EXTI_0);
}

void EXTI1_IRQHandler(void)
{
	exti_irq_handler(EXTI_1);
}

void EXTI2_IRQHandler(void)
{
	exti_irq_handler(EXTI_2);
}

void EXTI3_IRQHandler(void)
{
	exti_irq_handler(EXTI_3);
}

void EXTI4_IRQHandler(void)
{
	exti_irq_handler(EXTI_4);
}

void EXTI9_5_IRQHandler(void)
{
	uint32 pr = EXTI_REG->PR;

	if((pr & (1 << EXTI_5)) != 0)
		exti_irq_handler(EXTI_5);
	if((pr & (1 << EXTI_6)) != 0)
		exti_irq_handler(EXTI_6);
	if((pr & (1 << EXTI_7)) != 0)
		exti_irq_handler(EXTI_7);
	if((pr & (1 << EXTI_8)) != 0)
		exti_irq_handler(EXTI_8);
	if((pr & (1 << EXTI_9)) != 0)
		exti_irq_handler(EXTI_9);
}

void EXTI15_10_IRQHandler(void)
{
	uint32 pr = EXTI_REG->PR;

	if((pr & (1 << EXTI_9)) != 0)
		exti_irq_handler(EXTI_9);
	if((pr & (1 << EXTI_10)) != 0)
		exti_irq_handler(EXTI_10);
	if((pr & (1 << EXTI_11)) != 0)
		exti_irq_handler(EXTI_11);
	if((pr & (1 << EXTI_12)) != 0)
		exti_irq_handler(EXTI_12);
	if((pr & (1 << EXTI_13)) != 0)
		exti_irq_handler(EXTI_13);
	if((pr & (1 << EXTI_14)) != 0)
		exti_irq_handler(EXTI_14);
	if((pr & (1 << EXTI_15)) != 0)
		exti_irq_handler(EXTI_15);
}

