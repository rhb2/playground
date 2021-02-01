#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "tree.h"


int
tree_balance_helper(node_t *pn)
{
	int left, right;
	int diff;
	if (pn == NULL)
		return (0);

	left = tree_balance_helper(pn->left);
	right = tree_balance_helper(pn->right);

	if (left == 100 || right == 100)
		return (100);

	diff = left - right;

	if (diff < -1 || diff > 1)
		return (100);
	
	return (1 + (left > right ? left : right));
}

bool
tree_balanced(tree_t *pt)
{
	int balance;

	assert(pt != NULL);

	balance = tree_balance_helper(pt->root);

	return (balance != 100);
}

int main(int argc, char **argv)
{
	int elems, i;
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

	if (tree_balanced(&tree)) {
		printf("The tree is balanced\n");
	} else {
		printf("The tree is not balanced\n");
	}

	return (0);
}
