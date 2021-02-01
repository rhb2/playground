#include <iostream>
#include <list>
#include <iterator>
#include <map>
#include <cassert>
#include "../util/sll.h"

using namespace std;


/*
 * Ordered insert in to singly linked list with an added optimization of
 * short circuiting if a duplicate value is detected upon insert.
 */
void
unique_ordered_insert(linkedlist<int> &ll, int elem)
{
	node<int> *cur;
	node<int> *tmp = new node<int>(elem);

	assert(tmp != NULL);

	if ((cur = ll.head) == NULL || tmp->val <= cur->val) {
		if (cur && tmp->val == cur->val)
			return;

		tmp->next = cur;
		ll.head = tmp;
		return;
	}

	for (; cur->next != NULL && cur->next->val < tmp->val; cur = cur->next);

	if (cur->next && tmp->val == cur->next->val)
		return;

	tmp->next = cur->next;
	cur->next = tmp;
}

void
remove_dups(linkedlist<int> &ll)
{
	linkedlist<int> tmp;

	while (ll.head != NULL) {
		int elem = ll.head->val;
		ll.pop_front();
		unique_ordered_insert(tmp, elem);
	}

	ll.head = tmp.head;
	tmp.head = NULL;
}

int main(int argc, char **argv)
{
	int i;
	int len = atoi(argv[1]);
	linkedlist<int> ll;	/* Home grown list */

	for (i = 0; i < len; i++) {
		int elem = rand() % len;
		ll.push_front(elem);
	}

	remove_dups(ll);
	cout << ll << endl;

	return (0);
}
