#ifndef _LINKED_LIST
#define	_LINKED_LIST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "node.h"


typedef struct linked_list {
	node_t *head;
	node_t *tail;
	struct linked_list *next;
} linked_list_t;

linked_list_t *ll_alloc(void);
void ll_print(linked_list_t *);
void ll_print_stats(linked_list_t *);
void ll_insert(linked_list_t *, node_t *);
bool ll_insert_ordered(linked_list_t *, node_t *, bool);
bool ll_insert_int(linked_list_t *, int);
bool ll_append_int(linked_list_t *, int);
bool ll_prepend_int(linked_list_t *, int);
void ll_prepend(linked_list_t *, node_t *);
void ll_append(linked_list_t *, node_t *);
void ll_reverse(linked_list_t *);
bool ll_remove_head(linked_list_t *, node_t **);
bool ll_remove_tail(linked_list_t *, node_t **);
bool ll_remove(linked_list_t *, int, node_t **);
bool ll_remove_int(linked_list_t *, int);
void ll_add_all(linked_list_t *, linked_list_t *);
node_t *ll_tail(linked_list_t *);
bool ll_peek_head(linked_list_t *, int *);
bool ll_peek_tail(linked_list_t *, int *);
node_t *ll_head(linked_list_t *, int *);
int ll_length(linked_list_t *);
linked_list_t *ll_create(int, bool);
void ll_destroy(linked_list_t *);
linked_list_t *ll_clone(linked_list_t *);


linked_list_t *
ll_alloc(void)
{
	linked_list_t *pl;

	pl = malloc(sizeof (linked_list_t));
	assert(pl != NULL);
	(void) bzero(pl, sizeof (linked_list_t));
	return (pl);
}

void
ll_print(linked_list_t *pl)
{
	node_t *tmp;

	assert(pl != NULL);

	for (tmp = pl->head; tmp != NULL; tmp = tmp->next)
		printf("%d ", tmp->val);

	printf("\n");
}

void
ll_print_stats(linked_list_t *pl)
{
	node_t *tmp;
	int count;

	assert(pl != NULL);

	printf("Head: ");
	node_print(pl->head, 0);

	printf("Tail: ");
	node_print(pl->tail, 0);

	for (count = 0, tmp = pl->head; tmp != NULL; tmp = tmp->next)
		count++;

	printf("Total elements: %d\n", count);
}

/*
 * Wrapper for ll_prepend() which was added late in the game.  Eventually this
 * API can probably be deprecated entirely, but for the time being, I would
 * rather not break exercises that rely on this interface.
 */
void
ll_insert(linked_list_t *pl, node_t *pn)
{
	ll_prepend(pl, pn);
}

/*
 * Ordered insert in to linked list.  The third argument specifies whether or
 * not we want to maintain a list of unique elements as we insert or not.
 */
bool
ll_insert_ordered(linked_list_t *pl, node_t *pn, bool unique)
{
	node_t *tmp;

	assert(pl != NULL && pn != NULL);

	if (pl->head == NULL || pl->head->val > pn->val) {
		pn->next = pl->head;
		pl->head = pn;

		if (pn->next == NULL)
			pl->tail = pn;

		return (true);
	}

	/*
	 * If we are here, then the list has at least one element, and moreover,
	 * the head of the list is smaller than the value that we are
	 * attempting to insert.
	 */	
	for (tmp = pl->head; tmp->next != NULL; tmp = tmp->next) {
		if (unique && tmp->val == pn->val)
			return (false);

		if (pn->val < tmp->next->val) {
			pn->next = tmp->next;
			tmp->next = pn;
			return (true);
		}
	}

	/* End of the list and it's apparently not unique. */
	if (unique && tmp->val == pn->val)
		return (false);

	/*
	 * If we are here, then we've made it to the end of the list.  Just
	 * tack it on to the end, since the element that we are attempting to
	 * insert is either unique, or it happens to be the case that it's
	 * not unique, but we don't care.
	 */
	tmp->next = pn;
	pl->head = pn;
	return (true);
}

bool
ll_insert_int(linked_list_t *pl, int num)
{
	node_t *pn;

	assert(pl != NULL);

	if ((pn = node_alloc(num)) == NULL)
		return (false);

	ll_insert(pl, pn);
	return (true);
}

void
ll_prepend(linked_list_t *pl, node_t *pn)
{
	node_t *tmp;

	assert(pl != NULL && pn != NULL);

	if (pl->head == NULL)
		pl->tail = pn;

	pn->next = pl->head;
	pl->head = pn;
}

void
ll_append(linked_list_t *pl, node_t *pn)
{

	assert(pl != NULL && pn != NULL);

	/* Empty list. */
	if (pl->head == NULL) {
		pl->head = pl->tail = pn;
		return;
	}

	pl->tail->next = pn;
	pl->tail = pn;
}

bool
ll_prepend_int(linked_list_t *pl, int num)
{
	assert(pl != NULL);

	return (ll_insert_int(pl, num));
}

bool
ll_append_int(linked_list_t *pl, int num)
{
	node_t *pn;

	assert(pl != NULL);

	if ((pn = node_alloc(num)) == NULL)
		return (false);

	ll_append(pl, pn);
	return (true);
}

