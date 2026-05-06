#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <limits.h>

#include "cdefs.h"
#include "strutil.h"

int vscnprintf(char *restrict buf, size_t size, const char *restrict fmt,
	       va_list args)
{
	int ret;
	int ssize;

	if (unlikely(!size))
		return 0;

	if (unlikely(size > (size_t)INT_MAX))
		return -1;

	ssize = (int)size;
	ret = vsnprintf(buf, size, fmt, args);
	if (ret < ssize)
		return ret;

	return ssize - 1;
}

int scnprintf(char *restrict buf, size_t size, const char *restrict fmt, ...)
{
	int ret;
	va_list args;

	va_start(args, fmt);
	ret = vscnprintf(buf, size, fmt, args);
	va_end(args);

	return ret;
}
