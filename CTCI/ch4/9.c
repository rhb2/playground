#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "tree.h"
#include "../util/linkedlist.h"


/* Don't ask. */
typedef struct array_list {
	linked_list_t *list;
} array_list_t;

array_list_t *
array_list_alloc()
{
	array_list_t *pal;

	pal = malloc(sizeof (array_list_t));
	assert(pal != NULL);
	(void) bzero(pal, sizeof (array_list_t));
	return (pal);
}

void
array_list_add(array_list_t *pal, linked_list_t *pl)
{
	linked_list_t *tmp;

	assert(pal != NULL && pl != NULL);

	/* Empty array list. */
	if (pal->list == NULL) {
		pal->list = pl;
		return;
	}

	/* Get to the end of the array list, then add the new result. */
	for (tmp = pal->list; tmp->next != NULL; tmp = tmp->next);
	tmp->next = pl;
}

void
array_list_print(array_list_t *pal)
{
	linked_list_t *pl;

	assert(pal != NULL);

	for (pl = pal->list; pl != NULL; pl = pl->next)
		ll_print(pl);
}

void
weave_lists(linked_list_t *first, linked_list_t *second, array_list_t *results,
    linked_list_t *prefix)
{
	node_t *headfirst;
	node_t *headsecond;

	assert(first != NULL && second != NULL && results != NULL &&
	    prefix != NULL);

	if (ll_length(first) == 0 || ll_length(second) == 0) {
		linked_list_t *pl;
		linked_list_t *result = ll_clone(prefix);
		ll_add_all(result, first);
		ll_add_all(result, second);

		array_list_add(results, result);
		return;
	}

	/*
	 * Recurse with the head of the first added to the prefix.  Removing
	 * the head will damage the first list, so we will need to put it back
	 * where we found it when we are done.
	 */
	(void) ll_remove_head(first, &headfirst);
	(void) ll_append(prefix, headfirst);
	weave_lists(first, second, results, prefix);
	(void) ll_remove_tail(prefix, &headfirst);
	(void) ll_prepend(first, headfirst);

	/*
	 * Do the same thing for the second list, damaging it, then repairing
	 * it.
	 */
	(void) ll_remove_head(second, &headsecond);
	(void) ll_append(prefix, headsecond);
	weave_lists(first, second, results, prefix);
	(void) ll_remove_tail(prefix, &headsecond);
	(void) ll_prepend(second, headsecond);
}

array_list_t *
all_sequences(node_t *pn)
{
	array_list_t *result;
	array_list_t *left;
	array_list_t *right;
	linked_list_t *prefix;
	linked_list_t *pl;
	linked_list_t *pr;

	result = array_list_alloc();

	if (pn == NULL) {
		linked_list_t *list = ll_alloc();
		array_list_add(result, list);
		return (result);
	}

	prefix = ll_alloc();
	(void) ll_append_int(prefix, pn->val);

	left = all_sequences(pn->left);
	right = all_sequences(pn->right);

	for (pl = left->list; pl != NULL; pl = pl->next) {
		for (pr = right->list; pr != NULL; pr = pr->next) {
			array_list_t *weaved = array_list_alloc();
			weave_lists(pl, pr, weaved, prefix);
                        array_list_add(result, weaved->list);
			free(weaved);
		}
	}

	free(prefix);
	return (result);
}

int main(int argc, char **argv)
{
	int elems, i;
	tree_t tree;
	array_list_t *seq;

	assert(argc == 2);

	elems = atoi(argv[1]);
	(void) bzero(&tree, sizeof (tree_t));

	/*
	 * Note: If you want to build an unbalanced tree quickly, go over to
	 * tree.h and comment out the line the performs the balance upon insert.
	 */
	for (i = 0; i < elems; i++)
		tree_insert(&tree, i);

	printf("Tree structure:\n");
	tree_print(&tree);

	seq = all_sequences(tree.root);
	printf("\nAll sequences of insertions that could build this tree:\n");
	array_list_print(seq);
	return (0);
}
