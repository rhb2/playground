#include <iostream>
#include <vector>

using namespace std;


bool
overlap(vector<int> &a, vector<int> &b)
{

	return ((a[0] <= b[0] && b[0] <= a[1]) ||
	    (b[0] <= a[0] && a[0] <= b[1]));
}

bool
compare(vector<int> &a, vector<int> &b)
{
	return (a[0] < b[0]);
}

vector<vector<int>>
merge(vector<vector<int>> &intervals)
{
	int i;
	int last = 0;
	vector<vector<int>> results;

	if  (intervals.size() == 0)
		return (results);

	std::sort(intervals.begin(), intervals.end(), compare);

	results.push_back(intervals[0]);

	for (i = 0; i < intervals.size(); i++) {
		if (overlap(results[last], intervals[i])) {
			results[last][0] = min(results[last][0],
			    intervals[i][0]);
			results[last][1] = max(results[last][1],
			    intervals[i][1]);
		} else {
			results.push_back(intervals[i]);
			last++;
		}
	}

	return (results);
}

ostream &
operator<<(ostream &out, const vector<vector<int>> &v)
{
	int i;

	for (i = 0; i < v.size(); i++)
		cout << "[" << v[i][0] << ", " << v[i][1] << "] ";

	return (out);
}

int main(void)
{
	int i, j;

	//vector<vector<int>> intervals = {{2,3},{4,5},{6,7},{8,9},{1,10}};
	vector<vector<int>> intervals = {{1,4},{0,2},{3,5}};
//	vector<vector<int>> intervals = {{1,3},{2,6},{8,10},{15,18}};
//	vector<vector<int>> intervals = {{1,4},{0,4}};
//	vector<vector<int>> intervals = {{1,4},{2, 3}};
	vector<vector<int>> result;

	cout << intervals << endl;

	result = merge(intervals);

	cout << intervals << endl;
	cout << result << endl;

	return (0);
}
