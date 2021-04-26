#include <iostream>
#include <vector>
#include <string>

using namespace std;

void
powerset_impl(vector<int> &v, vector<int> subset, int offset,
    vector<vector<int>> &ps)
{
	if (offset == v.size()) {
		ps.push_back(subset);
		return;
	}

	/* Once without the current element. */
	powerset_impl(v, subset, offset + 1, ps);

	/* Once with the current element. */
	subset.push_back(v[offset]);
	powerset_impl(v, subset, offset + 1, ps);
}

vector<vector<int>>
powerset(vector<int> &v)
{
	vector<vector<int>> ps;
	vector<int> subset;

	powerset_impl(v, subset, 0, ps);
	return (ps);
}

int main(int argc, char **argv)
{
	int i;
	vector<vector<int>> ps;
	vector<int> v;

	for (i = 0; i < 4; i++)
		v.push_back(i + 1);

	ps = powerset(v);

	for (i = 0; i < ps.size(); i++) {
		int j;
		for (j = 0; j < ps[i].size(); j++)
			cout << ps[i][j] << " ";
		cout << endl;
	}
	return (0);
}