bool
ll_remove_head(linked_list_t *pl, node_t **ppn)
{
	node_t *pn;

	assert(pl != NULL && ppn != NULL);

	if (pl->head == NULL)
		return (false);

	pn = pl->head;
	pl->head = pl->head->next;
	pn->next = NULL;
	*ppn = pn;

	/* Last element in the list. */
	if (pl->head == NULL)
		pl->tail = NULL;

	return (true);
}

bool
ll_remove_tail(linked_list_t *pl, node_t **ppn)
{
	node_t *pn;
	node_t *prev;
	assert(pl != NULL && ppn != NULL);

	/* Empty list. */
	if (pl->head == NULL)
		return (false);

	/* There is only one element in the list. */
	if (pl->head == pl->tail) {
		*ppn = pl->tail;
		pl->head = pl->tail = NULL;
		return (true);
	}

	/* There are at least two elements in this list. */
	for (pn = pl->head; pn->next != NULL; prev = pn, pn = pn->next);
	*ppn = pn;
	prev->next = NULL;
	pl->tail = prev;
	return (true);
}

bool
ll_remove(linked_list_t *pl, int val, node_t **ppn)
{
	node_t *pn;
	node_t *prev;

	assert(pl != NULL && ppn != NULL);

	if (pl->head == NULL)
		return (false);

	/* Last element in the list. */
	if (pl->head->val == val) {
		*ppn = pl->head;
		pl->head = pl->head->next;

		/* Set the tail to NULL if we just emptied the list. */
		if (pl->head == NULL)
			pl->tail = NULL;

		return (true);
	}

	/* Any other element in the list */
	for (pn = pl->head; pn != NULL; prev = pn, pn = pn->next) {
		if (pn->val == val) {
			prev->next = pn->next;
			pn->next = NULL;
			*ppn = pn;

			if (prev->next == NULL)
				pl->tail = prev;

			return (true);
		}
	}

	/* Element not found. */
	return (false);
}

/*
 * Should be used when the caller already knows exactly which element that
 * they want to remove from the list.  This is a wrapper for `ll_remove()'.
 * The only thing that it does beyond that function is it frees the node
 * if it is found.
 */
bool
ll_remove_int(linked_list_t *pl, int val)
{
	node_t *pn;
	bool ret;

	ret = ll_remove(pl, val, &pn);

	if (ret)
		free(pn);
	
	return (ret);
}

void
ll_add_all(linked_list_t *dst, linked_list_t *src)
{
	bool ret;
	node_t *pn;

	assert(src != NULL && dst != NULL);

	for (pn = src->head; pn != NULL; pn = pn->next) {
		ret = ll_append_int(dst, pn->val);
		assert(ret);
	}
}

void
ll_reverse(linked_list_t *pl)
{
	linked_list_t tmplist;
	node_t *pn;

	assert(pl != NULL);

	(void) bzero(&tmplist, sizeof (linked_list_t));

	while (ll_remove_head(pl, &pn))
		ll_insert(&tmplist, pn);

	pl->head = tmplist.head;
}

node_t *
ll_tail(linked_list_t *pl)
{
	node_t *pn;

	assert(pl != NULL);

	for (pn = pl->head; pn->next != NULL; pn = pn->next);

	return (pn);
}

bool
ll_peek_head(linked_list_t *pl, int *elem)
{
	assert(pl != NULL && elem != NULL);

	if (pl->head == NULL)
		return (false);

	*elem = pl->head->val;
	return (true);
}

bool
ll_peek_tail(linked_list_t *pl, int *elem)
{
	assert(pl != NULL && elem != NULL);

	if (pl->tail == NULL)
		return (false);

	*elem = pl->tail->val;
	return (true);
}

int
ll_length(linked_list_t *pl)
{
	int i = 0;
	node_t *pn;

	for (pn = pl->head; pn != NULL; pn = pn->next)
		i++;

	return (i);
}

linked_list_t *
ll_create(int len, bool ordered)
{
	int i, elem;
	node_t *pn;
	linked_list_t *pl;

	pl = malloc(sizeof (linked_list_t));
	assert(pl != NULL);

	(void) bzero(pl, sizeof (linked_list_t));

	for (i = 0; i < len; i++) {
		elem = ordered ? i : rand() % len;
		pn = node_alloc(elem);
		assert(pn != NULL);

		ll_insert(pl, pn);
	}

	return (pl);
}

void
ll_destroy(linked_list_t *lp)
{
	node_t *pn;
	node_t *last;

	assert(lp != NULL);

	pn = lp->head;

	while (pn != NULL) {
		last = pn;
		pn = pn->next;
		free(last);
	}

	free(lp);
}

/*
 * Perform a deep copy of a given linked list.
 */
linked_list_t *
ll_clone(linked_list_t *lp)
{
	linked_list_t *clp;
	node_t *pn;

	assert(lp != NULL);

	if ((clp = malloc(sizeof (linked_list_t))) == NULL)
		return (NULL);

	(void) bzero(clp, sizeof (linked_list_t));
	for (pn = lp->head; pn != NULL; pn = pn->next) {
		/*
		 * The only reason that something like this might not succeed
		 * is if we failed to allocate the underlying storage for the
		 * node that gets appended to the new list.
		 */
		if (!ll_append_int(clp, pn->val)) {
			ll_destroy(clp);
			return (NULL);
		}
	}
	return (clp);
}

#endif /* _LINKED_LIST */
