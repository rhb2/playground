#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "tree.h"


node_t *
find_node(node_t *pn, int val)
{
	node_t *left;
	node_t *right;

	if (pn == NULL)
		return (NULL);

	if (pn->val == val)
		return (pn);

	left = find_node(pn->left, val);
	right = find_node(pn->right, val);

	if (left == NULL && right == NULL)
		return (NULL);

	return (left != NULL ? left : right);	
}

node_t *
find_ancestor_impl(node_t *pn, int p, int q, node_t **ppn)
{
	node_t *left;
	node_t *right;

	assert(ppn != NULL);

	if (pn == NULL)
		return (NULL);

	if (pn->val == p)
		return (pn);

	left = find_ancestor_impl(pn->left, p, q, ppn);
	right = find_ancestor_impl(pn->right, p, q, ppn);

	if (left != NULL) {
		if (find_node(pn->right, q) != NULL)
			*ppn = pn;
	}

	if (right != NULL) {
		if (find_node(pn->left, q) != NULL)
			*ppn = pn;
	}

	return (left != NULL ? left : right);
}

bool
find_ancestor(tree_t *pt, int p, int q, node_t **ppn)
{
	assert(pt != NULL && ppn != NULL);

	*ppn = NULL;

	return (find_ancestor_impl(pt->root, p, q, ppn) && *ppn != NULL);
}

void
find_ancestor_test(tree_t *pt, int p, int q)
{
	node_t *common = NULL;

	assert(pt != NULL);

	if (find_ancestor(pt, p, q, &common)) {
		printf("Common ancestor between %d and %d: %d\n",
		    p, q, common->val);
	} else {
		printf("%d and %d have no common ancestor\n", p, q);
	}

}

int main(int argc, char **argv)
{
	int elems, i;
	tree_t tree;
	node_t *common;

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

	find_ancestor_test(&tree, 2, 12);
	find_ancestor_test(&tree, 3, 11);
	find_ancestor_test(&tree, 10, 14);
	find_ancestor_test(&tree, 2, 4);
	find_ancestor_test(&tree, 3, 5);

	return (0);
}
