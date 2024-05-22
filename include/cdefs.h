#if !defined(CDEFS_H)
#define CDEFS_H

#if !defined(__has_attribute)
#define __has_attribute(x)	0
#endif

#if !defined(__has_c_attribute)
#define __has_c_attribute(x)	0
#endif

#if !defined(__has_builtin)
#define __has_builtin(x)	0
#endif

#if !defined(__has_extension)
#define __has_extension		__has_feature
#endif

#if !defined(__has_feature)
#define __has_feature(x)	0
#endif

#if !defined(__has_include)
#define __has_include(x)	0
#endif

/* Concatenate tokens x and y, without expansion. */
#define CONCAT(x, y)		x ## y
/* Expand tokens x and y, then concatenate the expanded results. */
#define XCONCAT(x, y)		CONCAT(x, y)
/* Stringify variadic arguments, without expansion. */
#define STRING(...)		#__VA_ARGS__
/* Expand all variadic arguments, then stringify the arguments. */
#define XSTRING(...)		STRING(__VA_ARGS__)

/*
 * A variant of static_assert() that acts as an expression, always resolving to
 * zero. Useful for embedding compile-time assertions within expressions.
 */
#define static_assert_expr(expr, msg) \
	((int)(sizeof(struct { _Static_assert((expr), msg); int x; }) * 0))

/*
 * Signed variants (ssizeof) allow for consistency when performing arithmetic
 * operations or comparisons with other signed integers, avoiding potential
 * issues related to type promotion or sign mismatch. (-Wconversion)
 */
#define ssizeof(x)		((ptrdiff_t)sizeof(x))
#define bit_sizeof(x)		(CHAR_BIT * sizeof(x))
#define bit_ssizeof(x)		((ptrdiff_t)bit_sizeof(x))

#endif /* !defined(CDEFS_H) */
