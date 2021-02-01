#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>


void
matrix_print(int **matrix, int x, int y)
{
	int i, j;

	for (j = 0; j < y; j++) {
		for (i = 0; i < x; i++)
			printf("%d%s", matrix[i][j],
			    matrix[i][j] < 10 ? "  " : " ");
		printf("\n");
	}
}

int **
matrix_create(int x, int y)
{
	int **matrix;
	int *raw;
	int i, j;
	int count = 0;

	if ((raw = malloc(sizeof (int) * x * y)) == NULL)
		return (NULL);

	if ((matrix = malloc (sizeof (int *) * x)) == NULL) {
		free(raw);
		return (NULL);
	}

	(void) bzero(raw, sizeof (int) * x * y);
	(void) bzero(matrix, sizeof (int *) * x);

	for (i = 0; i < x; i++)
		matrix[i] = &raw[y * i];

	for (i = 0; i < x; i++) {
		for (j = 0; j < y; j++)
			matrix[i][j] = count++;
	}

	return (matrix);
}

void
sprinkle_zeros(int **matrix, int x, int y, int pct)
{
	int i, j, rnd;

	assert(matrix != NULL);

	for (i = 0; i < x; i++) {
		for (j = 0; j < y; j++) {
			rnd = rand() % 100;
			if (rnd < pct)
				matrix[i][j] = 0;
		}
	}
}

/* Zero out a given row starting at `start' and ending at `end'. */
void
zero_row(int **matrix, int row, int start, int end)
{
	int i;

	assert(matrix != NULL);

	for (i = start; i < end; i++)
		matrix[i][row] = 0;
}

/* Zero out a given column starting at `start' and ending at `end'. */
void
zero_col(int **matrix, int col, int start, int end)
{
	int i;

	assert(matrix != NULL);

	for (i = start; i < end; i++)
		matrix[col][i] = 0;
}

void
find_zeros(int **matrix, int x, int y, bool *rows, bool *cols)
{
	int i, j;

	assert(matrix != NULL && rows != NULL && cols != NULL);

	for (i = 0; i < x; i++) {
		for (j = 0; j < y; j++) {
			if (matrix[i][j] == 0) {
				cols[i] = true;
				rows[j] = true;
			}
		}
	}
}

/*
 * Similar to find_zeros() above, except that instead of doing the book
 * keeping in separate storage, we use the first row and column of the matrix
 * instead.  This will reduce the space complexity from O(n) to O(1).
 */
void
zero_out2(int **matrix, int x, int y)
{
	int i, j;
	bool first_row = false;
	bool first_col = false;

	assert(matrix != NULL);

	/* Scan the first row for zeros. */
	for (i = 0; i < x; i++) {
		if (matrix[i][0] == 0) {
			first_row = true;
			break;
		}
	}

	/* Scan the first column for zeros. */
	for (i = 0; i < y; i++) {
		if (matrix[0][i] == 0) {
			first_col = true;
			break;
		}
	}

	/*
	 * Scan the rest of the matrix.  If there are any zeros in a given
	 * column, reflect that in the first row.  If there are any zeros in
	 * a given row, reflect that in the first column.
	 */
	for (i = 1; i < x; i++) {
		for (j = 1; j < y; j++) {
			if (matrix[i][j] == 0) {
				matrix[i][0] = 0;
				matrix[0][j] = 0;
			}
		}
	}

	/*
	 * Scan the first row now.  For all entries that contain a zero, we
	 * should zero out the entire column.
	 */
	for (i = 1; i < x; i++) {
		if (matrix[i][0] == 0) {
			int start = 1;
			int end = y;
			zero_col(matrix, i, start, end);
		}
	}

	/*
	 * Scan the first column now.  For all entries that contain a zero, we
	 * should zero out the entire row.
	 */
	for (i = 1; i < y; i++) {
		if (matrix[0][i] == 0) {
			int start = 1;
			int end = x;
			zero_row(matrix, i, start, end);
		}
	}

	if (first_row)
		zero_row(matrix, 0, 0, x);

	if (first_col)
		zero_col(matrix, 0, 0, y);
}

/*
 * x represents the total number of columns (or the row length).
 * y represents the total number of rows (or the columns length).
 * Note: This can also be done with even less space if instead of using
 * any auxilary storage, we use the first column and row of the matrix
 * instead.  At some point I might entertain adding that as an alternative
 * solution, but this is good enough for the demo, lol.
 */
void
zero_out(int **matrix, int x, int y)
{
	int i;
	bool *rows = malloc(sizeof (bool) * y);
	bool *cols = malloc(sizeof (bool) * x);

	assert(matrix != NULL && rows != NULL && cols != NULL);

	(void) bzero(rows, sizeof (bool) * y);
	(void) bzero(cols, sizeof (bool) * x);

	find_zeros(matrix, x, y, rows, cols);

	/* Zero out the rows. */
	for (i = 0; i < y; i++) {
		if (rows[i])
			zero_row(matrix, i, 0, x);
	}

	/* Zero out the columns. */
	for (i = 0; i < x; i++) {
		if (cols[i])
			zero_col(matrix, i, 0, y);
	}

	free(rows);
	free(cols);
}

int main(int argc, char **argv)
{
	int x, y;

	assert(argc == 3);

	x = atoi(argv[1]);
	y = atoi(argv[2]);

	int **matrix = matrix_create(x, y);
	matrix_print(matrix, x, y);
	printf("\n");

	/* Randomly distribute zeros to roughly about 5% of the matrix. */
	sprinkle_zeros(matrix, x, y, 5);
	matrix_print(matrix, x, y);
	printf("\n");

	zero_out2(matrix, x, y);
	matrix_print(matrix, x, y);
	printf("\n");

	return (0);
}
