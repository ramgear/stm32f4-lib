/**
 * @file	trace.c
 * @brief	Framework header file.
 * @details	Framework header file.
 * @version	1.0
 * @date	Sep 5, 2015
 * @author	Eakkasit L.
 * @bug		No known bug
 * @warning	Improper use can crash your application
 * @copyright	GNU Public License.
 */

#include <string.h>
#include <trace.h>

#define	TRACE_BUFFER_SIZE	64

int
trace_printf(const char* format, ...)
{
  int ret;
  va_list ap;

  va_start (ap, format);

  static char buf[TRACE_BUFFER_SIZE];

  // Print to the local buffer
  ret = vsnprintf (buf, sizeof(buf), format, ap);
  if (ret > 0)
    {
      // Transfer the buffer to the device
      ret = trace_write (buf, (size_t)ret);
    }

  va_end (ap);
  return ret;
}

int
trace_puts(const char *s)
{
  trace_write(s, strlen(s));
  return trace_write("\n", 1);
}

int
trace_putchar(int c)
{
  trace_write((const char*)&c, 1);
  return c;
}


ssize_t
trace_write (const char* buf, size_t nbyte)
{
	  // Since the single character debug channel is quite slow, try to
	  // optimise and send a null terminated string, if possible.
	  if (buf[nbyte] == '\0')
	    {
	      // send string
	      call_host (SEMIHOSTING_SYS_WRITE0, (void*) buf);
	    }
	  else
	    {
	      // If not, use a local buffer to speed things up
	      char tmp[TRACE_BUFFER_SIZE];
	      size_t togo = nbyte;
	      while (togo > 0)
	        {
	          unsigned int n = ((togo < sizeof(tmp)) ? togo : sizeof(tmp));
	          unsigned int i = 0;
	          for (; i < n; ++i, ++buf)
	            {
	              tmp[i] = *buf;
	            }
	          tmp[i] = '\0';

	          call_host (SEMIHOSTING_SYS_WRITE0, (void*) tmp);

	          togo -= n;
	        }
	    }

	  // All bytes written
	  return (ssize_t) nbyte;
}
