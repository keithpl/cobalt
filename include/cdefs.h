#ifndef CDEFS_H
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

#endif /* CDEFS_H */
