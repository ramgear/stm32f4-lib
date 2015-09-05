//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "trace.h"
#include <OutputPin.h>
#include <InputPin.h>
#include <HardwareSerial.h>
#include <Delay.h>

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

int
main(int argc, char* argv[])
{
  // At this stage the system clock should have already been configured
  // at high speed.

	serail1 = SERIAL4;
	serail1.m_RxPin	= PA1;
	serail1.m_TxPin	= PA0;

	led3 = PD13;
	led4 = PD12;

	btn = PB0;
	btn.AttachInterrupt(btn_irq_handler);

	serail1.Begin(9600);

	trace("RCC Clock: %d\n", RCC_SYSTEM_CLOCK);

  // Infinite loop
  while (1)
    {
       // Add your code here.
	  led4 = !led4;
	  Delay::Milli(500);
    }
}

void
btn_irq_handler(void *driver)
{
	(void)driver;

	led3 = !led3;
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
