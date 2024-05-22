#if !defined(CDEFS_H)
#define CDEFS_H

#include <limits.h>
#include <stddef.h>

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
 * Signed variants (ssizeof) allow for consistency when performing arithmetic
 * operations or comparisons with other signed integers, avoiding potential
 * issues related to type promotion or sign mismatch. (-Wconversion)
 */
#define ssizeof(x)		((ptrdiff_t)sizeof(x))
#define bit_sizeof(x)		(CHAR_BIT * sizeof(x))
#define bit_ssizeof(x)		((ptrdiff_t)bit_sizeof(x))

/*
 * A variant of static_assert() that acts as an expression, always resolving to
 * zero. Useful for embedding compile-time assertions within expressions.
 */
#define static_assert_expr(expr, msg) \
	((int)(sizeof(struct { _Static_assert((expr), msg); int x; }) * 0))

#define array_length(array) \
	((sizeof(array) / sizeof((array)[0])) + assert_array(array))

#define array_slength(array)	((ptrdiff_t)array_length(array))

#if __has_builtin(__builtin_types_compatible_p)

/*
 * `&(array)[0]` always decays into a pointer type. If this type matches the
 * type of `array`, then a pointer was passed to assert_array(), not an array.
 *
 * Note: `__typeof__` will be replaced by `typeof` when C23 is available.
 */
#define assert_array(array)						\
	static_assert_expr(						\
		!__builtin_types_compatible_p(				\
			__typeof__(array),				\
			__typeof__(&(array)[0])				\
		),							\
		"assert_array(): non-array argument passed: " #array	\
	)

#else /* __has_builtin(__builtin_types_compatible_p) */

#define assert_array(array)	0

#endif /*__has_builtin(__builtin_types_compatible_p) */


#if __has_builtin(__builtin_types_compatible_p)

/*
 * Calculate the address of the parent structure given a pointer to a field
 * within that structure. Perform compile-time type checking of the provided
 * pointer and field.
 */
#define container_of(ptr, type, field)					\
	(((type *)((char *)(ptr) - offsetof(type, field))) +		\
	static_assert_expr(						\
		__builtin_types_compatible_p(				\
			__typeof__(*(ptr)),				\
			__typeof__(((type *)0)->field)			\
		),							\
		"container_of(): pointer type mismatch"			\
	))

#else /* __has_builtin(__builtin_types_compatible_p) */

/* Attempt weak type checking with the ternary operator. */
#define container_of(ptr, type, field)					\
	((type *)((char *)(1 ? (ptr) : &((type *)0)->field) -		\
		  offsetof(type, field)))

#endif /* __has_builtin(__builtin_types_compatible_p) */

#if __has_builtin(__builtin_expect)
#define likely(expr)		__builtin_expect((expr) != 0, 1)
#define unlikely(expr)		__builtin_expect((expr) != 0, 0)
#else
#define likely(expr)		(expr)
#define unlikely(expr)		(expr)
#endif

#if __has_attribute(__used__)
#define always_used		__attribute__((__used__))
#else
#define always_used
#endif

#if __has_attribute(__unused__)
#define maybe_unused		__attribute__((__unused__))
#define always_unused		__attribute__((__unused__))
#else
#define maybe_unused
#define always_unused
#endif

#if __has_attribute(__nonnull__)
#define nonnull_params(...)	__attribute__((__nonnull__(__VA_ARGS__)))
#else
#define nonnull_params(...)
#endif

#if __has_attribute(__fallthrough__)
#define fallthrough		__attribute__((__fallthrough__))
#else
#define fallthrough
#endif

#if __has_attribute(__noinline__)
#define never_inline		__attribute__((__noinline__))
#else
#define never_inline
#endif

#if __has_attribute(__always_inline__)
#define always_inline		__attribute__((__always_inline__)) inline
#else
#define always_inline		inline
#endif

#if __has_attribute(__const__)
#define constfunc		__attribute__((__const__))
#else
#define constfunc
#endif

#if __has_attribute(__pure__)
#define purefunc		__attribute__((__pure__))
#else
#define purefunc
#endif

#if __has_attribute(__warn_unused_result__)
#define nodiscard		__attribute__((__warn_unused_result__))
#else
#define nodiscard
#endif

#if __has_attribute(__format_arg__)
#define format_arg(arg)		__attribute__((__format_arg__(arg)))
#else
#define format_arg(arg)
#endif

#if __has_attribute(__format__)
#define formatlike(type, fmtarg, firstvararg) \
	__attribute__((__format__(type, fmtarg, firstvararg)))
#else
#define formatlike(type, fmtarg, firstvararg)
#endif

#define printflike(fmtarg)	formatlike(__printf__, fmtarg, fmtarg + 1)
#define vprintflike(fmtarg)	formatlike(__printf__, fmtarg, 0)
#define scanflike(fmtarg)	formatlike(__scanf__, fmtarg, fmtarg + 1)
#define vscanflike(fmtarg)	formatlike(__scanf__, fmtarg, 0)

#endif /* !defined(CDEFS_H) */
