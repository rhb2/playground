#include <iostream>
#include <vector>
#include "../util/cpptree.h"

using namespace std;


void
count_sum_paths_impl(node<int> *pn, vector<int> &v, int target, int depth,
    int &total)
{
	int i;

	if (pn == NULL)
		return;

	if (v.size() == depth)
		v.push_back(0);

	for (i = 0; i <= depth; i++) {
		v[i] += pn->val;
		if (v[i] == target)
			total++;
	}

	count_sum_paths_impl(pn->left, v, target, depth + 1, total);
	count_sum_paths_impl(pn->right, v, target, depth + 1, total);

	for (i = 0; i <= depth; i++)
		v[i] -= pn->val;
}

int
count_sum_paths(tree<int> &t, int target)
{
	int total = 0;
	vector<int> sums;

	count_sum_paths_impl(t.root, sums, target, 0, total);

	return (total);
}

int main(int argc, char **argv)
{
	tree<int> t;
	int i, total;

	total = atoi(argv[1]);

	for (i = 0; i < total; i++)
		t.insert(i);

	cout << t << endl;

	for (i = 0; i < total; i++)
		cout << "Total paths that sum to " << i << ": " <<
		    count_sum_paths(t, i) << endl;

	return (0);
}
