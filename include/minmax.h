#if !defined(MINMAX_H)
#define MINMAX_H

#include "cdefs.h"

#define MINMAX_GENERIC(op, x, y) _Generic((x) + (y),	\
	int:			op ## _int,		\
	long:			op ## _long,		\
	long long:		op ## _llong,		\
	unsigned int:		op ## _int,		\
	unsigned long:		op ## _ulong,		\
	unsigned long long:	op ## _ullong,		\
	float:			op ## _float,		\
	double:			op ## _double,		\
	long double:		op ## _ldouble		\
)((x), (y))

#define min(x, y)		MINMAX_GENERIC(min, (x), (y))
#define max(x, y)		MINMAX_GENERIC(max, (x), (y))

#define min3(x, y, z)		min(min((x), (y)), (z))
#define max3(x, y, z)		max(max((x), (y)), (z))

#define clamp(val, low, high)	min(max((val), (low)), (high))

static inline constfunc int min_int(int x, int y)
{
	return (x < y) ? x : y;
}

static inline constfunc int max_int(int x, int y)
{
	return (x > y) ? x : y;
}

static inline constfunc long min_long(long x, long y)
{
	return (x < y) ? x : y;
}

static inline constfunc long max_long(long x, long y)
{
	return (x > y) ? x : y;
}

static inline constfunc long long min_llong(long long x, long long y)
{
	return (x < y) ? x : y;
}

static inline constfunc long long max_llong(long long x, long long y)
{
	return (x > y) ? x : y;
}

static inline constfunc unsigned int min_uint(unsigned int x, unsigned int y)
{
	return (x < y) ? x : y;
}

static inline constfunc unsigned int max_uint(unsigned int x, unsigned int y)
{
	return (x > y) ? x : y;
}

static inline constfunc unsigned long min_ulong(unsigned long x,
						unsigned long y)
{
	return (x < y) ? x : y;
}

static inline constfunc unsigned long max_ulong(unsigned long x,
						unsigned long y)
{
	return (x > y) ? x : y;
}

static inline constfunc unsigned long long min_ullong(unsigned long long x,
						      unsigned long long y)
{
	return (x < y) ? x : y;
}

static inline constfunc unsigned long long max_ullong(unsigned long long x,
						      unsigned long long y)
{
	return (x > y) ? x : y;
}

static inline constfunc float min_float(float x, float y)
{
	return (x < y) ? x : y;
}

static inline constfunc float max_float(float x, float y)
{
	return (x > y) ? x : y;
}

static inline constfunc double min_double(double x, double y)
{
	return (x < y) ? x : y;
}

static inline constfunc double max_double(double x, double y)
{
	return (x > y) ? x : y;
}

static inline constfunc long double min_ldouble(long double x, long double y)
{
	return (x < y) ? x : y;
}

static inline constfunc long double max_ldouble(long double x, long double y)
{
	return (x > y) ? x : y;
}

#endif /* !defined(MINMAX_H) */
