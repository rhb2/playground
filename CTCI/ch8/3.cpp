#include <iostream>
#include <vector>

using namespace std;

int
magic_index(vector<int> &v, int left, int right)
{
	int index;

	if (left > right)
		return (-1);

	index = (left + right) / 2;

	if (index == v[index])
		return (index);

	/*
	 * Example:
	 * index = 2 and v[index] = 3.  In a case like that, we know that we
	 * have to go left.  A case that would justify searching right instead
	 * would be if index = 3, but v[index]  = 2.  If we search to the right,
	 * there is still a chance that we could find a situation where
	 * index = 4 and v[index] is also equal to 4.
	 */
	if (index < v[index])
		return (magic_index(v, left, index - 1));
	else
		return (magic_index(v, index + 1, right));
}

int
magic_index_nunique(vector<int> &v, int left, int right)
{
	int index;
	int val;
	int l, r;

	if (left > right)
		return (-1);

	index = (left + right) / 2;
	val = v[index];

	if (index == v[index])
		return (index);

	if ((l = magic_index_nunique(v, left, min(val, index - 1))) != -1)
		return (l);

	if ((r = magic_index_nunique(v, index + 1, max(val, right))) != -1)
		return (r);

	return (-1);
}

int main(void)
{
	vector<int> v1 = {-1, 0, 2, 4, 5, 6, 7, 8};
	vector<int> v2 = {-1, 0, 1, 3, 5, 6, 7, 8};
	vector<int> v3 = {-1, 0, 1, 1, 3, 5, 7, 100};

	cout << magic_index(v1, 0, v1.size() - 1) << endl;
	cout << magic_index(v2, 0, v2.size() - 1) << endl;
	cout << magic_index_nunique(v3, 0, v3.size() - 1) << endl;
	return (0);
}
