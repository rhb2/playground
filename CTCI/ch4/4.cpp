/*
 * This uses a recursive technique to check the balance at every subtree in the
 * tree.  It works, but another interesting idea might be to get the total
 * number of nodes at each level and if that number isn't a power of two,
 * disqualify it (unless it's the last level).
 */
#include <iostream>
#include <list>
#include <vector>
#include <cassert>

#include "../util/cpptree.h"

using namespace std;

int
get_height(node<int> *pn)
{
	int left, right;

	if (pn == NULL)
		return (0);

	left = get_height(pn->left);
	right = get_height(pn->right);
	return (1 + max(left, right));	
}

bool
is_balanced(node<int> *pn)
{
	bool left, right;

	if (pn == NULL)
		return (true);

	left = is_balanced(pn->left);
	right = is_balanced(pn->right);

	if (!left || !right)
		return (false);

	return (abs(get_height(pn->left) - get_height(pn->right)) < 2);
}

int main(int argc, char **argv)
{
	int i, total;
	tree<int> t, t2;
	node<int> pn(1);

	total = atoi(argv[1]);

	for (i = 0; i < total; i++)
		t.insert(i);

	for (i = 1; i < total; i++)
		t.insert(i * -1);

	cout << t;

	if (is_balanced(t.root))
		cout << "Tree is balanced." << endl;
	else
		cout << "Tree is not balanced." << endl;

	cout << endl;

	/*
	 * Now create a fake tree where the right side points to the entire
	 * tree that was created above and the left side is NULL.  This should
	 * be horribly imbalanced.
	 */
	t2.root = &pn;
	pn.right = t.root;

	cout << t2;

	if (is_balanced(&pn))
		cout << "Tree is balanced." << endl;
	else
		cout << "Tree is not balanced." << endl;

	t2.root = NULL;

	return (0);
}
