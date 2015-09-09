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
#include <HC05Bluetooth.h>

#include <bkpsram.h>

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

#define BKPSRAM_TEST_SIGNATURE	0x55555555
#define BKPSRAM_TEST_OFFSET		0

HC05Bluetooth	hc05;
OutputPin led4;

int
main(int argc, char* argv[])
{
  // At this stage the system clock should have already been configured
  // at high speed.
	uint32 val = 0;

	bkpsram_init();
	val = bkpsram_read_32(BKPSRAM_TEST_OFFSET);
	bkpsram_write_32(BKPSRAM_TEST_OFFSET, val + 1);
	val = bkpsram_read_32(BKPSRAM_TEST_OFFSET);

	trace("Signature: 0x%08X\n", val);

	trace("RCC Clock: %d\n", RCC_SYSTEM_CLOCK);

	led4 = PD14;

	hc05 = SERIAL4;
	hc05.m_RxPin	= PA1;
	hc05.m_TxPin	= PA0;
	hc05.m_CmdPin	= PD15;
	hc05.m_PwrPin	= PB1;
	hc05.m_StatPin 	= PB0;
	hc05.Begin();

  // Infinite loop
	uint32 counter = 0;
  while (1)
    {
       // Add your code here.
	  if(hc05.Connected())
	  {
		  hc05.Send("Counter: %d\r\n", counter++);
	  }

	  led4 = !led4;
	  Delay::Milli(1000);
    }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
