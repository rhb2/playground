#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "tree.h"


/*
 * Given a node in a tree, continue moving up the tree until we find an
 * ancestor that is greater than the value in the caller-supplied node.
 */
node_t *
move_up(node_t *pn)
{
	node_t *parent = NULL;

	assert(pn != NULL);

	while (pn != NULL) {
		parent = pn->parent;

		if (parent == NULL)
			break;

		/*
		 * Finally, we have found an ancestor that is larger than us
		 * in the BST.  Return it.
		 */
		if (parent->left == pn)
			break;

		/* Nothing yet.  Continue moving up. */
		pn = parent;
		parent = parent->parent;
	}

	return (parent);
}

node_t *
get_left_most(node_t *pn)
{
	assert(pn != NULL);

	for (; pn->left != NULL; pn = pn->left);

	return (pn);
}

node_t *
get_successor(node_t *pn)
{
	node_t *successor;

	if (pn->right)
		return (get_left_most(pn->right));

	return (move_up(pn));
}

void
tree_print_inorder(node_t *pn)
{
	if (pn == NULL)
		return;

	tree_print_inorder(pn->left);
	printf("%d ", pn->val);
	tree_print_inorder(pn->right);
}

void
print_successors(node_t *pn)
{
	node_t *successor;

	if (pn == NULL)
		return;

	print_successors(pn->left);

	if ((successor = get_successor(pn)) != NULL) {
		printf("Successor of %d is %d.\n", pn->val, successor->val);
	} else {
		printf("%d has no successor.\n", pn->val);
	}

	print_successors(pn->right);
}

int main(int argc, char **argv)
{
	int elems, i;
	node_t *pn;
	tree_t tree;

	assert(argc == 2);

	elems = atoi(argv[1]);
	(void) bzero(&tree, sizeof (tree_t));

	printf("Tree structure:\n");
	for (i = 0; i < elems; i++)
		tree_insert(&tree, i);

	tree_print(&tree);
	printf("\n\nIn order traversal: ");
	tree_print_inorder(tree.root);
	printf("\n\n");

	/*
	 * Walk the tree, and set each child's parent point to point at its
	 * parent.
	 */
	tree_link_up(&tree);

	/* For every node in the tree, print its successor. */
	print_successors(tree.root);
	return (0);
}
