/*
 * The CTCI book talks about how you can use a tree to get in done with a
 * run-time complexity of O(log n) for a balanced tree and O(n) for one that
 * is unbalanced, but you really don't need to make it that difficult.  It
 * can be done using a vector and binary search / insert.
 */
#include <iostream>
#include <vector>

using namespace std;


int
binsearch(vector<int> &v, int val)
{
	int i;
	int left = 0;
	int right = v.size() - 1;
	int mid = 0;

	while (left <= right) {
		mid = (left + right) / 2;

		if (val == v[mid])
			break;

		if (val < v[mid])
			right = mid - 1;
		else
			left = mid + 1;
	}

	/* In case there are dupes in the stream. */
	while (v[mid] <= val && mid < v.size())
		mid++;

	return (mid);
}

void
binary_insert(vector<int> &v, int val)
{
	int index;

	if (v.size() == 0) {
		v.push_back(val);
		return;
	}

	index = binsearch(v, val);
	v.insert(v.begin() + index, val);
}

int main(int argc, char **argv)
{
	int i;
	int len = atoi(argv[1]);
	vector<int> v;

	for (i = 0; i < len; i++)
		binary_insert(v, rand() % 30);

	for (i = 0; i < v.size(); i++)
		cout << v[i] << " ";
	cout << endl;

	for (i = 0; i < len * 3; i++) {
		cout << i << " is ranked: " << binsearch(v, i) << endl;
	}

	return (0);
}
