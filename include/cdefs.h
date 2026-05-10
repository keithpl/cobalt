#ifndef CDEFS_H
#define CDEFS_H

#include <stddef.h>
#include <stdint.h>

#ifndef __has_attribute
#define __has_attribute(x)	0
#endif

#ifndef __has_c_attribute
#define __has_c_attribute(x)	0
#endif

#ifndef __has_builtin
#define __has_builtin(x)	0
#endif

#ifndef __has_feature
#define __has_feature(x)	0
#endif

#ifndef __has_extension
#define __has_extension		__has_feature
#endif

#ifndef __has_include
#define __has_include(x)	0
#endif

/*
 * Provide `typeof` using a compiler extension, `__typeof__`.
 *
 * While this is an extension in <= C17, `typeof` was standardized in C23, with
 * the same behavior as the extension, relying on the extension is acceptable
 * going forward.
 *
 * This definition can be dropped after the project switches to -std=c23.
 */
#if !defined(__STDC_VERSION__) || (__STDC_VERSION__ < 202311L)
#ifndef typeof
#define typeof			__typeof__
#endif
#endif

/*
 * Check a condition at compile time; the condition must be a compile-time
 * constant expression.
 *
 * Unlike `static_assert()`, which is a declaration and restricted to
 * declaration context, this macro expands to a constant expression of value
 * `(int)0` and may appear anywhere an expression is valid.
 */
#define static_assert_expr(cond, msg)					\
	((int)(sizeof(struct {						\
		_Static_assert((cond), msg);				\
		int dummy;						\
	}) * 0))

/*
 * Signed variant of `sizeof`, expanding to a value of `ptrdiff_t`. Asserts at
 * compile-time that `sizeof(x)` does not exceed `PTRDIFF_MAX`.
 *
 * Useful for arithmetic and comparisons where mixing `size_t` with signed
 * types would trigger -Wconversion or -Wsign-compare.
 */
#define ssizeof(x)							\
	((ptrdiff_t)sizeof(x) +						\
	 static_assert_expr(sizeof(x) <= (size_t)PTRDIFF_MAX,		\
			    "sizeof(" #x ") exceeds PTRDIFF_MAX"))

/*
 * Concatenate tokens `x` and `y` without macro expansion.
 *
 * This is primarily a helper for `CONCAT()`; use `CONCAT()` instead unless
 * macro expansion is not desired.
 */
#define CONCAT_(x, y)		x ## y

/* First expand tokens `x` and `y`, then concatenate the results. */
#define CONCAT(x, y)		CONCAT_(x, y)

/*
 * Stringify all variadic tokens without macro expansion.
 *
 * This is primarily a helper for `STRING()`; use `STRING()` instead unless
 * macro expansion is not desired.
 */
#define STRING_(...)		#__VA_ARGS__

/* First expand all variadic tokens, then stringify the results. */
#define STRING(...)		STRING_(__VA_ARGS__)

/*
 * Remove the `const` qualifier from `ptr` by casting it through `uintptr_t`.
 * Casting directly from `const T *` to `T *`, even through `const void *` or
 * `void *`, triggers -Wcast-qual.
 *
 * Do NOT use this macro on any object that was originally declared `const` as
 * this is undefined behavior.
 */
#define DECONST(type, ptr)	((type)(uintptr_t)(const void *)(ptr))

/*
 * Check if `x` is an array.
 *
 * For an array `x` of type `T [N]`, `&x` is of type `T (*)[N]`; for a
 * pointer `x` of type `T *`, `&x` is of type `T **`.
 *
 * The selection type `typeof((x)[0]) (*)[]` has type `T (*)[]`, a pointer to
 * an incomplete array, which is compatible with `T (*)[N]` but not `T **`.
 * Arrays match the first case; pointers fall through to the default.
 *
 * typeof(x)    typeof(&x)      typeof((x)[0]) (*)[]    result
 * ---------    ----------      --------------------    ------
 * int[N]       int (*)[N]      int (*)[]               1
 * int *        int **          int (*)[]               0
 */
#define is_array(x) _Generic((&(x)),					\
	typeof((x)[0]) (*)[]:	1,					\
	default:		0					\
)

#endif /* CDEFS_H */
