#include <iostream>
#include <vector>

using namespace std;

template <class T>
ostream &
operator<<(ostream &out, const vector<T> &v)
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
permutations(vector<int> &v, int offset)
{
	int i;

	if (offset == v.size()) {
		cout << v << endl;
		return;
	}

	for (i = offset; i < v.size(); i++) {
		swap(v, i, offset);
		permutations(v, offset + 1);
		swap(v, i, offset);
	}
}

void
ncr_impl(vector<int> &v, vector<int> &result, int r, int offset)
{
	int i;

	if (result.size() == r) {
		cout << result << endl;
		return;
	}

	for (i = offset; i < v.size(); i++) {
		result.push_back(v[i]);
		ncr_impl(v, result, r, i + 1);
		result.pop_back();
	}
}

void
ncr(vector<int> &v, int r)
{
	vector<int> result;

	ncr_impl(v, result, r, 0);
}

void
get_next(vector<int> &v, vector<vector<int>> &ps, int iteration)
{
	int i;
	vector<vector<int>> tmp = ps;

	for (i = 0; i < tmp.size(); i++)
		tmp[i].push_back(v[iteration]);

	ps.insert(ps.end(), tmp.begin(), tmp.end());
}

void
powerset(vector<int> &v)
{
	int i;
	vector<vector<int>> result = {{}};

	for (i = 0; i < v.size(); i++)
		get_next(v, result, i);

	for (i = 0; i < result.size(); i++)
		cout << result[i] << endl;
}

int main(int argc, char **argv)
{
	vector<int> v = {1, 2, 3, 4};

	//permutations(v, 0);
	//ncr(v, 3);
	powerset(v);

	return (0);
}
