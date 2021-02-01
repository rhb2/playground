#include <iostream>
#include <stack>

using namespace std;

void
spill(stack<int> &src, stack<int> &dst, int total, int *largest)
{
	int i;
	int l;

	l = src.top();
	src.pop();

	assert(largest != NULL);

	for (i = 1; i < total; i++) {
		int tmp = src.top();
		src.pop();
		if (tmp > l) {
			dst.push(l);
			l = tmp;
		} else {
			dst.push(tmp);
		}
	}

	*largest = l;
}

void
sort_stack(stack<int> &s)
{
	int largest;
	int total = s.size();
	stack<int> tmp;

	while (total > 0) {
		spill(s, tmp, total, &largest);
		s.push(largest);
		while (!tmp.empty()) {
			s.push(tmp.top());
			tmp.pop();
		}
		total--;
	}
}

int main(int argc, char **argv)
{
	int i;
	int total = atoi(argv[1]);
	stack<int> s;

	for (i = 0; i < total; i++) {
		int val = rand() % total * 3;
		s.push(val);
		cout << val << endl;
	}

	sort_stack(s);

	while (!s.empty()) {
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;
	return (0);
}
