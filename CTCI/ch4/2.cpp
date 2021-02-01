#include <iostream>
#include <vector>
#include <cassert>
#include "../util/cpptree.h"

using namespace std;


ostream &
operator <<(ostream &out, const vector<int> &v)
{
	int i;

	for (i = 0; i < v.size(); i++)
		out << v[i] << " ";

	return (out);
}

void
build_tree(vector<int> &v, int left, int right, int depth, node<int> **ppn)
{
	int i, center;
	node<int> *pn;

	if (left >= right) {
		if (left == right) {
			*ppn = new node<int>(left);
		}
		return;
	}

	center = (left + right) / 2;

	pn = new node<int>(v[center]);
	*ppn = pn;

	build_tree(v, left, center - 1, depth + 1, &pn->left);
	build_tree(v, center + 1, right, depth + 1, &pn->right);
}

int main(int argc, char **argv)
{
	int i;
	int total = atoi(argv[1]);
	vector<int> v;
	tree<int> t;

	for (i = 0; i < total; i++)
		v.push_back(i);

	cout << v << endl;

	build_tree(v, 0, v.size() - 1, 0, &t.root);

	cout << t << endl;
	return (0);
}
