//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include <OutputPin.h>
#include <InputPin.h>
#include <SystemTick.h>
#include <HardwareSerial.h>

// ----------------------------------------------------------------------------
//
// Standalone STM32F4 empty sample (trace via DEBUG).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the DEBUG output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

OutputPin 	led3;
OutputPin 	led4;
InputPin 	btn;

HardwareSerial	serail1;

void
btn_irq_handler(void *);
void
systick_irq_handler(void *);

int
main(int argc, char* argv[])
{
  // At this stage the system clock should have already been configured
  // at high speed.

	serail1 = SERIAL1;
	serail1.m_RxPin	= PB6;
	serail1.m_TxPin	= PB7;

	led3 = PD13;
	led4 = PD12;

	btn = PB0;
	btn.AttachInterrupt(btn_irq_handler);

	SystemTick::SetFrequency(1000);
	SystemTick::AttachInterrupt(systick_irq_handler);


  // Infinite loop
  while (1)
    {
       // Add your code here.
    }
}

void
btn_irq_handler(void *driver)
{
	(void)driver;

	led3 = !led3;
}

void
systick_irq_handler(void *p_ticks)
{
	if(*((uint32 *)p_ticks) % 500 == 0)
	{
		led4 = !led4;
	}
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
