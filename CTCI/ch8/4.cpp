#include <iostream>
#include <vector>

using namespace std;

ostream &
operator<<(ostream &out, const vector<int> &v)
{
	int i;

	for (i = 0; i < v.size(); i++)
		cout << v[i] << " ";

	return (out);
}

void
ncr_impl(vector<int> &v, vector<int> &result, int offset, int r)
{
	int i;

	if (result.size() == r) {
		cout << result << endl;
		return;
	}

	for (i = offset; i < v.size(); i++) {
		result.push_back(v[i]);
		ncr_impl(v, result, i + 1, r);
		result.pop_back();
	}
}

void
ncr(vector<int> &v, int r)
{
	vector<int> result;

	ncr_impl(v, result, 0, r);
}

void
powerset(vector<int> &v)
{
	int i;

	for (i = 1; i <= v.size(); i++)
		ncr(v, i);

}

int main(int argc, char **argv)
{
	int i;
	vector<int> v;

	for (i = 0; i < 5; i++)
		v.push_back(i);

	return (0);
}
