#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "../util/node.h"
#include "../util/tree.h"


int
get_rank_helper(node_t *pn, int val)
{
	int count;
	int ret;

	/*
	 * If we reach this point, then it means that the value that we were
	 * looking for was not found.  Or, at least it was not found in this
	 * part of the subtree.  Propogate this back up the stack.  The only
	 * way that this won't make it all the way back to the caller is if
	 * the value happens to exist somewhere else above us in the tree.
	 */
	if (pn == NULL)
		return (-1);

	if (val < pn->val)
		return (get_rank_helper(pn->left, val));

	ret = get_rank_helper(pn->right, val);

	/*
	 * If the value was not found to the right of us, _and_ it is the case
	 * that we it is not present here, then propogate that -1 result up
	 * the stack.  The reason this check is necessary is because we are
	 * working with a tree that can contain duplicate values.  Moreover,
	 * when inserting in to the tree, the heuristic is that any value that
	 * is greater than or equal to the current value must go right.  This
	 * is why we must still search the right subtree even if we find what
	 * we are looking for.  Another node with the same value could still be
	 * in the right subtree and we need to account for its rank as well.
	 */
	if (ret == -1 && pn->val != val)
		return (-1);

	/*
	 * Get a count of all elements in the left subtree, before recursing
	 * to the right.  Sadly, that will all turn out to be a colossal waste
	 * of time if we do not find what we are looking for.
	 */
	count = tree_get_count(pn->left) + 1;
	return (count + get_rank_helper(pn->right, val));
}

/*
 * This function will -- given a BST -- return a count of all nodes that are
 * less than or equal to the value supplied by the caller in `val'.  Note,
 * the tree can contain duplicate values.  One thing that would make this
 * problem much easier to solve is if insead of allowing duplicates, each
 * node kept a count of the total number of times that it occurred within a
 * tree.  This way, we would not have to deal with situations where we find
 * the node that we are looking for but still need to recurse.  At the same
 * time, the advantage to this approach is that it can be done with any tree
 * and does not require state information like that.
 */
int
get_rank(tree_t *tp, int val)
{
	assert(tp != NULL);

	return (get_rank_helper(tp->root, val));
}

void
test_get_rank(tree_t *pt, int val)
{
	int ret;

	assert(pt != NULL);

	ret = get_rank(pt, val);
	printf("get_rank(%d) = %d\n", val, ret);
}

int main(int argc, char **argv)
{
	int i;
	int array[] = {5, 1, 4, 4, 5, 9, 7, 13, 3};
	int len = sizeof (array) / sizeof (array[0]);
	tree_t tree;


	(void) bzero(&tree, sizeof (tree_t));

	for (i = 0; i < len; i++)
		(void) tree_insert(&tree, array[i]);
	
	tree_print(&tree);

	test_get_rank(&tree, 1);
	test_get_rank(&tree, 3);
	test_get_rank(&tree, 4);
	test_get_rank(&tree, 5);
	test_get_rank(&tree, 6);

	return (0);
}
