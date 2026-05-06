#include <limits.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

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

size_t safe_strncpy(char *restrict dest, const char *restrict src, size_t n)
{
	size_t len;
	size_t src_len;

	if (unlikely(!n))
		return 0;

	src_len = strnlen(src, n);
	len = (src_len < n) ? src_len : n - 1;

	memcpy(dest, src, len);
	dest[len] = 0;
	return src_len;
}
