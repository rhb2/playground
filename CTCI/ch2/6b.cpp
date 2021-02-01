#include <iostream>
#include <cassert>
#include "../util/sll.h"

using namespace std;

bool
is_palindrome(linkedlist<int> &l)
{
	linkedlist<int> tmp;
	int elem;
	int len = l.size();
	int i;

	for (i = 0; i < len / 2; i++) {
		tmp.push_front(l.head->val);
		l.pop_front();
	}

	if (len % 2)
		l.pop_front();

	/*
	 * Lists are the same size, so we will reach the end of both at the
	 * same time.
	 */
	while (l.head != NULL) {
		if (l.head->val != tmp.head->val)
			return (false);

		l.pop_front();
		tmp.pop_front();
	}

	return (true);
}

int main(int argc, char **argv)
{
	linkedlist<int> l;
	int i;
	int len;

	assert(argc == 2);

	len = atoi(argv[1]);

	for (i = 0; i < len; i++)
		l.push_back(i);

	l.push_front(9);
	
	for (i = 0; i < len; i++)
		l.push_front(i);

	cout << l;

	if (is_palindrome(l))
		cout << " is a palindrom." << endl;
	else
		cout << " is not a palindrome." << endl;

	return (0);
}
