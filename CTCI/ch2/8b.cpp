#include <iostream>
#include <cassert>
#include "../util/sll.h"

using namespace std;

node<int> *
find_loop(linkedlist<int> &ll)
{
	node<int> *pn1, *pn2;

	for (pn1 = pn2 = ll.head; pn1->next != pn2->next->next;
	    pn1 = pn1->next, pn2 = pn2->next->next);

	pn1 = pn1->next;
	pn2 = ll.head;

	for (; pn1 != pn2; pn1 = pn1->next, pn2 = pn2->next);
	return (pn1);
}

int main(int argc, char **argv)
{
	linkedlist<int> l;
	node<int> *tail, *pn, *loop;
	int i, len;

	assert(argc == 2);

	len = atoi(argv[1]);

	for (i = 0; i < len; i++)
		l.push_back(i);

	cout << l << endl;

	pn = l.get_at(len / 2);
	cout << *pn << endl;
	tail = l.get_tail();

	tail->next = pn;
	loop = find_loop(l);
	cout << *loop << endl;
	tail->next = NULL;

	return (0);
}
