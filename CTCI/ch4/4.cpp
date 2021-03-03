/*
 * This uses a recursive technique to check the balance at every subtree in the
 * tree.  It works, but another interesting idea might be to get the total
 * number of nodes at each level and if that number isn't a power of two,
 * disqualify it (unless it's the last level).
 */
#include <iostream>
#include <list>
#include <vector>
#include <queue>
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
is_balanced1(node<int> *pn)
{
	bool left, right;

	if (pn == NULL)
		return (true);

	left = is_balanced1(pn->left);
	right = is_balanced1(pn->right);

	if (!left || !right)
		return (false);

	return (abs(get_height(pn->left) - get_height(pn->right)) < 2);
}

/*
 * This is straight fire.  Not only is it iterative, but its worst case
 * complexity is O(n).  It will detect an imbalance at the first possible
 * sign of one and flag failure.  So, in the case where the tree is not
 * balanced, we won't even need to visit every single node in the tree to
 * figure it out.
 */
bool
is_balanced2(node<int> *pn)
{
	pair<node<int> *, int> p;
	queue<pair<node<int> *, int>> q;
	int cur_depth = 0;
	vector<int> counts;

	if (pn == NULL)
		return (true);

	p.first = pn;
	p.second = 0;
	q.push(p);
	counts.push_back(0);

	while (!q.empty()) {
		p = q.front();
		q.pop();

		/*
		 * We need to do two things.  Bump our current level as well
		 * as check how many nodes we saw in the previous level.  If
		 * if was not 2^previous_level, then there is an imbalance.
		 */
		if (p.second > cur_depth) {
			if (cur_depth >= 1 &&
			    counts[cur_depth - 1] != pow(2, cur_depth - 1))
				return (false);

			counts.push_back(1);
			cur_depth++;
		} else {
			counts[cur_depth]++;
		}

		if (p.first->left != NULL)
			q.push(pair<node<int> *, int>(p.first->left,
			    cur_depth + 1));

		if (p.first->right != NULL)
			q.push(pair<node<int> *, int>(p.first->right,
			    cur_depth + 1));
	}

	return (true);
}

int main(int argc, char **argv)
{
	int i, total;
	tree<int> t, t2;
	node<int> pn(1);

	total = atoi(argv[1]);

	for (i = 0; i < total; i++)
		t.insert(i);

	cout << t;

	if (is_balanced2(t.root))
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

	if (is_balanced2(&pn))
		cout << "Tree is balanced." << endl;
	else
		cout << "Tree is not balanced." << endl;

	t2.root = NULL;

	return (0);
}
