#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "tree.h"


#define	MAX_INT	0x7FFFFFFF
#define	MIN_INT	(MAX_INT * -1)

bool
is_bst_helper(node_t *pn, int min, int max)
{
	if (pn == NULL)
		return (true);

	/*
	 * First, validate that the current node is within the acceptable range
	 * dictated by `min' and `max'.  If it isn't, then return false.
	 */
	if (pn->val < min || pn->val >= max)
		return (false);

	/*
	 * Now validate the subtrees on either side of the current node using
	 * the current node's value as the `max' for the left subtree and
	 * the `min' for the right subtree.
	 */
	return (is_bst_helper(pn->left, min, pn->val) &&
	    is_bst_helper(pn->right, pn->val, max));
}

bool
is_bst(tree_t *pt)
{
	assert(pt != NULL);

	return (is_bst_helper(pt->root, MIN_INT, MAX_INT));
}

int main(int argc, char **argv)
{
	int elems, i;
	tree_t tree;

	assert(argc == 2);

	elems = atoi(argv[1]);
	(void) bzero(&tree, sizeof (tree_t));

	/*
	 * Note: I augmented tree_insert_helper() in tree.h to create a tree
	 * that was not a BST by generating a random number between 1 and 10
	 * and going right if it was greater than 5, otherwise left.
	 */
	for (i = 0; i < elems; i++)
		tree_insert(&tree, i);

	tree_print(&tree);

	if (is_bst(&tree)) {
		printf("Tree is BST.\n");
	} else {
		printf("Tree is not BST.\n");
	}

	return (0);
}
