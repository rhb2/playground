#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>


void
matrix_print(int **matrix, int len)
{
	int i, j;

	for (i = 0; i < len; i++) {
		for (j = 0; j < len; j++)
			printf("%d%s", matrix[j][i],
			    matrix[j][i] < 10 ? "  " : " ");
		printf("\n");
	}
}

int **
matrix_create(int n)
{
	int **matrix;
	int *raw;

	int i, j;

	if ((raw = malloc(sizeof (int) * n * n)) == NULL)
		return (NULL);

	if ((matrix = malloc (sizeof (int *) * n)) == NULL) {
		free(raw);
		return (NULL);
	}

	(void) bzero(raw, sizeof (int) * n * n);
	(void) bzero(matrix, sizeof (int *) * n);

	for (i = 0; i < n; i++)
		matrix[i] = &raw[n * i];

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			matrix[i][j] = (i * n) + j;
	}

	return (matrix);
}

/*
 * Function takes a 2 dimensional matrix and rotates the whole thing by
 * 90 degrees in place (i.e. no auxiliary structures were used).  This
 * algorithm executes on the matrix like layers of an onion, starting with
 * the outter-most layer first and working inward.  Run time complexity is
 * O(n^2).
 */
void
matrix_rotate_90(int **matrix, int len)
{
	int i, layer;

	assert(matrix != NULL);

	for (layer = 0; layer < len / 2; layer++) {
		int first = layer;
		int last = len - 1 - layer;

		for (i = first; i < last; i++) {
			int offset = i - first;
			int top = matrix[i][first];

			/* Right column to top. */
			matrix[i][first] = matrix[last][i];

			/* Bottom column to left. */
			matrix[last][i] = matrix[last - offset][last];

			/* Left column to bottom. */
			matrix[last - offset][last] =
			    matrix[first][last - offset];

			/* Top column to left. */
			matrix[first][last - offset] = top;
		}
	}
}

int main(int argc, char **argv)
{
	int len;

	assert(argc == 2);

	len = atoi(argv[1]);

	int **matrix = matrix_create(len);
	matrix_print(matrix, len);

	printf("\n");
	matrix_rotate_90(matrix, len);
	printf("\n");
	matrix_print(matrix, len);

	return (0);
}
