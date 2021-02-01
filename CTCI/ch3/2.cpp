#include <iostream>
#include "../util/stack.h"

using namespace std;


void
push(int val, stack<int> &mystack, stack<pair<int, int> > &m)
{
	pair<int, int> p(val, 1);

	mystack.push(val);

	if (m.size() == 0 || val < m.top().first) {
		m.push(p);
		return;
	}

	if (val == m.top().first) {
		m.data.back().second++;
		return;
	}
}

void
pop(stack<int> &mystack, stack<pair<int, int> > &m)
{
	int val;
	pair<int, int> p;

	if (mystack.size() == 0)
		return;

	val = mystack.top();
	p = m.top();
	mystack.pop();

	if (val > p.first)
		return;

	if (val == p.first && --m.data.back().second == 0)
		m.pop();
}

int
min(stack<int> &mystack, stack<pair<int, int> > &m)
{
	if (m.size() == 0)
		return (0);

	return (m.top().first);
}

void
print_min(stack<pair<int, int> > &m)
{
	int i;

	for (i = 0; i < m.data.size(); i++) {
		cout << m.data.at(i).first << ", "
		    << m.data.at(i).second << endl;
	}
}

int main(int argc, char **argv)
{
	int i;
	int total = atoi(argv[1]);
	stack<int> mystack;
	stack<pair<int, int> > m;

	for (i = 0; i < total; i++)
		push(rand() % 10, mystack, m);

	cout << mystack << endl;
	print_min(m);

	while (mystack.size() > 1) {
		pop(mystack, m);
		cout << mystack << endl;
		cout << "Smallest elem: " << min(mystack, m) << endl;
	}

	return (0);
}
