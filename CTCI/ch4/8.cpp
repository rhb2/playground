#include <iostream>
#include <stack>
#include <cassert>
#include "../util/cpptree.h"

using namespace std;


/*
 * Per the problem requirements, this function finds the node by performing a
 * depth first search, assuming that it's not a binary search tree.  That is,
 * a parent node, may not be greater than its left child and smaller than its
 * right child.  There may be absolutely no order at all to this tree.  For
 * that reason, the complexity of this function is O(n).  If we were allowed
 * to assume that it was a BST, we could reduce the complexity to O(log n).
 */
bool
find_node(node<int> *pn, int target, stack<int> &s)
{
	bool left, right;

	if (pn == NULL)
		return (false);

	s.push(pn->val);

	if (pn->val == target)
		return (true);

	if (find_node(pn->left, target, s) || find_node(pn->right, target, s))
		return (true);

	s.pop();
	return (false);
}

bool
find_common_ancestor(node<int> *pn, int t1, int t2)
{
	stack<int> s1, s2;

	/*
	 * One or both of the values specified apparently are not in the
	 * tree.  Return false in that case.
	 */
	if (!(find_node(pn, t1, s1) && find_node(pn, t2, s2)))
		return (false);

	while (s1.size() > s2.size())
		s1.pop();

	while (s2.size() > s1.size())
		s2.pop();

	while (s1.top() != s2.top()) {
		s1.pop();
		s2.pop();
	}

	cout << "First common ancestor is: " << s1.top() << endl;
	return (true);
}

int main(int argc, char **argv)
{
	int i, total;
	tree<int> t;
	stack<int> s1, s2;

	total = atoi(argv[1]);

	for (i = 0; i < total; i++)
		t.insert(i);

	cout << t << endl;
	find_common_ancestor(t.root, 12, 19);

	return (0);
}
