#include <iostream>
#include <cassert>
#include "../util/sll.h"

using namespace std;

int main(int argc, char **argv)
{
	linkedlist<int> l;
	node<int> *i1;
	node<int> *i2;
	int len;
	int k;
	int i;

	assert(argc == 3);

	len = atoi(argv[1]);
	k = atoi(argv[2]);

	for (i = 0; i < len; i++)
		l.push_front(rand() % (len * 3));

	cout << l << endl;

	i1 = l.head;

	for (i = 0; i < k; i++, i1 = i1->next);

	i2 = l.head;

	while (i1 != NULL) {
		i1 = i1->next;
		i2 = i2->next;
	}

	cout << *i2 << endl;
	return (0);
}
