#ifndef _NODE_H
#define	_NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>


typedef struct node {
	int val;		/* Value store at this location. */
	struct node *left;	/* Left child. */
	struct node *right;	/* Right child. */
	struct node *next;	/* Hardly used except in bullshit problems. */
	struct node *parent;	/* Again, used for bullshit problems. */
} node_t;

node_t *node_alloc(int);
void node_print(node_t *, int);
node_t *node_step(node_t *, int);

node_t *
node_alloc(int val)
{
	node_t *pn;

	if ((pn = malloc(sizeof (node_t))) == NULL)
		return (NULL);

	(void) bzero(pn, sizeof (node_t));
	pn->val = val;
	return (pn);
}

void
node_print(node_t *pn, int depth)
{
	int i;

	assert(pn != NULL);

	for (i = 0; i < depth; i++)
		printf("   ");

	printf("%d\n", pn->val);
}

/*
 * Advance the iterator by a specified number of steps.  If we are at the end
 * of the list, return NULL.  That is, if we receive a NULL pointer, return
 * NULL back to the caller.
 */
node_t *
node_step(node_t *pn, int steps)
{
	int i;

	if (pn == NULL)
		return (NULL);

	for (i = 0; i < steps; i++) {
		if (pn == NULL)
			return (NULL);

		pn = pn->next;
	}

	return (pn);
}

#endif	/* _NODE_H */
