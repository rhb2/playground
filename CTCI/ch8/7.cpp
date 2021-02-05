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
	int i;

	permutations_impl(v, 0);
}

int main(int argc, char **argv)
{
	int i;
	int total = atoi(argv[1]);
	vector<int> v;

	for (i = 0; i < total; i++)
		v.push_back(i);

	permutations(v);
	return (0);
}
