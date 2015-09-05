/**
 ******************************************************************************
 * @file	cpu_startup.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	24-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#include "cpu.h"
#include "trace.h"


/*
 * ************************************************************************************************
 * Global define in linker scripts
 * ************************************************************************************************
 */

/**
 * @name	Linker define entries.
 * @{
 */

#define	__SIDATA__					_sidata						/*!< Begin address for the initialization from ROM */
#define	__SDATA__					_sdata						/*!< Begin address for the initialization in RAM  */
#define	__EDATA__					_edata						/*!< End address for the initialization in RAM  */

#define	__BSS_START__				__bss_start__				/*!< Begin address of uninitialization in RAM  */
#define	__BSS_END__					__bss_end__					/*!< End address of uninitialization in RAM  */

#define	__PRE_INIT_ARR_START__		__preinit_array_start
#define	__PRE_INIT_ARR_END__		__preinit_array_end
#define	__INIT_ARR_START__			__init_array_start
#define	__INIT_ARR_END__			__init_array_end
#define	__FINI_ARR_START__			__fini_array_start
#define	__FINI_ARR_END__			__fini_array_end
/** @} */

extern uint32 __SIDATA__;
extern uint32 __SDATA__;
extern uint32 __EDATA__;

// Begin address for the .bss section; defined in linker script
extern uint32 __BSS_START__;
// End address for the .bss section; defined in linker script
extern uint32 __BSS_END__;


// These magic symbols are provided by the linker.
extern void
(*__PRE_INIT_ARR_START__[]) (void) __attribute__((weak));
extern void
(*__PRE_INIT_ARR_END__[]) (void) __attribute__((weak));
extern void
(*__INIT_ARR_START__[]) (void) __attribute__((weak));
extern void
(*__INIT_ARR_END__[]) (void) __attribute__((weak));
extern void
(*__FINI_ARR_START__[]) (void) __attribute__((weak));
extern void
(*__FINI_ARR_END__[]) (void) __attribute__((weak));

/**************************************************************************************************/

/**
 * The implementation for the main function.
 */
extern int
main (void);

/**
 * The implementation for the exit routine; for embedded applications, a system reset will be performed.
 */
extern void
__attribute__((noreturn))
_exit (int);

void CPU_DataInit(uint32 *src, uint32 *start, uint32 *end)
{
	uint32 *ptr = start;
	while (ptr < end)
		*ptr++ = *src++;
}

void CPU_BSSInit(uint32 *start, uint32 *end)
{
	uint32 *ptr = start;
	while (ptr < end)
		*ptr++ = (uint32)0;
}

void CPU_InitArray(void)
{
	  int count;
	  int i;

	  count = __PRE_INIT_ARR_END__ - __PRE_INIT_ARR_START__;
	  for (i = 0; i < count; i++)
		  __PRE_INIT_ARR_START__[i] ();

	  count = __INIT_ARR_END__ - __INIT_ARR_START__;
	  for (i = 0; i < count; i++)
		  __INIT_ARR_START__[i] ();
}

void CPU_FinishArray(void)
{
	  int count;
	  int i;

	  count = __FINI_ARR_END__ - __FINI_ARR_START__;
	  for (i = count; i > 0; i--)
		  __FINI_ARR_START__[i - 1] ();
}

__attribute__ ((section(".after_vectors"),noreturn,weak))
void CPU_Startup(void)
{
	int ret;

	/* Call CPU early initialization */
	cpu_init_early();

	/* Copy the initialized data from ROM to RAM. */
	CPU_DataInit(&__SIDATA__, &__SDATA__, &__EDATA__);

	/* Zero fill uninitialized data */
	CPU_BSSInit(&__BSS_START__, &__BSS_END__);

	/* C++ execute the constructors for the static objects */
	CPU_InitArray();

	/* Call CPU initialization */
	cpu_init();

	/* Call main function */
	ret = main();

	/* C++ execute the destructors for the static objects */
	CPU_FinishArray();

	/* Terminate process with status */
	_exit(ret);

	/* Should never reach this, _exit() should have already performed a reset. */
	while(1);
}

/**
 * @brief	Reset Handler interrupt service routine.
 * 		Call startup code on reset.
 */
__attribute__ ((section(".after_vectors"),noreturn))
void
ISR_Reset_Handler(void)
{
	 CPU_Startup();
}



/*
 * ************************************************************************************************
 * Newlib implementations
 * ************************************************************************************************
 */
void
__attribute__((weak))
_exit(int code __attribute__((unused)))
{
  while (1)
    ;
}

void
__attribute__((weak,noreturn))
abort(void)
{
  trace_puts("abort(), exiting...");

  _exit(1);
}

caddr_t
_sbrk(int incr)
{
  extern char _Heap_Begin; // Defined by the linker.
  extern char _Heap_Limit; // Defined by the linker.

  static char* current_heap_end;
  char* current_block_address;

  if (current_heap_end == 0)
    {
      current_heap_end = &_Heap_Begin;
    }

  current_block_address = current_heap_end;

  // Need to align heap to word boundary, else will get
  // hard faults on Cortex-M0. So we assume that heap starts on
  // word boundary, hence make sure we always add a multiple of
  // 4 to it.
  incr = (incr + 3) & (~3); // align value to 4
  if (current_heap_end + incr > &_Heap_Limit)
    {
      // Some of the libstdc++-v3 tests rely upon detecting
      // out of memory errors, so do not abort here.
#if 0
      extern void abort (void);

      _write (1, "_sbrk: Heap and stack collision\n", 32);

      abort ();
#else
      // Heap has overflowed
      errno = ENOMEM;
      return (caddr_t) - 1;
#endif
    }

  current_heap_end += incr;

  return (caddr_t) current_block_address;
}
