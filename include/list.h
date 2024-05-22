#if !defined(LIST_H)
#define LIST_H

#include <stdbool.h>
#include <stddef.h>

#include "cdefs.h"

struct list_node {
	struct list_node *next, *prev;
};

#define list_entry(node, type, field) \
	container_of(node, type, field)

#define list_is_head(head, entry, field) \
	(&(entry)->field == (head))

#define list_first(head, type, field) \
	list_entry((head)->next, type, field)

#define list_last(head, type, field) \
	list_entry((head)->prev, type, field)

#define list_next(entry, type, field) \
	list_entry((entry)->field.next, type, field)

#define list_prev(entry, type, field) \
	list_entry((entry)->field.prev, type, field)

#define list_for_each(head, pos)					\
	for ((pos) = (head)->next;					\
	     (pos) != (head);						\
	     (pos) = (pos)->next)

#define list_for_each_tail(head, pos)					\
	for ((pos) = (head)->prev;					\
	     (pos) != (head);						\
	     (pos) = (pos)->prev)

#define list_for_each_safe(head, pos, tmp)				\
	for ((pos) = (head)->next, (tmp) = (pos)->next;			\
	     (pos) != (head);						\
	     (pos) = (tmp), (tmp) = (pos)->next)

#define list_for_each_tail_safe(head, pos, tmp)				\
	for ((pos) = (head)->prev, (tmp) = (pos)->prev;			\
	     (pos) != (head);						\
	     (pos) = (tmp), (tmp) = (pos)->prev)

#define list_for_each_entry(head, pos, type, field)			\
	for ((pos) = list_first((head), type, field);			\
	     !list_is_head((head), (pos), field);			\
	     (pos) = list_next((pos), type, field))

#define list_for_each_entry_tail(head, pos, type, field)		\
	for ((pos) = list_last((head), type, field);			\
	     !list_is_head((head), (pos), field);			\
	     (pos) = list_prev((pos), type, field))

#define list_for_each_entry_safe(head, pos, tmp, type, field)		\
	for ((pos) = list_first((head), type, field),			\
	     (tmp) = list_next((pos), type, field);			\
	     !list_is_head((head), (pos), field);			\
	     (pos) = (tmp), (tmp) = list_next((pos), type, field))

#define list_for_each_entry_tail_safe(head, pos, tmp, type, field)	\
	for ((pos) = list_last((head), type, field),			\
	     (tmp) = list_prev((pos), type, field);			\
	     !list_is_head((head), (pos), field);			\
	     (pos) = (tmp), (tmp) = list_prev((pos), type, field))

static inline bool list_is_first(const struct list_node *head,
				 const struct list_node *node)
{
	return head->next == node;
}

static inline bool list_is_last(const struct list_node *head,
				const struct list_node *node)
{
	return head->prev == node;
}

static inline bool list_is_empty(const struct list_node *head)
{
	return head->next == head;
}

static inline void list_link(struct list_node *prev, struct list_node *next)
{
	prev->next = next;
	next->prev = prev;
}

static inline void list_init(struct list_node *head)
{
	list_link(head, head);
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

static inline void list_add_tail(struct list_node *head,
				 struct list_node *node)
{
	list_insert(node, head->prev, head);
}

static inline void list_del(struct list_node *node)
{
	list_link(node->prev, node->next);
}

static inline void list_del_explicit(struct list_node *node)
{
	list_del(node);
	node->prev = NULL;
	node->next = NULL;
}

#endif /* !defined(LIST_H) */
