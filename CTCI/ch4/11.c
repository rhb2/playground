#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "tree.h"


void
get_random(tree_t *pt)
{
	int total, index;
	int i = 0;
	node_queue_t nq;
	node_t *pn;
	bool ret;

	assert(pt != NULL);

	if ((total = tree_get_count(pt->root)) == 0)
		return;

	index = rand() % total;

	ret = node_queue_init(&nq, total);
	assert(ret);

	(void) node_queue_insert(&nq, pt->root);

	while (!node_queue_empty(&nq)) {
		(void) node_queue_remove(&nq, &pn);
		if (i == index)
			break;

		i++;
		(void) node_queue_insert(&nq, pn->left);
		(void) node_queue_insert(&nq, pn->right);
	}

	printf("Random node: %d\n", pn->val);
	node_queue_destroy(&nq);
	printf("\n");
}

int main(int argc, char **argv)
{
	int elems, i, sum;
	tree_t tree;

	assert(argc == 2);

	elems = atoi(argv[1]);
	(void) bzero(&tree, sizeof (tree_t));

	/*
	 * Note: If you want to build an unbalanced tree quickly, go over to
	 * tree.h and comment out the line the performs the balance upon insert.
	 */
	for (i = 0; i < elems; i++)
		tree_insert(&tree, i);

	tree_print(&tree);
	printf("\n");

	get_random(&tree);

	return (0);
}
