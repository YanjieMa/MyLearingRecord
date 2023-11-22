
#include <stdarg.h>
#include <stdio.h>
#include <assert.h>

#include "../headers/common.h"

// wrapper of stdio printf
// controlled by the debug verbose bit set
uint64_t debug_fprintf(uint64_t open_set,FILE *stream, const char *format, ...)
{
    if ((open_set & DEBUG_VERBOSE_SET) == 0x0)
    {
        return 0x0;
    }

    // implementation of std printf()
    va_list argptr;
    va_start(argptr, format);
    int ret = vfprintf(stream, format, argptr);
    va_end(argptr);

    return ret;
}
/*	va_list argptr
 *	void va_start(va_list argptr, const char * format)
 *	type va_arg(va_list argptr, type)
 *	void va_end(va_list argptr)
 *	void va_copy(va_list src, va_list dst)
 * */
