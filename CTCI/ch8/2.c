#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "../util/matrix.h"


typedef struct pair {
	int row;
	int col;
} pair_t;

/*
 * The functions below are utility functions intended to take a given
 * location and adjust it such that the new location reflects the direction
 * in which we want to travel.  It's worth nothing that these return copies
 * of the location passed in.  They do not directly modify the original.  In
 * a lot of maze type problems, it is typical that we will need to generate
 * coordinates going in 4 different directions all based on the original.
 * This is the basis for why we do not modify the original.
 */
pair_t
move_down(pair_t p)
{
	pair_t down = p;
	down.row++;
	return (down);
}

pair_t
move_right(pair_t p)
{
	pair_t right = p;
	right.col++;
	return (right);
}

bool
find_path(int **matrix, pair_t loc, int rows, int cols)
{
	bool ret;

	assert(matrix != NULL);

	if (loc.row > rows || loc.col > cols)
		return (false);

	/*
	 * Mark our current location.  This is mostly to visualize the paths
	 * that we end up taking later.  This might come in handy.
	 */
	matrix[loc.col][loc.row] = 2;

	/* We have arrived at the destination. */
	if (loc.row == rows && loc.col == cols)
		return (true);

	/*
	 * If moving to the right is not out of bounds and the next cell over
	 * does not happen to be an obstruction, the move that way now.
	 */
	if (loc.col < cols && matrix[loc.col + 1][loc.row] !=1) {
		if (find_path(matrix, move_right(loc), rows, cols))
			return (true);
	}

	/*
	 * If moving down is not out of bounds and the next cell below us
	 * does not happen to be an obstruction, the move that way now.
	 */
	if (loc.row < rows && matrix[loc.col][loc.row + 1] !=1) {
		return (find_path(matrix, move_down(loc), rows, cols));
	}

	return (false);
}

int main(int argc, char **argv)
{
	int i;
	int rows, cols;
	int **matrix;
	pair_t start;
	bool ret;

	assert(argc == 3);

	cols = atoi(argv[1]);
	rows = atoi(argv[2]);

	matrix = matrix_zalloc(cols, rows);

	/*
	 * Throw some obstacles in the matrix.
	 */
	for (i = 0; i < rows - 3; i++)
		matrix[1][i] = 1;

	for (i = 1; i < cols; i++)
		matrix[i][rows - 2] = 1;

	(void) bzero(&start, sizeof (pair_t));
	ret = find_path(matrix, start, rows - 1, cols - 1);

	printf("0 = unvisited cell\n1 = obstruction\n2 = visited cell\n\n");
	matrix_print(matrix, cols, rows);
	
	if (ret) {
		printf("We found a path to the destination.\n");
	} else {
		printf("We were unable to find a path to the destination.\n");
	}

	return (0);
}
