#include <iostream>
#include <list>
#include <iterator>

using namespace std;

void
print_list(list<int> &l)
{
	list<int>::iterator it;

	for (it = l.begin(); it != l.end(); it++)
		cout << *it << " ";

	cout << endl;
}

void
partition(list<int> &l, int val)
{
	list<int>::iterator it;

	for (it = l.begin(); it != l.end(); it++) {
		if (*it < val) {
			l.erase(it);
			l.push_front(*it);
		}
	}
}

int main(int argc, char **argv)
{
	list<int> l;
	int i;
	int len = atoi(argv[1]);
	int part = atoi(argv[2]);

	for (i = 0; i < len; i++)
		l.push_front(rand() % len);

	print_list(l);
	partition(l, part);
	print_list(l);

	return (0);
}
