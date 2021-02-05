#include <iostream>
#include <vector>
#include <set>

using namespace std;


ostream &
operator <<(ostream &out, const pair<int, int> &p)
{
	out << "(" <<  p.first << ", " << p.second << ")";
	return (out);
}

ostream &
operator <<(ostream &out, const set<pair<int, int>> &s)
{
	set<pair<int, int>>::iterator si;

	for (si = s.begin(); si != s.end(); si++)
		out << *si;

	return (out);
}

ostream &
operator <<(ostream &out, const vector<pair<int, int>> &v)
{
	int i;

	for (i = 0; i < v.size(); i++)
		out << v[i];

	return (out);
}

void
find_path_impl(
	int rows,
	int cols,
	pair<int, int> loc,
	set<pair<int, int>> &visited,
	set<pair<int, int>> &obstacles,
	vector<pair<int, int>> path)
{
	pair<int, int> tmp;

	if ((loc.first < 0 || loc.first >= rows) ||
	    (loc.second < 0 || loc.second >= cols))
		return;

	/*
	 * If our new location is an obstacle or we have already visited it,
	 * then return.
	 */
	if (obstacles.find(loc) != obstacles.end() ||
	    visited.find(loc) != visited.end())
		return;

	if (loc.first == rows - 1 && loc.second == cols - 1) {
		cout << "We found the way!" << endl << path << endl;
		return;
	}

	visited.insert(loc);
	path.push_back(loc);

	tmp = loc;
	loc.first++;
	find_path_impl(rows, cols, tmp, visited, obstacles, path);

	tmp = loc;
	loc.first--;
	find_path_impl(rows, cols, tmp, visited, obstacles, path);

	tmp = loc;
	loc.second++;
	find_path_impl(rows, cols, tmp, visited, obstacles, path);

	tmp = loc;
	loc.second--;
	find_path_impl(rows, cols, tmp, visited, obstacles, path);

	path.pop_back();
}
    

void
find_path(int rows, int cols, set<pair<int, int>> &obstacles)
{
	set<pair<int, int>> visited;
	pair<int, int> start(0, 0);
	vector<pair<int, int>> path;

	find_path_impl(rows, cols, start, visited, obstacles, path);
}

int main(int argc, char **argv)
{
	int i;
	int rows, cols;
	set<pair<int, int>> obstacles;

	rows = atoi(argv[1]);
	cols = atoi(argv[2]);

	for (i = 0; i < rows; i++) {
		pair<int, int> p(rand() % rows, rand() % cols);
		if (obstacles.find(p) != obstacles.end()) {
			i--;
			continue;
		}
		obstacles.insert(p);
	}

	cout << "obstacles: " << obstacles << endl;
	find_path(rows, cols, obstacles);

	return (0);
}
