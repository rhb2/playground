#include <iostream>
#include <cassert>
#include "../util/sll.h"

using namespace std;

node<int> *
intersection(linkedlist<int> &l1, linkedlist<int> &l2)
{
	int len1 = l1.size();
	int len2 = l2.size();
	node<int> *s, *l;
	int delta, i;

	if (len1 < len2) {
		s = l1.head;
		l = l2.head;
	} else {
		s = l2.head;
		l = l1.head;
	}

	delta = abs(len1 - len2);
	for (i = 0; i < delta; i++, l = l->next);

	for (; s != NULL && l != NULL; s = s->next, l = l->next) {
		if (s == l)
			return (s);
	}

	return (NULL);
}

int main(int argc, char **argv)
{
	linkedlist<int> ll1, ll2, ll3;
	node<int> *tail1, *tail2;
	int len1, len2, len3;
	node<int> *inode;
	int i;

	assert(argc == 4);

	len1 = atoi(argv[1]);
	len2 = atoi(argv[2]);
	len3 = atoi(argv[3]);

	for (i = 0; i < len1; i++)
		ll1.push_front(rand() % 10);

	for (i = 0; i < len2; i++)
		ll2.push_front(rand() % 10);

	for (i = 0; i < len3; i++)
		ll3.push_front(rand() % 10);

	tail1 = ll1.get_tail();
	tail1->next = ll3.head;

	tail2 = ll2.get_tail();
	tail2->next = ll3.head;

	cout << ll1 << endl;
	cout << ll2 << endl;
	cout << ll3 << endl;

	if ((inode = intersection(ll1, ll2)) != NULL) {
		cout << "The lists intersect at " << inode->val << endl;
	} else {
		cout << "The lists do not intersect. " << endl;
	}

	tail1->next = NULL;
	tail2->next = NULL;

	return (0);
}
