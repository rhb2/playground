#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>


#define	ABS(x)	((x) < 0 ? (x) * -1 : (x))

typedef struct pair {
	int row;
	int col;
} pair_t;

void
pair_init(pair_t *p, int row, int col)
{
	assert(p != NULL);

	p->row = row;
	p->col = col;
}

bool
diagonal_conflict(pair_t p1, pair_t p2)
{
	int delta_col = ABS(p1.col - p2.col);
	int delta_row = ABS(p1.row - p2.row);

	return (delta_col == delta_row);
}

bool
valid_cell(pair_t p, pair_t *pairs, int len)
{
	int i;

	/*
	 * March through our list of locations where queens have been placed
	 * so far.  There is no collision on the row because we place one queen
	 * per row, but if we find another queen in a different row, but same
	 * column, or a queen that is on the diagonal of the location that
	 * are proposing, then that location must be disqualified.
	 */
	for (i = 0; i < len; i++) {
		if (p.col == pairs[i].col || diagonal_conflict(p, pairs[i]))
			return (false);
	}
	return (true);
}

void
print_pair(pair_t p)
{
	printf("(%d, %d)", p.col, p.row);
}

void
print_pairs(pair_t *pairs, int len)
{
	int i;

	assert(pairs != NULL);

	for (i = 0; i < len; i++) {
		print_pair(pairs[i]);
		printf(" ");
	}

	printf("\n");
}

void
place_queens(pair_t *locations, int row, int dimensions)
{
	int i;

	if (row == dimensions) {
		printf("We have a working solution!\n");
		print_pairs(locations, row);
	}

	for (i = 0; i < dimensions; i++) {
		pair_t p;
		pair_init(&p, row, i);

		if (!valid_cell(p, locations, row))
			continue;

		locations[row] = p;
		place_queens(locations, row + 1, dimensions);
	}
}

int main(int argc, char **argv)
{
	pair_t locations[8];
	(void) bzero(locations, sizeof (locations));
	place_queens(locations, 0, 8);
	return (0);
}
