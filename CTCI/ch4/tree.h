#ifndef	_TREE_H
#define	_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "../util/node.h"


#ifdef LOL
typedef struct node {
	int val;		/* Value store at this location. */
	struct node *left;	/* Left child. */
	struct node *right;	/* Right child. */
	struct node *next;	/* Hardly used except in bullshit problems. */
	struct node *parent;	/* Again, used for bullshit problems. */
} node_t;
#endif

typedef struct tree {
	node_t *root;	/* Root of the tree. */
} tree_t;

void tree_print_helper(node_t *, int);
void tree_print(tree_t *);
void tree_init(tree_t *);
int tree_get_height(node_t *);
int tree_get_balance(node_t *);
node_t *tree_get_last(node_t *);
void tree_link_up(tree_t *);
bool tree_has(tree_t *, int val);

/*
 * The node queue and its subsequent methods are intended to queue up pointers
 * to node_t strucutres that comprise a tree.  The primary application for it
 * is to perform breadth-first operations on a binary tree.
 */
typedef struct node_queue {
	node_t **array;	/* Array of node pointers. */
	int capacity;	/* Capacity of the queue. */
	int front;	/* Front of queue. */
	int back;	/* Back of queue. */
} node_queue_t;

bool node_queue_init(node_queue_t *, int);
void node_queue_desroy(node_queue_t *);
bool node_queue_full(node_queue_t *);
bool node_queue_empty(node_queue_t *);
bool node_queue_insert(node_queue_t *, node_t *);
bool node_queue_remove(node_queue_t *, node_t **);

bool
node_queue_init(node_queue_t *pnq, int capacity)
{
	node_t **array;
	assert(pnq != NULL);

	if (capacity <= 1)
		capacity++;

	if ((array = malloc(capacity * sizeof (node_t *))) == NULL)
		return (false);

	(void) bzero(pnq, sizeof (node_queue_t));
	pnq->array = array;
	pnq->capacity = capacity;
	return (true);
}

void
node_queue_destroy(node_queue_t *pnq)
{
	assert(pnq != NULL);

	free(pnq->array);
 	(void) bzero(pnq, sizeof (node_queue_t));
}

bool
node_queue_full(node_queue_t *pnq)
{
	assert(pnq != NULL);

	return ((pnq->front + 1) % pnq->capacity == pnq->back);
}

bool
node_queue_empty(node_queue_t *pnq)
{
	assert(pnq != NULL);

	return (pnq->front == pnq->back);
}

bool
node_queue_insert(node_queue_t *pnq, node_t *pn)
{
	assert(pnq != NULL);

	if (pn == NULL)
		return (false);

	if (node_queue_full(pnq))
		return (false);

	pnq->array[pnq->front] = pn;
	pnq->front = (pnq->front + 1) % pnq->capacity;
	return (true);
}

bool
node_queue_remove(node_queue_t *pnq, node_t **ppn)
{
	assert(pnq != NULL && ppn != NULL);

	if (node_queue_empty(pnq))
		return (false);

	*ppn = pnq->array[pnq->back];
	pnq->back = (pnq->back + 1) % pnq->capacity;
	return (true);
}

void
tree_print_helper(node_t *pn, int level)
{
	if (pn == NULL)
		return;

	tree_print_helper(pn->right, level + 1);
	node_print(pn, level);
	tree_print_helper(pn->left, level + 1);
}

void
tree_print(tree_t *pt)
{
	assert(pt != NULL);

	tree_print_helper(pt->root, 0);
}

static void
rotate_left(node_t **ppn)
{
	node_t *root;
	node_t *right;

	assert(ppn != NULL);

	if ((root = *ppn) == NULL)
		return;

	right = root->right;
	root->right = right->left;
	right->left = root;
	*ppn = right;
}

static void
rotate_right(node_t **ppn)
{
	node_t *root;
	node_t *left;

	assert(ppn != NULL);

	if ((root = *ppn) == NULL)
		return;

	left = root->left;
	root->left = left->right;
	left->right = root;
	*ppn = left;
}

int
tree_get_balance(node_t *pn)
{
	if (pn == NULL)
		return (0);

	return (tree_get_height(pn->left) - tree_get_height(pn->right));
}

int
tree_get_height(node_t *pn)
{
	int left;
	int right;
	if (pn == NULL)
		return (0);

	left = tree_get_height(pn->left);
	right = tree_get_height(pn->right);
	return (1 + (left > right ? left : right));
}

int
tree_get_count(node_t *pn)
{
	if (pn == NULL)
		return (0);

	return (1 + tree_get_count(pn->left) + tree_get_count(pn->right));
}

static void
tree_balance(node_t **ppn)
{
	int balance;
	node_t *root;

	assert(ppn != NULL);

	if ((root = *ppn) == NULL)
		return;

	balance = tree_get_balance(root);

	if (balance == 2) {
		/* Left heavy.  Better rotate right. */
		if (tree_get_balance(root->right) == -1)
			rotate_left(&root->right);
		rotate_right(ppn);
	} else if (balance == -2) {
		if (tree_get_balance(root->left) == 1)
			rotate_right(&root->left);
		rotate_left(ppn);
	}	
}

void
tree_insert_helper(node_t **ppn, node_t *pn)
{
	node_t **child;
	node_t *root;

	assert(ppn != NULL && pn != NULL);

	if ((root = *ppn) == NULL) {
		*ppn = pn;
		return;
	}

//	child = rand() % 10 > 5 ?  &root->right : &root->left;
	child = pn->val >= root->val ? &root->right : &root->left;
	tree_insert_helper(child, pn);
	tree_balance(ppn);
}

void
tree_insert(tree_t *pt, int val)
{
	node_t *pn;

	assert(pt != NULL);

	pn = node_alloc(val);

	assert(pn != NULL);

	tree_insert_helper(&pt->root, pn);
}

bool
tree_has(tree_t *pt, int val)
{
	node_t *pn;

	assert(pt != NULL);

	for (pn = pt->root; pn != NULL;) {
		if (val == pn->val)
			return (true);

		pn = (val >= pn->val) ? pn->right : pn->left;
	}

	return (false);
}

node_t *
tree_get_last(node_t *pn)
{
	int count;
	node_t *last;
	bool ret;
	node_queue_t nq;

	assert(pn != NULL);
	if ((count = tree_get_count(pn)) == 0)
		return (NULL);

	ret = node_queue_init(&nq, count);
	assert(ret);

	(void) node_queue_insert(&nq, pn);

	while (!node_queue_empty(&nq)) {
		(void) node_queue_remove(&nq, &last);

		if (last->right == NULL)
			break;

		(void) node_queue_insert(&nq, last->left);
		(void) node_queue_insert(&nq, last->right);
	}

	node_queue_destroy(&nq);

	return (last);
}

static void
tree_link_up_helper(node_t *pn)
{
	if (pn == NULL)
		return;

	if (pn->left)
		pn->left->parent = pn;

	if (pn->right)
		pn->right->parent = pn;

	tree_link_up_helper(pn->left);
	tree_link_up_helper(pn->right);
}

void
tree_link_up(tree_t *pt)
{
	assert(pt != NULL);

	tree_link_up_helper(pt->root);
}

#endif	/* _TREE_H */
