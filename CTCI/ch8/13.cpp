#include <iostream>
#include <vector>
#include <map>

using namespace std;

class box {
public:
	box(void) {length = width = height = 0;}
	box(int, int, int);
	~box(void) {}

	friend bool operator<(const box &, const box &);
	friend ostream &operator<<(ostream &, const box &);

	int length;
	int width;
	int height;
};

box::box(int w, int h, int l)
{
	length = l;
	width = w;
	height = h;
}

bool
operator<(const box &lhs, const box &rhs)
{
	return (lhs.length < rhs.length &&
	    lhs.width < rhs.width &&
	    lhs.height < rhs.height);
}

ostream &
operator<<(ostream &out, const box &b)
{
	out << "[" << "w=" << b.width << " h=" << b.height
	    << " l=" << b.length << "]";

	return (out);
}

bool
compare(box &b1, box &b2)
{
	return (b1.height > b2.height);
}

int
stack_boxes(vector<box> &vb, vector<box> &stack, int offset, map<int, int> &m)
{
	int i;
	int without_current;
	int with_current = 0;

	if (offset == vb.size()) {
		for (i = 0; i < stack.size(); i++)
			cout << stack[i];
		cout << endl;
		return (0);
	}

	if (stack.empty() || vb[offset] < stack.back()) {
		if (m.find(offset) == m.end()) {
			stack.push_back(vb[offset]);
			m[offset] = stack_boxes(vb, stack, offset + 1, m);
			m[offset] += vb[offset].height;
			stack.pop_back();
		}
		with_current = m[offset];
	}

	without_current = stack_boxes(vb, stack, offset + 1, m);
	return (max(with_current, without_current));
}

int
stack_boxes(vector<box> &vb)
{
	int i;
	map<int, int> m;
	vector<box> stack;

	std::sort(vb.begin(), vb.end(), compare);
	return (stack_boxes(vb, stack, 0, m));
}

int main(void)
{
	int i;
	vector<box> v = {
	    { 3, 9, 9 },
	    { 1, 4, 10 },
	    { 5, 10, 11 },
	    { 3, 9, 3 },
	    { 1, 5, 3 },
	    { 7, 12, 1 }
	};

	cout << stack_boxes(v) << endl;
	return (0);
}
