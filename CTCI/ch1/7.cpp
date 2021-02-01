#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

void
print_matrix(vector<vector<int> > matrix)
{
	int row, col;
	int size = matrix.size();


	for (row = 0; row < size; row++) {
		for (col = 0; col < size; col++) {
			cout.width(3);
			cout << matrix[col][row] << " ";
		}
		cout << endl;
	}
}

void
rotate_90(vector<vector<int> > &matrix)
{
	int row, col;
	int size = matrix.size();
	int off, limit;

	size = matrix.size();

	for (row = 0, col = 0; row < size / 2; row++, col++) {
		int limit = size - row - 1;
		for (off = 0; off < limit - col; off++) {
			int tmp = matrix[col + off][row];
			matrix[col + off][row] = matrix[limit][row + off];
			matrix[limit][row + off] = matrix[limit - off][limit];
			matrix[limit - off][limit] = matrix[col][limit - off];
			matrix[col][limit - off] = tmp;
		}
	}
}

int main(int argc, char **argv)
{
	int i, j;
	int value = 0;
	vector< vector<int> > matrix;
	int n = atoi(argv[1]);

	for (i = 0; i < n; i++) {
		vector<int> v;
		for (j = 0; j < n; j++)
			v.push_back(value++);

		matrix.push_back(v);
	}

	print_matrix(matrix);
	cout << endl;
	rotate_90(matrix);
	print_matrix(matrix);
	return (0);
}
