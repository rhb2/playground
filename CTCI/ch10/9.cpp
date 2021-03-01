#include <iostream>
#include <vector>
#include <cassert>

using namespace std;


ostream &
operator<<(ostream &out, vector<vector<int>> &v)
{
	int i, j;

	for (i = 0; i < v.size(); i++) {
		for (j = 0; j < v[i].size(); j++)
			out << v[i][j] << (v[i][j] < 10 ? "  ": " ");

		out << endl;
	}

	return (out);
}

pair<int, int>
get_mid(pair<int, int> tl, pair<int, int> br)
{
	pair<int, int> result;

	result.first = (tl.first + br.first) / 2;
	result.second = (tl.second + br.second) / 2;
	return (result);
}

bool
search_impl(vector<vector<int>> &vv, pair<int, int> tl, pair<int, int> br,
    int val)
{
	int cur;
	pair<int, int> mid = get_mid(tl, br);
	bool ret = false;

	cur = vv[mid.first][mid.second];

	if (cur == val)
		return (true);

	if (mid == tl || mid == br)
		return (false);

	/*
	 * If our midway point is greater than the value that we are
	 * searching for, then it could be in quadrants 1, 2, or 3.
	 */
	if (val < cur) {
		/* Search the first (top-right) quadrant. */
		if (search_impl(vv, pair<int, int>(mid.first, tl.second),
		    pair<int, int>(br.first, mid.second), val))
			return (true);

		/* Search the second (top-left) quadrant. */
		if (search_impl(vv, tl, mid, val))
			return (true);

		/* Search the third (bottom-left) quadrant. */
		return (search_impl(vv, pair<int, int>(tl.first, mid.second),
		    pair<int, int>(mid.first, br.second), val));
	}

	/*
	 * If we're here, then the midway point is less than the value that
	 * we're searching for which means it could be in quadrants 1, 3, or 4.
	 */

	/* Search the first (top-right) quadrant. */
	if (search_impl(vv, pair<int, int>(mid.first, tl.second),
	    pair<int, int>(br.first, mid.second), val))
		return (true);

	/* Search the third (bottom-left) quadrant. */
	if (search_impl(vv, pair<int, int>(tl.first, mid.second),
	    pair<int, int>(mid.first, br.second), val))
		return (true);

	/* Search the fourth (bottom-right) quadrant. */
	return (search_impl(vv, mid, br, val));
}

bool
search(vector<vector<int>> &vv, int val)
{
	pair<int, int> tl(0, 0);
	pair<int, int> br(vv.size(), vv[0].size());

	return (search_impl(vv, tl, br, val));
}

int main(int argc, char **argv)
{
	int i, j;
	int length, width;
	vector<vector<int>> vv;

	assert(argc == 3);

	length = atoi(argv[1]);
	width = atoi(argv[2]);

	for (i = 0; i < width; i++) {
		vector<int> v;
		for (j = 0; j < length; j++) {
			v.push_back(5 * (i + j));
		}
		vv.push_back(v);
	}

	cout << vv << endl << endl;

	for (i = 0; i < 50; i++) {
		cout << i << " was ";
		if (search(vv, i))
			cout << "found." << endl;
		else
			cout << "not found." << endl;
	}

	return (0);
}
