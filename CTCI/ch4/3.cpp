#include <iostream>
#include <list>
#include <vector>
#include <cassert>

#include "../util/cpptree.h"

using namespace std;

void
build_lists(vector<list<int>> &v, node<int> *pn, int depth)
{
	if (pn == NULL)
		return;

	if (depth == v.size()) {
		list<int> l;
		v.push_back(l);
	}

	v[depth].push_back(pn->val);

	build_lists(v, pn->left, depth + 1);
	build_lists(v, pn->right, depth + 1);	
}

int main(int argc, char **argv)
{
	int i, total;
	tree<int> t;
	vector<list<int>> v;

	total = atoi(argv[1]);

	for (i = 0; i < total; i++)
		t.insert(i);

	cout << t << endl;

	build_lists(v, t.root, 0);

	for (i = 0; i < v.size(); i++) {
		list<int>::iterator it;
		list<int> l = v[i];

		for (it = l.begin(); it != l.end(); it++)
			cout << *it << " ";
		cout << endl;
	}

	return (0);
}
