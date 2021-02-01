#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "tree.h"


#define	SMALL	7
#define	BIG	15

bool
tree_eq(node_t *pn1, node_t *pn2)
{
	/* This handles the NULL case too. */
	if (pn1 == pn2)
		return (true);

	if (pn1 == NULL || pn2 == NULL)
		return (false);

	if (pn1->val != pn2->val)
		return (false);

	return (tree_eq(pn1->left, pn2->left) &&
	    tree_eq(pn1->right, pn2->right));
}

bool
subtree_impl(node_t *big, node_t *small)
{
	if (big == small)
		return (true);

	if (big == NULL || small == NULL)
		return (false);

	if ((big->val == small->val) && tree_eq(big, small))
		return (true);

	return (subtree_impl(big->left, small) ||
	    subtree_impl(big->right, small));
}

/*
 * Determine if the small tree is a subtree of the larger tree.
 */
bool
subtree(tree_t *big, tree_t *small)
{
	assert(big != NULL && small != NULL);

	if (small->root == NULL)
		return (true);

	return (subtree_impl(big->root, small->root));
}

int main(int argc, char **argv)
{
	int i;
	tree_t small;
	tree_t big;

	(void) bzero(&small, sizeof (tree_t));
	(void) bzero(&big, sizeof (tree_t));

	for (i = 0; i < SMALL; i++)
		tree_insert(&small, i);

	for (i = 0; i < BIG; i++)
		tree_insert(&big, i);

	printf("Small tree:\n");
	tree_print(&small);
	printf("\nBig tree:\n");
	tree_print(&big);

	if (subtree(&big, &small))
		printf("`small' is a subtree of `big'.\n");
	else
		printf("`small' is not a subtree of `big'.\n");

	/*
	 * Change the small subtree enough such that it is unlike any subtree
	 * in the larger tree.  Fortunately, for us, that just requires the
	 * addition of a single element.
	 */
	printf("\nAdd another element to the small tree and re-test.\n");
	tree_insert(&small, 20);

	printf("Small tree:\n");
	tree_print(&small);
	printf("\nBig tree:\n");
	tree_print(&big);

	if (subtree(&big, &small))
		printf("`small' is a subtree of `big'.\n");
	else
		printf("`small' is not a subtree of `big'.\n");

	return (0);
}
