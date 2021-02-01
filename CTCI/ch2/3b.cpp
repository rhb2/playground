#include <iostream>
#include <cassert>
#include "../util/sll.h"

using namespace std;


void
remove(linkedlist<int> &l, node<int> *pn)
{
	int val;
	node<int> *next;

	/* Not allowed to do the head or tail. */
	assert(l.head != pn && pn->next != NULL);

	next = pn->next;

	pn->val = next->val;
	pn->next = next->next;

	delete next;
}

int main(int argc, char **argv)
{
	linkedlist<int> l;
	node<int> *pn;
	int i;
	int len;
	int idx;

	assert(argc == 3);

	len = atoi(argv[1]);
	idx = atoi(argv[2]);

	for (i = 0; i < len; i++)
		l.push_back(i);

	cout << l << endl;

	for (i = 0; i < len - 2; i++) {
		pn = l.get_at(1);
		remove(l, pn);
		cout << l << endl;
	}

	return (0);
}
