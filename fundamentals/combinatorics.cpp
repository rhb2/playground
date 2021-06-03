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
swap(vector<int> &v, int x, int y)
{
	v[x] = (v[x] + v[y]) - (v[y] = v[x]);
}

void
permutations_impl(vector<int> &v, int offset)
{
	int i;

	if (offset == v.size()) {
		cout << v << endl;
		return;
	}

	for (i = offset; i < v.size(); i++) {
		swap(v, offset, i);
		permutations_impl(v, offset + 1);
		swap(v, offset, i);
	}
}

void
permutations(vector<int> &v)
{
	permutations_impl(v, 0);
}

void
ncr_impl(vector<int> &v, vector<int> &tmp, int offset, int r)
{
	int i;

	if (tmp.size() == r) {
		cout << tmp << endl;
		return;
	}

	for (i = offset; i < v.size(); i++) {
		tmp.push_back(v[i]);
		ncr_impl(v, tmp, i + 1, r);
		tmp.pop_back();
	}
}

void
ncr(vector<int> &v, int r)
{
	vector<int> tmp;

	ncr_impl(v, tmp, 0, r);
}

void
powerset_impl(vector<int> &v, vector<int> &tmp, int offset)
{
	int i;

	if (offset == v.size()) {
		cout << tmp << endl;
		return;
	}

	/* Make one recursive call without the current element. */
	powerset_impl(v, tmp, offset + 1);

	/* Make another one _with_ the current element. */
	tmp.push_back(v[offset]);
	powerset_impl(v, tmp, offset + 1);
	tmp.pop_back();
}

void
powerset(vector<int> &v)
{
	vector<int> tmp;

	powerset_impl(v, tmp, 0);
}

void
test_impl(vector<int> &v, vector<int> &tmp, int offset, int r)
{
	if (offset == v.size()) {
		if (tmp.size() == r)
			cout << tmp << endl;
		return;
	}

	test_impl(v, tmp, offset + 1, r);

	tmp.push_back(v[offset]);
	test_impl(v, tmp, offset + 1, r);
	tmp.pop_back();
}

void
test(vector<int> &v, int r)
{
	vector<int> tmp;

	test_impl(v, tmp, 0, r);
}

int main(int argc, char **argv)
{
	int len = atoi(argv[1]);
	int i;
	vector<int> v;

	for (i = 0; i < len; i++)
		v.push_back(i);

//	permutations(v);
	ncr(v, 3);

	cout << endl << endl;
//	powerset(v);
	test(v, 3);

	return (0);
}
