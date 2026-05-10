#ifndef CDEFS_H
#define CDEFS_H

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

#endif /* CDEFS_H */
