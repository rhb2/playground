#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>


void
matrix_print(int **matrix, int col, int row)
{
	int i, j;

	for (j = 0; j < row; j++) {
		for (i = 0; i < col; i++)
			printf("%d%s", matrix[i][j],
			    matrix[i][j] < 10 ? "  " : " ");
		printf("\n");
	}
}

int **
matrix_zalloc(int cols, int rows)
{
	int **matrix;
	int *raw;
	int i;

	if ((raw = malloc(sizeof (int) * cols * rows)) == NULL)
		return (NULL);

	if ((matrix = malloc (sizeof (int *) * cols)) == NULL) {
		free(raw);
		return (NULL);
	}

	(void) bzero(raw, sizeof (int) * cols * rows);
	(void) bzero(matrix, sizeof (int *) * cols);

	/* Wire it up. */
	for (i = 0; i < cols; i++)
		matrix[i] = &raw[rows * i];

	return (matrix);
}

/*
 * In most cases, this function won't be necessary and one can just call
 * `matrix_zalloc()' instead, but on occasions, some toy problems need it
 * to be initialized with all unique values.  That's where this constructor
 * comes in handy.
 */
int **
matrix_create(int x, int y)
{
	int **matrix;
	int *raw;
	int i, j;
	int count = 0;

	/* Allocate a (zero'd out) matrix with the dimensions x, y. */
	if ((matrix = matrix_zalloc(x, y)) == NULL)
		return (NULL);

	/* Populate it with unqique values. */
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

/*
int main(int argc, char **argv)
{
	int x, y;

	assert(argc == 3);

	x = atoi(argv[1]);
	y = atoi(argv[2]);

	int **matrix = matrix_create(x, y);
	matrix_print(matrix, x, y);
	printf("\n");

	sprinkle_zeros(matrix, x, y, 5);
	matrix_print(matrix, x, y);
	printf("\n");

	return (0);
}*/
