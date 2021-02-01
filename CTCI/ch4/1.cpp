#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

bool
find_route(vector<vector<int>> &al, int start, int end)
{
	queue<int> q;
	map<int, bool> m;

	if ((start >= al.size() || start < 0) ||
	    (end >= al.size() || end < 0))
		return (false);

	q.push(start);
	m[start] = true;

	while (!q.empty()) {
		int i;
		int node = q.front();
		q.pop();

		if (node == end)
			return (true);

		/*
		 * Add all neighbors to the queue that we have not visited
		 * yet.
		 */
		for (i = 0; i < al.at(node).size();  i++) {
			int neighbor = al.at(node).at(i);
			if (m.find(neighbor) != m.end())
				continue;

			m[neighbor] = true;
			q.push(neighbor);
		}
	}


	return (false);
}

int main(int argc, char **argv)
{
	int i;
	vector<vector<int>> al;

	for (i = 0; i < 6; i++) {
		vector<int> v;
		al.push_back(v);
	}

	al.at(0).push_back(1);
	al.at(0).push_back(3);

	al.at(1).push_back(0);

	al.at(2).push_back(3);

	al.at(3).push_back(5);

	al.at(4).push_back(0);
	al.at(5).push_back(4);

	if (find_route(al, 0, 4))
		cout << "Path exists." << endl;
	else
		cout << "Path does not exist." << endl;

	return (0);
}
