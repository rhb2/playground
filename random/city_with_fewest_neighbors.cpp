#include <iostream>
#include <vector>
#include <iomanip>
#include <map>

using namespace std;

ostream &
operator<<(ostream &out, const vector<vector<int>> &matrix)
{
	int i, j;

	for (i = 0; i < matrix.size(); i++) {
		for (j = 0; j < matrix[i].size(); j++) {
			out << std::setw(10);
			if (matrix[i][j] == INT_MAX)
				out << "inf";
			else
				out << matrix[i][j];;
		}
		out << endl;
	}

	return (out);
}

/*
 * Compute the cost required to get from any city to any city by way of the
 * city supplied by the caller.
 */
void
process_city(vector<vector<int>> &m, int city, int total)
{
	int i, j;

	for (i = 0; i < total; i++) {
		for (j = 0; j < total; j++) {
			int cost;

			if (m[i][city] == INT_MAX || m[city][j] == INT_MAX)
				continue;

			/*
			 * `cost' is what it takes to get from i to `city',
			 * plus whatever it takes to get from `city' to `j'.
			 */
			cost = m[i][city] + m[city][j];

			/*
			 * If we found a shorter path to `j' by going through
			 * `city', then update the cost with that it'd take to
			 * go i -> city -> j.
			 */
			if (i != j && cost < m[i][j])
				m[i][j] = cost;
		}
	}
}

/*
 * For a given city, return the total number of destinations that it can
 * reach that are below the cost `threashold' supplied by the caller.
 */
int
get_connections(vector<int> &v, int threshold)
{
	int count = 0;

	for (int i = 0; i < v.size(); i++)
		if (v[i] <= threshold)
			count++;

	return (count);
}

int
find_the_city(vector<vector<int>> &edges, int threshold, int nodes)
{
	vector<vector<int>> matrix;

	for (int i = 0; i < nodes; i++) {
		vector<int> tmp(nodes);
		matrix.push_back(tmp);

		for (int j = 0; j < nodes; j++)
			matrix[i][j] = INT_MAX;
	}

	/* It costs 0 for a city to get to itself. */
	for (int i = 0; i < edges.size(); i++)
		matrix[edges[i][0]][edges[i][0]] = 0;

	/*
	 * Fill out the cost that it takes for each city to arrive at its
	 * direct connections.  Note that there are two assignment instructions
	 * below because all connections are bidirectional.  If this was a
	 * directed graph, then there would only be one assignment.
	 */
	for (int i = 0; i < edges.size(); i++) {
		matrix[edges[i][0]][edges[i][1]] = edges[i][2];
		matrix[edges[i][1]][edges[i][0]] = edges[i][2];
	}

	cout << matrix << endl;

	for (int k = 0; k < nodes; k++)
		process_city(matrix, k, nodes);

	int smallest = INT_MAX;
	int city = -1;

	/*
	 * Find the city with the fewest number of other cities that it can
	 * reach below a certain threshold, favoring the city with the highest
	 * index number.
	 */
	for (int i = 0; i < matrix.size(); i++) {
		int n = get_connections(matrix[i], threshold);

		if (n <= smallest && i > city) {
			city = i;
			smallest = n;
		}
	}

	return (city);
}

int main(void)
{
	vector<vector<int>> edges1 = {
		{ 0, 1, 3 },
		{ 1, 2, 1 },
		{ 1, 3, 4 },
		{ 2, 3, 1 }
	};

	vector<vector<int>> edges2 = {
		{ 0, 1, 2 },
		{ 0, 4, 8 },
		{ 1, 2, 3 },
		{ 1, 4, 2 },
		{ 2, 3, 1 },
		{ 3, 4, 1 }
	};

//	cout << find_the_city(edges1, 4, 4) << endl;
	cout << find_the_city(edges2, 2, 5) << endl;

	return (0);
}
