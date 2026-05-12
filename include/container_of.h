#ifndef CONTAINER_OF_H
#define CONTAINER_OF_H

#include <stddef.h>

#include "cdefs.h"

#if __has_builtin(__builtin_types_compatible_p)

#define container_of_assert_types(ptr, type, member)			\
	static_assert_expr(						\
		__builtin_types_compatible_p(				\
			typeof(ptr),					\
			typeof(&((type *)0)->member)			\
		),							\
		"container_of(): type mismatch: " #ptr			\
		" is not compatible with " #type "." #member		\
	)

#else
#define container_of_assert_types(ptr, type, member)	0
#endif

/*
 * Arithmetic is performed as `const char *`; casting the result directly to
 * `const type *` may increase the alignment requirement and trigger
 * -Wcast-align. Casting through `const void *` first suppresses the warning.
 */
#define container_of_const(ptr, type, member)				\
	((const type *)(const void *)(					\
		(const char *)(ptr) - offsetof(type, member) +		\
		container_of_assert_types((ptr), type, member)		\
	))

#define container_of_deconst(ptr, type, member)				\
	DECONST(type *, container_of_const((ptr), type, member))

#define container_of(ptr, type, member) _Generic((ptr),			\
	const typeof(*(ptr)) *:						\
		container_of_const((ptr), type, member),		\
	default:							\
		container_of_deconst((ptr), type, member)		\
)

#endif /* CONTAINER_OF_H */
