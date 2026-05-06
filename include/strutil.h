#ifndef STRUTIL_H
#define STRUTIL_H

#include <stdarg.h>
#include <stddef.h>

#include "cdefs.h"

int vscnprintf(char *restrict buf, size_t size, const char *restrict fmt,
	       va_list args) vprintf_like(3);

int scnprintf(char *restrict buf, size_t size, const char *restrict fmt, ...)
	printf_like(3, 4);

#endif /* STRUTIL_H */
