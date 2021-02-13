/*
 * Program to find the longest palindrome in a (possibly) massive array.  The
 * approach to solving problems like this (and ones like longest sub array with
 * a given sum), can be implemented largely using the same method.  With
 * problems like this, there is usually at least three nested loops where the
 * really interesting logic takes place in the inner-most loop.  At least for
 * me, this heuristic gets really hard to understand, so I have broken up the
 * process into three distinct loops.  Starting from the inner loop and working
 * my way out, their respective purposes are:
 *
 * 1. Given an array, and a left and right index only, perform whatever the
 *    magical evalaution is on the elements within that range (e.g. test for
 *    palindrome, or whether the sum is some value.
 *
 * 2. For a given length, call the function specified in 1, but call it for all
 *    possible offsets within the array.  For example, if the desired length is
 *    three, this loop, will perform function (1) on a sliding window of three
 *    elements, starting from the beginning of the array and working its way
 *    to the end of it: 0..2, 1..3, 2..4, 3..5.
 *
 * 3. Call function described in (2) for all possible lengths, starting with
 *    a length of 1 and working our way up to a subarray that is equal in size
 *    to the entire array itself.
 *
 * Memoization of results should take place in (1), so make sure to include the
 * plumbing needed to pass a 2D table from the function in (3) all the way down
 * to the function in (1) since that's where the magic happens.
 *
 * Summary:
 * When tackling these kinds of problems, I have found that it is easier to
 * frame mentally when you first think about what needs to happen for a single
 * iteration between a left and right index.  From there, you can slide the
 * left/right index forward unti the window reaches the other side of the array.
 * After that, it's just a matter of varying the size of the window, starting
 * with a size of one and increasing it from there.
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

void
process_range(vector<int> &v, int left, int right, vector<vector<bool>> &map,
    pair<int, int> &p)
{
	int i;
	int longest = p.second - p.first;

	for (i = left; i <= right; i++) {
		bool result = (v[left] == v[right] && map[left + 1][right - 1]);
		map[left][right] = result;

		if (result  && right - left >= longest) {
			p.first = left;
			p.second = right;
		}
	}
}

void
process_ranges(vector<int> &v, int len, vector<vector<bool>> &map,
    pair<int, int> &p)
{
	int l, r;

	for (l = 0, r = len - 1; r < v.size(); l++, r++)
		process_range(v, l, r, map, p);
}

void
process_all_ranges(vector<int> &v)
{
	int len;
	int i;
	pair<int, int> p(0, 0);

	vector<vector<bool>> map;

	for (i = 0; i < v.size(); i++) {
		vector<bool> tmp(v.size());
		map.push_back(tmp);
	}

	for (i = 0; i < v.size(); i++)
		map[i][i] = true;

	for (i = 0; i < v.size() - 1; i++)
		map[i][i + 1] = (v[i] == v[i + 1]);

	for (len = 3; len <= v.size(); len++)
		process_ranges(v, len, map, p);

	cout << "Longest range: (" << p.first << ", " << p.second << ")"
	    << endl;
}

int main(int argc, char **argv)
{
	int i;
	int len = atoi(argv[1]);
	vector<int> v;
	vector<int> v2;

	for (i = 0; i < len; i++)
		v.push_back(rand() % 10);

	for (i = 0; i < 5; i++) {
		v2.insert(v2.begin(), i);
		v2.push_back(i);
	}

	v.insert(v.begin() + v.size() / 2, v2.begin(), v2.end());
	cout << v << endl;
	process_all_ranges(v);

	return (0);
}
