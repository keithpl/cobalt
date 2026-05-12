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

static inline void list_link(struct list_node *prev, struct list_node *next)
{
	prev->next = next;
	next->prev = prev;
}

static inline void list_init(struct list_node *node)
{
	list_link(node, node);
}

static inline void list_insert(struct list_node *node,
			       struct list_node *prev,
			       struct list_node *next)
{
	list_link(prev, node);
	list_link(node, next);
}

static inline void list_add(struct list_node *head, struct list_node *node)
{
	list_insert(node, head, head->next);
}

static inline void list_add_tail(struct list_node *head, struct list_node *node)
{
	list_insert(node, head->prev, head);
}

static inline void list_del(struct list_node *node)
{
	list_link(node->prev, node->next);
}

static inline void list_del_init(struct list_node *node)
{
	list_del(node);
	list_init(node);
}

static inline void list_move(struct list_node *dst_head,
			     struct list_node *node)
{
	list_del(node);
	list_add(dst_head, node);
}

static inline void list_move_tail(struct list_node *dst_head,
				  struct list_node *node)
{
	list_del(node);
	list_add_tail(dst_head, node);
}

static inline void list_replace(struct list_node *old_node,
				struct list_node *new_node)
{
	list_insert(new_node, old_node->prev, old_node->next);
}

static inline void list_replace_init(struct list_node *old_node,
				     struct list_node *new_node)
{
	list_replace(old_node, new_node);
	list_init(old_node);
}

#endif /* LIST_H */
