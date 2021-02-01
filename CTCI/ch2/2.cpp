#include <iostream>
#include <list>
#include <iterator>
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

int main(int argc, char **argv)
{
	list<int> l;
	list<int>::iterator i1;
	list<int>::iterator i2;
	int length = atoi(argv[1]);
	int k = atoi(argv[2]);
	int i;

	for (i = 0; i < length; i++)
		l.push_front(i);

	print_list(l);

	i2 = next(l.begin(), k);

	for (i1 = l.begin(); i2 != l.end(); i1++, i2++);

	cout << *i1 << endl;
	return (0);	
}
