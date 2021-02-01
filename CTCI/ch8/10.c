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
move_up(pair_t p)
{
	pair_t up = p;
	up.row--;
	return (up);
}

pair_t
move_right(pair_t p)
{
	pair_t right = p;
	right.col++;
	return (right);
}

pair_t
move_left(pair_t p)
{
	pair_t left = p;
	left.col--;
	return (left);
}

void
matrix_set(int **matrix, pair_t loc, int val)
{
	assert(matrix != NULL);
	matrix[loc.col][loc.row] = val;
}

bool
validate_location(int **matrix, pair_t loc, int rows, int cols)
{
	assert(matrix != NULL);

	return (loc.row <= rows && loc.row >= 0 &&
	    loc.col <= cols && loc.col >= 0 &&
	    matrix[loc.col][loc.row] == 0);
}

void
paint_brush(int **matrix, pair_t loc, int rows, int cols, int val)
{

	assert(matrix != NULL);

	if (!validate_location(matrix, loc, rows, cols))
		return;

	/* Fill in this cell with the specified value. */
	matrix_set(matrix, loc, val);

	/* Do the rest of the canvas now. */
	paint_brush(matrix, move_up(loc), rows, cols, val);
	paint_brush(matrix, move_down(loc), rows, cols, val);
	paint_brush(matrix, move_left(loc), rows, cols, val);
	paint_brush(matrix, move_right(loc), rows, cols, val);
}

int main(int argc, char **argv)
{
	int i;
	int rows, cols;
	int **matrix;
	pair_t start;
	bool ret;

	cols = 10;
	rows = 10;

	matrix = matrix_zalloc(cols, rows);

	/*
	 * We are going to build a wall around a big group of zeros so that
	 * that there is no way out.  We will first attempt to paint brush
	 * everything inside the fence.
	 */
	for (i = 2; i < cols - 2; i++) {
		matrix[i][2] = 1;
		matrix[i][rows - 3] = 1;
	}

	for (i = 2; i < rows - 2; i++) {
		matrix[2][i] = 1;
		matrix[cols - 3][i] = 1;
	}

	/* 
	 * Note: If you put a hole in the wall, (for example), by saying
	 * something to the effect of:
	 *
	 * matrix[2][3] = 0;
	 *
	 * It will cause the paint brush operation to spill color out all over
	 * the map.
	 */

	matrix_print(matrix, cols, rows);

	printf("\n");

	/* Fill up the area inside the fence with 2. */
	start.row = 3;
	start.col = 3;
	paint_brush(matrix, start, rows - 1, cols - 1, 2);
	matrix_print(matrix, cols, rows);

	printf("\n");

	/* Now, fill up everything outside of the fence with 3. */
	start.row = 0;
	start.col = 0;
	paint_brush(matrix, start, rows - 1, cols - 1, 3);
	matrix_print(matrix, cols, rows);

	return (0);
}
