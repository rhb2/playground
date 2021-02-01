#include <iostream>
#include <queue>
#include "../util/cpptree.h"

using namespace std;

node<int> *
get_random_node(tree<int> &t, int total)
{
	int i;
	int elem = rand() % (total + 1);
	queue<node<int> *> q;
	node<int> *tmp = NULL;

	q.push(t.root);

	/*
	 * What kind of bad behavior happens if you use > instead of => ?
	 * If the random number selected is 0, this loop will never execute
	 * and you will return `tmp' which was declared on the stack.  Note a
	 * good, positive situation.
	 */
	for (i = 0; i <= elem; i++) {

		tmp = q.front();
		q.pop();

		if (tmp->left != NULL)
			q.push(tmp->left);

		if (tmp->right != NULL)
			q.push(tmp->right);
	}

	return (tmp);
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

	for (i = 0; i < total; i++) {
		pn = get_random_node(t, total);
		cout << "Random node: " << pn->val << endl;
	}

	return (0);
}
