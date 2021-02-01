#include <iostream>
#include <stack>
#include <cassert>
#include "../util/cpptree.h"

using namespace std;


void
swap(vector<int> &v, int x, int y)
{
	v[x] = (v[x] + v[y]) - (v[y] = v[x]);
}

ostream &
operator <<(ostream &out, const vector<int> &v)
{
	int i;

	for (i = 0; i < v.size(); i++)
		cout << v[i] << " ";

	return (out);
}

void
permute(vector<vector<int>> &v, int curvec, int offset)
{
	int i;

	if (offset == v[curvec].size()) {
		if (curvec == v.size() - 1) {
			for (i = 0; i < v.size(); i++)
				cout << v[i];
			cout << endl;
			return;
		}

		permute(v, curvec + 1, 0);
		return;
	}

	for (i = offset; i < v[curvec].size(); i++) {
		swap(v[curvec], offset, i);
		permute(v, curvec, offset + 1);
		swap(v[curvec], offset, i);
	}
}

/*
 * Scour the tree and build out a vector of vectors, representing each row
 * in the tree.
 */
void
get_rows(node<int> *pn, vector<vector<int>> &v, int depth)
{
	vector<int> nv;

	if (pn == NULL)
		return;

	if (v.size() == depth)
		v.push_back(nv);

	v[depth].push_back(pn->val);
	get_rows(pn->left, v, depth + 1);
	get_rows(pn->right, v, depth + 1);
}

int main(int argc, char **argv)
{
	int i, total;
	tree<int> t;
	vector<vector<int>> v;

	total = atoi(argv[1]);

	for (i = 0; i < total; i++)
		t.insert(i);

	cout << t << endl;

	get_rows(t.root, v, 0);
	permute(v, 0, 0);

	return (0);
}
