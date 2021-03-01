#include <iostream>
#include <vector>
#include <cassert>

using namespace std;


ostream &
operator<<(ostream &out, vector<int> &v)
{
	int i;

	for (i = 0; i < v.size(); i++)
		out << v[i] << " ";

	return (out);
}

/*
 * This has space complexity of O(n), but that's the price you pay to be able
 * to get it done in O(n log n) + O(n).  Doing it in-place takes longer.  More
 * on that below.
 */
vector<int>
peaks_valleys_1(vector<int> &v)
{
	int l_off = 0;
	int r_off = v.size() / 2;
	vector<int> result;

	std::sort(v.begin(), v.end());

	if (v.size() % 2)
		result.push_back(v[r_off++]);

	while (l_off < v.size() / 2 && r_off < v.size()) {
		result.push_back(v[l_off++]);
		result.push_back(v[r_off++]);
	}

	return (result);
}

void
swap(vector<int> &v, int x, int y)
{
	int tmp = v[x];
	v[x] = v[y];
	v[y] = tmp;
}

void
sift_left(vector<int> &v, int end, int start)
{
	int i;

	assert(end >= 0);

	while (start > end) {
		swap(v, start, start - 1);
		start--;
	}
}

/*
 * This one is done in place.  It's O(n log n) + O(n^2) => O(n^2).
 */
void
peaks_valleys_2(vector<int> &v)
{
	int start = v.size() / 2;
	int end = 0;

	if (v.size() % 2) {
		sift_left(v, end, start);
		end += 2;
		start++;
	}

	while (start < v.size()) {
		sift_left(v, end, start);
		end += 2;
		start++;
	}
}

int main(int argc, char **argv)
{
	int i;
	int len;
	vector<int> v;
	vector<int> result;

	assert(argc == 2);

	len = atoi(argv[1]);

	for (i = 0; i < len; i++)
		v.push_back(rand() % (len * 10));

	cout << v << endl;

	result = peaks_valleys_1(v);

	cout << result << endl;

	peaks_valleys_2(v);
	cout << v << endl;
}
