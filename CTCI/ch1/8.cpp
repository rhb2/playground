#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

void
matrix_print(vector<vector<int> > &m)
{
	int row, col;
	int size;

	size = m.size();

	for (row = 0; row < size; row++) {
		for (col = 0; col < size; col++) {
			cout.width(3);
			cout << m[col][row];
		}
		cout << endl;
	}
}

void
zero_row(vector<vector<int> > &m, int row)
{
	int col;

	for (col = 0; col < m.size(); col++)
		m[col][row] = 0;
}

void
zero_col(vector<vector<int> > &m, int col)
{
	int row;
	
	for (row = 0; row < m.size(); row++)
		m[col][row] = 0;
}

void
zero_matrix(vector<vector<int> > &m)
{
	int row, col;
	int size = m.size();
	bool row_zero = false;
	bool col_zero = false;

	for (row = 0, col = 0; row < size; row++) {
		if (m[col][row] == 0) {
			col_zero = true;
			break;
		}
	}

	for (row = 0, col = 0; col < size; col++) {
		if (m[col][row] == 0) {
			row_zero = true;
			break;
		}
	}

	for (col = 0; col < size; col++) {
		for (row = 0; row < size; row++) {
			if (m[col][row] == 0) {
				m[col][0] = 0;
				m[0][row] = 0;
			}
		}
	}

	for (col = 1; col < size; col++) {
		if (m[col][0] == 0)
			zero_col(m, col);
	}

	for (row = 1; row < size; row++) {
		if (m[0][row] == 0)
			zero_row(m, row);
	}

	if (row_zero)
		zero_row(m, 0);

	if (col_zero)
		zero_col(m, 0);

}

int main(int argc, char **argv)
{
	int len = atoi(argv[1]);
	int i, j;
	int total = 0;
	vector<vector<int> > matrix;

	for (i = 0; i < len; i++) {
		vector<int> v;
		for (j = 0; j < len; j++) {
			v.push_back(++total);
		}
		matrix.push_back(v);
	}

	matrix[1][1] = 0;
	matrix[3][3] = 0;
	matrix_print(matrix);
	cout << endl;
	zero_matrix(matrix);
	matrix_print(matrix);
	return (0);
}
