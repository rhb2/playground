#include <iostream>
#include <vector>

using namespace std;

ostream &
operator<<(ostream &out, const vector<int> &v)
{
	int i;

	for (i = 0; i < v.size(); i++)
		out << v[i] << " ";

	return (out);
}

void
ncr_impl(vector<int> &v, vector<int> &tmp, int offset, int r)
{
	if (offset >= v.size()) {
		if (tmp.size() == r)
			cout << tmp << endl;
		return;
	}

	tmp.push_back(v[offset]);
	ncr_impl(v, tmp, offset + 1, r);
	tmp.pop_back();

	ncr_impl(v, tmp, offset + 1, r);
}

void
ncr(vector<int> &v, int r)
{
	vector<int> tmp;

	ncr_impl(v, tmp, 0, r);
}

void
swap(vector<int> &v, int x, int y)
{
	int tmp = v[x];
	v[x] = v[y];
	v[y] = tmp;
}

void
permutations(vector<int> &v, int offset)
{
	int i;

	if (offset >= v.size()) {
		cout << v << endl;
		return;
	}

	for (i = offset; i < v.size(); i++) {
		swap(v, offset, i);
		permutations(v, offset + 1);
		swap(v, offset, i);
	}
}

int main(int argc, char **argv)
{
	int i;
	int total = atoi(argv[1]);
	vector<int> v;

	for (i = 0; i < total; i++)
		v.push_back(i);

//	ncr(v, 3);
	permutations(v, 0);
}
