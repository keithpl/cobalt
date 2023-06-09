#if !defined(CDEFS_H)
#define CDEFS_H

#include <assert.h>
#include <limits.h>

#if !defined(__has_attribute)
#define __has_attribute(x)	0
#define __attribute__(x)
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

#define XCONCAT(x, y)		x ## y
#define CONCAT(x, y)		CONCAT(x, y)
#define XSTRING(...)		#__VA_ARGS__
#define STRING(...)		XSTRING(__VA_ARGS__)

/* 
 * Signed (ssizeof) variants provided to more easily content with
 * -Wconversion warnings.
 */
#define ssizeof(x)		((long)sizeof(x))
#define bit_sizeof(x)		(CHAR_BIT * sizeof(x))
#define bit_ssizeof(x)		((long)bit_sizeof(x))

/*
 * A variant of static_assert() that is itself an expression, always
 * resolving to zero.
 */
#define static_assert_expr(expr, msg) \
	((int)(sizeof(struct { static_assert((expr), msg); int _x; }) * 0))

#if __has_builtin(__builtin_types_compatible_p)
/*
 * '&(array)[0]' will always decay into a pointer type, if this type matches
 * the type of 'array', then a pointer was passed to assert_array().
 */
#define assert_array(array)						\
	static_assert_expr(						\
		!__builtin_types_compatible_p(				\
			__typeof__(array),				\
			__typeof__(&(array)[0])				\
		),							\
		"assert_array(): non-array argument passed: " #array	\
	)

#define container_of(ptr, type, field)					\
	(((type *)((unsigned char *)((ptr) - offsetof(type, field)))) +	\
	 static_assert_expr(						\
		__builtin_types_compatible_p(				\
			__typeof__(ptr),				\
			__typeof__(&((type *)0)->field)			\
		),							\
		"container_of(): pointer type mismatch"			\
	))
#else /* __has_builtin(__builtin_types_compatible_p) */

#define assert_array(array)	0

/* At least get some type checking with the ternary operator. */
#define container_of(ptr, type, field)					\
	((type *)((unsigned char *)(1 ? (ptr) : &((type *)0)->field) -	\
		  offsetof(type, field)))

#endif /* __has_builtin(__builtin_types_compatible_p) */

#define array_size(array) \
	((sizeof(array) / sizeof((array)[0])) + assert_array(array))

#define array_ssize(array)		((long)array_size(array))

#if __has_builtin(__builtin_expect)
#define predict_true(expr)		__builtin_expect((expr) != 0, 1)
#define predict_false(expr)		__builtin_expect((expr) != 0, 0)
#else
#define predict_true(expr)		(expr)
#define predict_false(expr)		(expr)
#endif

#endif /* !defined(CDEFS_H) */
