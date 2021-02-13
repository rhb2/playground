/*
 * Program to find the longest contiguous sequence of numbers in an array
 * whose sum is below some caller-specified threshold.
 */
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

ostream &
operator<<(ostream &out, const vector<vector<int>> &v)
{
	int i;

	for (i = 0; i < v.size(); i++)
		out << v[i] << endl;

	return (out);
}

void
process_range(vector<int> &v, int left, int right, vector<vector<int>> &map,
    pair<int, int> &p, int val)
{
	int i;
	int longest = p.second - p.first;

	for (i = left; i <= right; i++) {
		int result = v[right] + map[left][right - 1];
		map[left][right] = result;

		if (result <= val && right - left >= longest) {
			p.first = left;
			p.second = right;
		}
	}
}

void
process_ranges(vector<int> &v, int len, vector<vector<int>> &map,
    pair<int, int> &p, int val)
{
	int l, r;

	for (l = 0, r = len - 1; r < v.size(); l++, r++)
		process_range(v, l, r, map, p, val);
}

void
process_all_ranges(vector<int> &v, int val)
{
	int len;
	int i;
	pair<int, int> p(0, 0);

	vector<vector<int>> map;

	for (i = 0; i < v.size(); i++) {
		vector<int> tmp(v.size());
		map.push_back(tmp);
	}

	for (i = 0; i < v.size(); i++)
		map[i][i] = v[i];

	for (len = 2; len <= v.size(); len++)
		process_ranges(v, len, map, p, val);

	cout << "Longest range: (" << p.first << ", " << p.second << ")"
	    << endl;
}

int main(int argc, char **argv)
{
	int i;
	int len = atoi(argv[1]);
	vector<int> v;

	for (i = 0; i < len; i++)
		v.push_back(rand() % 10);

	cout << v << endl;
	process_all_ranges(v, 30);

	return (0);
}
