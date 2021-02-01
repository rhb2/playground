#include <iostream>
#include <cassert>
#include "../util/cpptree.h"

using namespace std;

/*
 * Connect all children directly to their parent.
 */
void
linkup(node<int> *cur, node<int> *parent)
{
	if (cur == NULL)
		return;

	cur->parent = parent;
	linkup(cur->left, cur);
	linkup(cur->right, cur);
}

node<int> *
get_leftmost_child(node<int> *pn)
{
	if (pn->left == NULL)
		return (pn);

	for (; pn->left != NULL; pn = pn->left);

	return (pn);
}

node<int> *
get_first_right_parent(node<int> *pn)
{
	node<int> *parent = pn->parent;

	for (;;) {
		if (parent == NULL)
			return (NULL);

		if (parent->left == pn)
			return (parent);

		pn = parent;
		parent = parent->parent;
	}
}

node<int> *
get_successor(node<int> *pn)
{
	if (pn == NULL)
		return (NULL);

	if (pn->right)
		return (get_leftmost_child(pn->right));

	return (get_first_right_parent(pn));
}

int main(int argc, char **argv)
{
	int i, total;
	tree<int> t;
	node<int> *pn;

	total = atoi(argv[1]);

	for (i = 0; i < total; i++)
		t.insert(i);

	cout << t << endl;

	linkup(t.root, NULL);

	pn = get_leftmost_child(t.root);
	cout << *pn << endl;

	while ((pn = get_successor(pn)) != NULL)
		cout << *pn << endl;

	return (0);
}
