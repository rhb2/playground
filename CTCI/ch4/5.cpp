#include <iostream>
#include <cassert>
#include "../util/cpptree.h"

using namespace std;

bool
is_bst(node<int> *pn, int min, int max)
{
	bool left, right;

	if (pn == NULL)
		return (true);

	if (pn->val < min || pn->val > max)
		return (false);

	left = is_bst(pn->left, min, pn->val);
	right = is_bst(pn->right, pn->val, max);

	return (left && right);	
}


int main(int argc, char **argv)
{
	int i, total;
	tree<int> t;

	total = atoi(argv[1]);

	for (i = 0; i < total; i++)
		t.insert(i);

	cout << t << endl;

	if (is_bst(t.root, INT_MIN, INT_MAX))
		cout << "Tree is a valid BST." << endl;
	else
		cout << "Tree is not a valid BST." << endl;


	t.root->right->right->val = 100;

	cout << t << endl;

	if (is_bst(t.root, INT_MIN, INT_MAX))
		cout << "Tree is a valid BST." << endl;
	else
		cout << "Tree is not a valid BST." << endl;

	return (0);
}
