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

list<int>
add_lists(list<int> l1, list<int>l2)
{
	list<int>::iterator i1, i2;
	list<int> sum;
	int carry = 0;
	int result;

	l1.reverse();
	l2.reverse();

	i1 = l1.begin();
	i2 = l2.begin();

	while (i1 != l1.end() && i2 != l2.end()) {
		result = *i1 + *i2 + carry;
		sum.push_front(result % 10);
		carry = result / 10;
		i1++;
		i2++;
	}

	while (i1 != l1.end()) {
		result = *i1 + carry;
		sum.push_front(result % 10);
		carry = result / 10;
		i1++;
	}

	while (i2 != l2.end()) {
		result = *i2 + carry;
		sum.push_front(result % 10);
		carry = result / 10;
		i2++;
	}

	if (carry > 0)
		sum.push_front(carry);

	return (sum);
}

int main(int argc, char **argv)
{
	list<int> l1, l2, sum;
	int i;
	int len1 = atoi(argv[1]);
	int len2 = atoi(argv[2]);

	for (i = 0; i < len1 - 1; i++)
		l1.push_front(rand() % 10);

	l1.push_front((rand() % 9) + 1);

	for (i = 0; i < len2 - 1; i++)
		l2.push_front(rand() % 10);

	l2.push_front((rand() % 9) + 1);

	print_list(l1);
	print_list(l2);

	sum = add_lists(l1, l2);
	print_list(sum);

	return (0);
}
