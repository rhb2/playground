#include <iostream>
#include <stack>
#include <vector>
#include <cassert>
#include "../util/cpptree.h"

using namespace std;


ostream &
operator <<(ostream &out, const vector<int> &v)
{
	int i;

	for (i = 0; i < v.size(); i++)
		cout << v[i] << " ";

	return (out);
}

vector<vector<int>>
bst_sequences(vector<node<int>> vn)
{
	int i;
	vector<vector<int>> output;

	for (i = 0; i < vn.size(); i++) {
		vector<node<int>> choices = vn;
		node<int> root = choices[i];

		choices.erase(choices.begin() + i);

		if (root.left)
			choices.insert(choices.begin(), *(root.left));

		if (root.right)
			choices.insert(choices.begin(), *(root.right));

		if (choices.size() > 0) {
			int j;
			vector<vector<int>> vv = bst_sequences(choices);

			for (j = 0; j < vv.size(); j++) {
				vv[j].insert(vv[j].begin(), root.val);
				output.push_back(vv[j]);
			}
		} else {
			/*
			 * This is where the recursion bottoms out.  This is
			 * the last element in _this_ particular sequence.  It
			 * will always be one of the leaf nodes in the tree and
			 * we will need to start a new list with this element
			 * being the only one on it.  As the recursion unwinds,
			 * earlier recusrive calls will place their values in
			 * front (i.e. to the left) of this element as you can
			 * see in the stanza above.
			 */
			vector<int> tmp;
			tmp.push_back(root.val);
			output.push_back(tmp);
		}
	}

	return (output);
}

int main(int argc, char **argv)
{
	int i;
	tree<int> t;
	vector<int> a = {4, 2, 1, 3, 5, 6};
	vector<vector<int>> vv;
	vector<node<int>> vn;

	for (i = 0; i < a.size(); i++)
		t.insert(a[i]);

	cout << t << endl;

	vn.push_back(*(t.root));
	vv = bst_sequences(vn);

	for (i = 0; i < vv.size(); i++)
		cout << vv[i] << endl;

	return (0);
}
