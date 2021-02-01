#include <iostream>
#include <cassert>

#include "../util/cpptree.h"

/*
 * Function to find a node matching the value in a binary tree.  Note, this
 * is intended to work on a tree which is not necessarily a BST, so once
 * again, we are looking at O(n) complexity to search.
 */
node<int> *
find_node(node<int> *pn, int target)
{
	node<int> *left, *right;

	if (pn == NULL)
		return (NULL);

	if (pn->val == target)
		return (pn);

	left = find_node(pn->left, target);
	right = find_node(pn->right, target);

	return (left != NULL ? left : right);	
}

bool
is_subtree_impl(node<int> *pn1, node<int> *pn2)
{
	if (pn1 == NULL || pn2 == NULL)
		return (true);

	if (pn1->val != pn2->val)
		return (false);

	return (is_subtree_impl(pn1->left, pn2->left) && 
	    is_subtree_impl(pn1->right, pn2->right));
}

/*
 * Determine if t2 is a subtree of t1.
 */
bool
is_subtree(tree<int> &t1, tree<int> &t2)
{
	node<int> *pn;

	if ((pn = find_node(t1.root, t2.root->val)) == NULL)
		return (false);

	return (is_subtree_impl(pn, t2.root));
}

int main(int argc, char **argv)
{
	int i;
	tree<int> t1, t2;

	for (i = 0; i < 63; i++)
		t1.insert(i);
	/*
	 * The following sequence of insertions will create a tree that
	 * looks like the following (below).  This is a subtree of the
	 * one above that we just created.
	 *
	 *                49
	 *            51
	 *                53
	 *         55
	 *                57
	 *            59
	 *                61
	 */
	t2.insert(55);
	t2.insert(51);
	t2.insert(59);
	t2.insert(49);
	t2.insert(53);
	t2.insert(57);
	t2.insert(61);

	cout << t1 << endl;
	cout << t2 << endl;

	if (is_subtree(t1, t2))
		cout << "t2 is a subtree of t1." << endl;
	else
		cout << "t2 is not a subtree of t1." << endl;

	return (0);
}
