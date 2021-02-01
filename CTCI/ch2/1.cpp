#include <iostream>
#include <list>
#include <iterator>
#include <map>
#include <cassert>

using namespace std;

void
print_list(list<int> &l)
{
	list<int>::iterator it;

	for (it = l.begin(); it != l.end(); it++)
		cout << *it << " ";

	cout << endl;
}

/*
 * Additional storage is used, but the dups are removed in O(n) time.
 */
void
remove_dups(list<int> &l)
{
	map<int, bool> m;
	list<int>::iterator it;

	for (it = l.begin(); it != l.end(); it++) {
		if (m.find(*it) != m.end())
			l.erase(it);
		else
			m[*it] = true;
	}
}

/*
 * Without any additional storage, the list has to be sorted first.  The cost
 * of the sort is O(n log n), plus another O(n) to remove the dupes.
 */
void
remove_dups2(list<int> &l)
{
	list<int>::iterator it;

	l.sort();

	for (it = l.begin(); it != l.end(); it++) {
		if (*it == *(next(it, 1)))
			l.erase(it);
	}
}

int main(int argc, char **argv)
{
	int i;
	int len = atoi(argv[1]);
	list<int> l;

	for (i = 0; i < len; i++)
		l.push_front(rand() % len);

	print_list(l);
	remove_dups2(l);
	print_list(l);
	return (0);
}
