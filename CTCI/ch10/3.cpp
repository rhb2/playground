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

int
find_rotation_point(vector<int> &v)
{
	int start = 0;
	int end = v.size() - 1;
	int last = v[end];
	int mid;

	while (start <= end) {
		mid = (start + end) / 2;
		if (v[mid] > last) {
			start = mid + 1;
		} else if (v[mid] < last) {
			end = mid - 1;
		} else {
			break;
		}
	}

	/*
	 * Depending on the contents of the array, the above algorithm could
	 * give us the end of the left side, or the start of the right side.
	 * It doesn't really matter which one it retuns, but we want it to be
	 * consistent.  For this particualr implementation, the intention is to
	 * always return the beginning of the right side.  The stanza below is
	 * intended to ensure that.
	 */
	if (v[mid] > v[mid + 1])
		mid++;

	return (mid);
}

bool
find_element(vector<int> &v, int val, int &index)
{
	int low, mid, high;
	int r_begin;

	r_begin = find_rotation_point(v);

	if (val >= v[r_begin] && val <= v[v.size() - 1]) {
		low = r_begin;
		high = v.size() - 1;
	} else {
		low = 0;
		high = r_begin - 1;
	}

	while (low <= high) {
		mid = (low + high) / 2;
		if (val < v[mid])
			high = mid - 1;
		else if (val > v[mid])
			low = mid + 1;
		else {
			index = mid;
			return (true);
		}
	}

	return (false);
}

int main(int argc, char **argv)
{
	int i;
	int j;
	int len = atoi(argv[1]);
	vector<int> v;

	for (i = 0; i < len; i++) {
		v.push_back(i);
		v.push_back(i);
	}

	/*
	 * Rotate the array and test to find each element after each rotation
	 * of one.  There should be nothing that we can't find.
	 */
	for (i = 0; i < v.size(); i++) {
		std::rotate(v.begin(), v.begin() + i, v.end());
		cout << v << endl;
		for (j = 0; j < v.size(); j++) {
			int index;
			if (find_element(v, j, index)) {
				cout << "Found " << j << " at offset " << index
				    << endl;
			} else {
				cout << "Unable to find " << j << endl;
			}
		}
	}

	return (0);
}
