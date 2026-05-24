#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "sbuf.h"

#define SBUF_DEFAULT_SIZE	64

static inline bool sbuf_is_dynamic(const struct sbuf *sb)
{
	return sb->flags & SBUF_DYNAMIC;
}

static inline bool sbuf_is_dynstruct(const struct sbuf *sb)
{
	return sb->flags & SBUF_DYNSTRUCT;
}

static inline bool sbuf_can_fit(const struct sbuf *sb, size_t len)
{
	return sbuf_avail(sb) >= len;
}

static inline void sbuf_attach(struct sbuf *sb, char *buf, size_t size,
			       unsigned int flags)
{
	sb->buf = buf;
	sb->size = size;
	sb->flags = flags;
	sbuf_reset(sb);
}

int sbuf_init(struct sbuf *sb, char *buf, size_t size, unsigned int user_flags)
{
	unsigned int flags = user_flags & SBUF_USERMASK;

	if (!sb)
		return -1;

	if (buf) {
		if (!size)
			return -1;
	} else {
		if (!size)
			size = SBUF_DEFAULT_SIZE;

		flags |= SBUF_DYNAMIC;
		buf = malloc(size);
		if (!buf)
			return -1;
	}
	sbuf_attach(sb, buf, size, flags);
	return 0;
}

struct sbuf *sbuf_create(char *buf, size_t size, unsigned int user_flags)
{
	int ret;
	struct sbuf *sb;

	sb = malloc(sizeof(*sb));
	if (!sb)
		return NULL;

	ret = sbuf_init(sb, buf, size, user_flags);
	if (ret < 0) {
		free(sb);
		return NULL;
	}

	sb->flags |= SBUF_DYNSTRUCT;
	return sb;
}

void sbuf_destroy(struct sbuf *sb)
{
	if (sbuf_is_dynamic(sb))
		free(sb->buf);
	if (sbuf_is_dynstruct(sb))
		free(sb);
}
