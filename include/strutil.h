#ifndef STRUTIL_H
#define STRUTIL_H

#include <stdarg.h>
#include <stddef.h>

#include "cdefs.h"

/*
 * A variant of `vsnprintf()` that returns the number of characters written,
 * not the number that would have been written. Returns -1 on error.
 */
int vscnprintf(char *restrict buf, size_t size, const char *restrict fmt,
	       va_list args) vprintf_like(3);

/*
 * A variant of `snprintf()` that returns the number of characters written,
 * not the number that would have been written. Returns -1 on error.
 */
int scnprintf(char *restrict buf, size_t size, const char *restrict fmt, ...)
	printf_like(3, 4);

/*
 * Copy at most `n - 1` characters from `src` to `dest`, always
 * null-terminating `dest`.
 *
 * Returns `strlen(src)` if `src` is shorter than `n`, or `n` if `src` was
 * truncated. Truncation can be detected by checking if the return value is
 * >= `n`.
 */
size_t safe_strncpy(char *restrict dest, const char *restrict src, size_t n)
	nonnull_params(1, 2);

#endif /* STRUTIL_H */
