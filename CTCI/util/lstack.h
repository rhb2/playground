#ifndef	_LSTACK_H
#define	_LSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "linkedlist.h"


typedef struct lstack {
	linked_list_t list;
} lstack_t;

void lstack_init(lstack_t *);
bool lstack_push(lstack_t *, int);
bool lstack_pop(lstack_t *, int *);
bool lstack_peek(lstack_t *, int *);
bool lstack_full(lstack_t *);
bool lstack_empty(lstack_t *);
int lstack_size(lstack_t *);
void lstack_print(lstack_t *);

void
lstack_init(lstack_t *sp)
{
	assert(sp != NULL);

	(void) bzero(sp, sizeof (lstack_t));
}

bool
lstack_push(lstack_t *sp, int val)
{
	node_t *np;

	assert(sp != NULL);

	if ((np = node_alloc(val)) == NULL)
		return (false);

	ll_insert(&sp->list, np);
	return (true);
}

bool
lstack_pop(lstack_t *sp, int *elem)
{
	node_t *np;

	assert(sp != NULL && elem != NULL);

	if (!ll_remove_head(&sp->list, &np))
		return (false);

	*elem = np->val;
	free(np);
	return (true);
}

bool
lstack_peek(lstack_t *sp, int *elem)
{
	return (ll_peek_head(&sp->list, elem));
}

bool
lstack_empty(lstack_t *sp)
{
	assert(sp != NULL);

	return (sp->list.head == NULL);
}

int
lstack_size(lstack_t *sp)
{
	assert(sp != NULL);

	return (ll_length(&sp->list));
}

void
lstack_print(lstack_t *sp)
{
	assert(sp != NULL);

	ll_print(&sp->list);
}

void
lstack_print_reverse_helper(node_t *pn)
{
	if (pn == NULL)
		return;

	lstack_print_reverse_helper(pn->next);
	printf("%d ", pn->val);
}

void
lstack_print_reverse(lstack_t *sp)
{
	assert(sp != NULL);
	lstack_print_reverse_helper(sp->list.head);
}

#endif	/* _LSTACK_H */
