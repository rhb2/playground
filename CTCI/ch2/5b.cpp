#include <iostream>
#include <cassert>
#include "../util/sll.h"

using namespace std;


linkedlist<int> *
sumlists(linkedlist<int> &l1, linkedlist<int> &l2)
{
	linkedlist<int> *result = new linkedlist<int>;
	int sum;
	int carry = 0;
	node<int> *pn1, *pn2;

	l1.reverse();
	l2.reverse();

	pn1 = l1.head;
	pn2 = l2.head;

	while (pn1 != NULL && pn2 != NULL) {
		int res = pn1->val + pn2->val + carry;
		sum = res % 10;
		carry = res / 10;
		result->push_front(sum);
		pn1 = pn1->next;
		pn2 = pn2->next;
	}

	while (pn1 != NULL) {
		int res = pn1->val + carry;
		sum = res % 10;
		carry = res / 10;
		result->push_front(sum);
		pn1 = pn1->next;
	}

	while (pn2 != NULL) {
		int res = pn2->val + carry;
		sum = res % 10;
		carry = res / 10;
		result->push_front(sum);
		pn2 = pn2->next;
	}

	if (carry > 0)
		result->push_front(carry);

	return (result);
}

int main(int argc, char **argv)
{
	linkedlist<int> ll1, ll2;
	int len1, len2;
	int i;

	assert(argc == 3);

	len1 = atoi(argv[1]);
	len2 = atoi(argv[2]);

	for (i = 0; i < len1 - 1; i++)
		ll1.push_front(rand() % 10);
	/* The most significant digit must be non-zero. */
	ll1.push_front((rand() % 9) + 1);

	for (i = 0; i < len2 - 1; i++)
		ll2.push_front(rand() % 10);
	/* The most significant digit must be non-zero. */
	ll2.push_front((rand() % 9) + 1);

	cout << ll1 << endl;
	cout << ll2 << endl;
	cout << *(sumlists(ll1, ll2)) << endl;

	return (0);
}
