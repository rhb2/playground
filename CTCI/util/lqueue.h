/*
 * List-based queue implementation.  This is essentially a wrapper for the
 * (singly) linked list data structure where insertions take place at the
 * tail of the list and removal takes place at the head.  This allows for both
 * operations to be performed in O(1) time.
 */
#ifndef _LQUEUE_H
#define	_LQUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "linkedlist.h"


typedef struct lqueue {
	linked_list_t list;
} lqueue_t;

void lqueue_init(lqueue_t *);
bool lqueue_insert(lqueue_t *, int);
bool lqueue_remove(lqueue_t *, int *);
bool lqueue_peek(lqueue_t *, int *);
void lqueue_print(lqueue_t *);

void
lqueue_init(lqueue_t *pq)
{
	assert(pq != NULL);

	(void) bzero(pq, sizeof (lqueue_t));
}

bool
lqueue_insert(lqueue_t *pq, int elem)
{
	node_t *np;

	if ((np = node_alloc(elem)) == NULL)
		return (false);

	ll_append(&pq->list, np);
	return (true);
}

bool
lqueue_remove(lqueue_t *pq, int *elem)
{
	node_t *np;

	assert(pq != NULL && elem != NULL);

	if (!ll_remove_head(&pq->list, &np))
		return (false);

	*elem = np->val;
	free(np);
	return (true);
}

bool
lqueue_peek(lqueue_t *pq, int *elem)
{
	return (ll_peek_head(&pq->list, elem));
}

void
lqueue_print(lqueue_t *pq)
{
	assert(pq != NULL);

	ll_print(&pq->list);
}

#endif	/* _LQUEUE_H */
