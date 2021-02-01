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
remove_node(list<int> &l, int val)
{
	list<int>::iterator it;

	for (it = l.begin(); it != l.end(); it++)
		if (*it == val)
			break;

	if (next(it, 1) == l.end())
		return;

	*it = *(next(it, 1));
	l.erase(next(it, 1));
}

int main(int argc, char **argv)
{
	int i;
	int len = atoi(argv[1]);
	int k = atoi(argv[2]);
	list<int> l;

	for (i = 0; i < len; i++)
		l.push_front(i);

	print_list(l);
	remove_node(l, 5);
	print_list(l);
	return (0);
}
