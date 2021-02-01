#include <iostream>
#include <string>
#include <cassert>
#include "../util/cpplist.h"

using namespace std;


/*
 * Pretend that the list is singly linked (that is, you can not use the prev
 * pointers in any node.  We are given access to the node that we want to
 * remove, but not the node before it.  The way around that issue is to copy
 * the contents of the next node in to the current one and then remove the
 * next one.  Note, this is only intended to be used on nodes in the middle of
 * a linked list (i.e. not the head or tail).
 */
template <class T>
void
list_remove(linkedlist<T> &l, node<T> *pn)
{
	node<T> *next;

	if (pn == l.get_head() || pn == l.get_tail())
		return;

	next = pn->next;
	pn->val = next->val;
	pn->next = next->next;
	delete next;

	if (next == l.get_tail())
		l.set_tail(pn);

	l.set_size(l.size() - 1);
}

int main(int argc, char **argv)
{
	int i;
	linkedlist<int> list1;
	node<int> *pn;

	for (i = 0; i < 10; i++)
		//list1.push_front(i);
		//list1.push_back(i);
		list1.single_ordered_insert(rand() % 20);

	cout << list1 << endl;

	pn = list1.get_at(5);

	list_remove(list1, pn);
	list_remove(list1, list1.get_at(5));
	cout << list1 << endl;

	return (0);
}
