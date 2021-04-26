#include <iostream>
#include <vector>
#include <map>

using namespace std;

ostream &
operator<<(ostream &out, const vector<vector<int>> &matrix)
{
	int i, j;

	for (i = 0; i < matrix.size(); i++) {
		for (j = 0; j < matrix[i].size(); j++)
			out << matrix[i][j] << " ";
		out << endl;
	}

	return (out);
}

void
paintfill(vector<vector<int>> &matrix, int from, int to, int row, int col)
{
	if (row < 0 || col < 0 || row >= matrix.size() || col >= matrix.size())
		return;

	if (matrix[col][row] != from)
		return;

	matrix[col][row] = to;

	paintfill(matrix, from, to, row + 1, col);
	paintfill(matrix, from, to, row - 1, col);
	paintfill(matrix, from, to, row, col + 1);
	paintfill(matrix, from, to, row, col - 1);
}

int main(int argc, char **argv)
{
	vector<vector<int>> matrix = {
		{ 1, 1, 1, 1, 1},
		{ 1, 2, 4, 5, 3},
		{ 1, 2, 1, 1, 2},
		{ 1, 2, 2, 1, 2},
		{ 1, 1, 1, 1, 2}
	};

	cout << matrix << endl;

	paintfill(matrix, 1, 0, 0, 0);

	cout << matrix << endl;
	return (0);
}
