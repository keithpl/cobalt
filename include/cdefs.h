#ifndef CDEFS_H
#define CDEFS_H

#include <stdint.h>

#if !defined(__has_attribute)
#define __has_attribute(x)	0
#endif

#if !defined(__has_c_attribute)
#define __has_c_attribute(x)	0
#endif

#if !defined(__has_builtin)
#define __has_builtin(x)	0
#endif

#if !defined(__has_feature)
#define __has_feature(x)	0
#endif

#if !defined(__has_extension)
#define __has_extension		__has_feature
#endif

#if !defined(__has_include)
#define __has_include(x)	0
#endif

/*
 * Provide `typeof` using a compiler extension.
 *
 * While this is an extension in <= C17, `typeof` was standardized in C23,
 * relying on the extension is acceptable going forward.
 *
 * This definition can be dropped after the project switches to -std=c23.
 */
#if !defined(__STDC_VERSION__) || (__STDC_VERSION__ < 202311L)
#ifndef typeof
#define typeof			__typeof__
#endif
#endif

/* Concatenate tokens `x` and `y` without macro expansion. Prefer `CONCAT`. */
#define CONCAT_(x, y)		x ## y
/* First expand tokens `x` and `y`, then concatenate the expanded results. */
#define CONCAT(x, y)		CONCAT_(x, y)

/* Stringify variadic arguments without macro expansion. Prefer `STRINGIFY`. */
#define STRINGIFY_(...)		#__VA_ARGS__
/* First expand all variadic arguments, then stringify the expanded results. */
#define STRINGIFY(...)		STRINGIFY_(__VA_ARGS__)

/*
 * Remove the `const` qualifier from `ptr` by casting it through `uintptr_t`.
 * Casting directly from `const T *` to `T *`, even through `const void *` or
 * `void *`, triggers -Wcast-qual.
 *
 * Do NOT use this macro on any object that was originally declared `const` as
 * this is undefined behavior.
 */
#define DECONST(type, ptr)	((type)(uintptr_t)(const void *)(ptr))

#endif /* CDEFS_H */
