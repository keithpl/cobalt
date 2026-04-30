#ifndef CDEFS_H
#define CDEFS_H

#include <stddef.h>
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
 * While this is currently an extension, `typeof` was standardized in C23,
 * relying on the extension is acceptable going forward.
 *
 * This definition can be dropped after the project switches to -std=c23.
 */
#if !defined(__STDC_VERSION__) || (__STDC_VERSION__ < 202311L)
#ifndef typeof
#define typeof		__typeof__
#endif
#endif

/* Concatenate tokens `x` and `y` without macro expansion. */
#define CONCAT(x, y)		x ## y
/* First expand tokens `x` and `y`, then concatenate the expanded results. */
#define XCONCAT(x, y)		CONCAT(x, y)

/* Stringify variadic arguments without macro expansion. */
#define STRINGIFY(...)		#__VA_ARGS__
/* First expand all variadic tokens, then stringify the expanded results. */
#define XSTRINGIFY(...)		STRINGIFY(__VA_ARGS__)

/*
 * Remove the `const` qualifier from `ptr` by casting it through `uintptr_t`.
 * Casting directly from `const T *` to `T *`, even through `const void *` or
 * `void *`, triggers -Wcast-qual.
 *
 * Do NOT use this on any object that was originally declared `const` as this is
 * undefined behavior.
 */
#define DECONST(type, ptr)	((type)(uintptr_t)(const void *)(ptr))

/*
 * A variant of `static_assert()` that expands to a constant expression of
 * value (int)0. Unlike `static_assert()`, which is a declaration, this macro
 * may appear anywhere an expression is valid.
 */
#define static_assert_expr(cond, msg)				\
	((int)(sizeof(struct {					\
		_Static_assert((cond), msg);			\
		int dummy;					\
	}) * 0))


#define sizeof_fits_ptrdiff(x)					\
	static_assert_expr(sizeof(x) <= (size_t)PTRDIFF_MAX,	\
			   "sizeof(" #x ") exceeds PTRDIFF_MAX")

/*
 * Signed variant of `sizeof`, expanding to a value of type `ptrdiff_t`.
 *
 * Useful for pointer arithmetic and comparisons where mixing `size_t` with
 * signed types would trigger -Wconversion or -Wsign-compare.
 *
 * Asserts at compile time that `sizeof(x)` safely fits within a `ptrdiff_t`.
 */
#define ssizeof(x) \
	((ptrdiff_t)sizeof(x) + sizeof_fits_ptrdiff(x))

/*
 * Test if `x` is an array.
 *
 * For a pointer `x` of type `T *`, `&x` is of type `T **`; for an array `x` of
 * type `T[N]`, `&x` is of type `T (*)[N]`. The selection type
 * `typeof(&(x)[0]) *` always evaluates to type `T **`, only pointers to
 * complete types match the first case and arrays fall through to the default.
 *
 * typeof(x)    typeof(&x)      typeof(&(x)[0]) *       result
 * ---------    ----------      -----------------       ------
 * int *        int **          int **                  0
 * int[N]       int (*)[N]      int **                  1
 */
#define is_array(x) _Generic(&(x),				\
	typeof(&(x)[0]) *:	0,				\
	default:		1				\
)

#define assert_is_array(array)					\
	static_assert_expr(is_array(array),			\
			   "assert_is_array(): "		\
			   "non-array object passed: " #array)

#define countof(array) \
	((sizeof(array) / sizeof((array)[0])) + assert_is_array(array))

#define scountof(array) \
	((ssizeof(array) / ssizeof((array)[0])) + assert_is_array(array))

#endif /* CDEFS_H */
