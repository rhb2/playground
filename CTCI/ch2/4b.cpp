#include <iostream>
#include <cassert>
#include "../util/sll.h"

using namespace std;

void
partition(linkedlist<int> &l, int val)
{
	linkedlist<int> tmp;
	int elem;
	int i;
	int len = l.size();

	for (i = 0; i < len; i++) {
		elem = l.head->val;
		l.pop_front();

		if (elem < val)
			tmp.push_front(elem);
		else
			tmp.push_back(elem);
	}

	l.head = tmp.head;
	tmp.head = NULL;
}

int main(int argc, char **argv)
{
	linkedlist<int> l;
	node<int> *pn;
	int i;
	int len;
	int val;

	assert(argc == 3);

	len = atoi(argv[1]);
	val = atoi(argv[2]);

	for (i = 0; i < len; i++)
		l.push_back(i);

	cout << l << endl;
	partition(l, val);
	cout << l << endl;
	l.reverse();
	cout << l << endl;

	return (0);
}
