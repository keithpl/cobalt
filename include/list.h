#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

#include "cdefs.h"
#include "container_of.h"

struct list_node {
	struct list_node *next, *prev;
};

#define list_entry(node, type, member) \
	container_of((node), type, member)

#define list_first_entry(head, type, member) \
	list_entry((head)->next, type, member)

#define list_last_entry(head, type, member) \
	list_entry((head)->prev, type, member)

#define list_next_entry(entry, member) \
	list_entry((entry)->member.next, typeof(*(entry)), member)

#define list_prev_entry(entry, member) \
	list_entry((entry)->member.prev, typeof(*(entry)), member)

static inline bool list_is_first(const struct list_node *head,
				 const struct list_node *node)
{
	return node == head->next;
}

static inline bool list_is_last(const struct list_node *head,
				const struct list_node *node)
{
	return node == head->prev;
}

static inline bool list_is_empty(const struct list_node *head)
{
	return head == head->next;
}

static inline bool list_is_head(const struct list_node *head,
				const struct list_node *node)
{
	return node == head;
}

#define list_entry_is_head(head, entry, member) \
	list_is_head((head), &(entry)->member)

#endif /* LIST_H */
