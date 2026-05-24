#ifndef SBUF_H
#define SBUF_H

#include <stddef.h>

#define SBUF_FIXED	0x0000u
#define SBUF_AUTOGROW	0x0001u
#define SBUF_USERMASK	0x00ffu
#define SBUF_DYNAMIC	0x0100u
#define SBUF_DYNSTRUCT	0x0200u
#define SBUF_OVERFLOWED	0x0400u

struct sbuf {
	char *buf;
	size_t size;
	size_t len;
	unsigned int flags;
};

static inline void sbuf_reset(struct sbuf *sb)
{
	sb->buf[0] = 0;
	sb->len = 0;
}

int sbuf_init(struct sbuf *sb, char *buf, size_t size, unsigned int user_flags);
struct sbuf *sbuf_create(char *buf, size_t size, unsigned int user_flags);

void sbuf_destroy(struct sbuf *sb);

#endif /* SBUF_H */
