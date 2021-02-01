#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "../util/matrix.h"


typedef struct pair {
	int col;
	int row;

} pair_t;

typedef struct map {
	int **matrix;	/* Storage for our table of numbers. */
	pair_t first;	/* Coordinates of the first row and col of the map. */
	pair_t last;	/* Coordinates of the last row and col of the map. */
} map_t;

void
check_pairs(pair_t start, pair_t end)
{
	assert(start.col <= end.col && start.row <= end.row);
}

/*
 * The following utility functions will divide a given map 4 ways at the point
 * specified by `loc'.  They will then initialize a map structure to have the
 * measurements of the desired quadrant.  This might seem like overkill, but
 * I wanted to keep the calculations out of the main algorithm to hopefully
 * make it easier to understand.  Each one of these returns the pointer passed
 * in to it which contains the measurements of the desired quadrant.  This
 * allows us to pass the entire function call as an argument to the search
 * function without call it separately to initialize `result' and then invoke
 * search on it.
 */
map_t *
quadrant1(map_t *map, map_t *result, pair_t loc)
{
	assert(map != NULL && result != NULL);

	(void) memcpy(result, map, sizeof (map_t));
	result->first.col = loc.col;
	result->last.row = loc.row;

	if (result->first.col == map->first.col)
		result->first.col = map->last.col;

	check_pairs(result->first, result->last);
	return (result);
}

map_t *
quadrant2(map_t *map, map_t *result, pair_t loc)
{
	assert(map != NULL && result != NULL);

	(void) memcpy(result, map, sizeof (map_t));
	result->last.col = loc.col;
	result->last.row = loc.row;

	check_pairs(result->first, result->last);
	return (result);
}

map_t *
quadrant3(map_t *map, map_t *result, pair_t loc)
{
	assert(map != NULL && result != NULL);

	(void) memcpy(result, map, sizeof (map_t));
	result->first.row = loc.row;
	result->last.col = loc.col;

	if (result->first.row == map->first.row)
		result->first.row = map->last.row;

	check_pairs(result->first, result->last);
	return (result);
}

map_t *
quadrant4(map_t *map, map_t *result, pair_t loc)
{ 
	assert(map != NULL && result != NULL);

	(void) memcpy(result, map, sizeof (map_t));
	result->first.col = loc.col;
	result->first.row = loc.row;

	if (result->first.col == map->first.col)
		result->first.col = map->last.col;

	if (result->first.row == map->first.row)
		result->first.row = map->last.row;

	check_pairs(result->first, result->last);
	return (result);
}

void
print_map(map_t mp)
{
	int col, row;
	map_t *map = &mp;

	assert(map != NULL);

	for (row = map->first.row; row <= map->last.row; row++) {
		for (col = map->first.col; col <= map->last.col; col++) {
			printf("%d%s", map->matrix[col][row],
			    map->matrix[col][row] < 10 ? "  " : " ");
		}
		printf("\n");
	}
}

map_t *
map_create(int cols, int rows)
{
	map_t *mp;
	int col, row;
	int offset = 0;

	if ((mp = malloc(sizeof (map_t))) == NULL)
		return (NULL);

	(void) bzero(mp, sizeof (map_t));

	if ((mp->matrix = matrix_zalloc(cols, rows)) == NULL) {
		free(mp);
		return (NULL);
	}

	mp->last.col = cols - 1;
	mp->last.row = rows - 1;

	for (col = 0; col < cols; col++) {
		for (row = 0; row < rows; row++) {
			mp->matrix[col][row] = offset + (2 * row);
		}
		offset += 2;
	}

	return (mp);
}

pair_t
get_center(map_t *mp)
{
	pair_t center;

	assert(mp != NULL);

	center.col = (mp->first.col + mp->last.col) / 2;
	center.row = (mp->first.row + mp->last.row) / 2;
	return (center);
}

int
map_get_elem(map_t *mp, pair_t pair)
{
	assert(mp != NULL);

	return (mp->matrix[pair.col][pair.row]);
}

bool
search(map_t *mp, int val)
{
	bool ret;
	map_t tmp;
	pair_t center;
	int center_val;

	if (memcmp(&mp->first, &mp->last, sizeof (pair_t)) == 0 &&
	    map_get_elem(mp, mp->last) != val)
		return (false);

	center = get_center(mp);
	center_val = map_get_elem(mp, center);

	/*
	 * We found the value that we are looking for.  We can stop the
	 * recursion and return at this point.
	 */
	if (val == center_val) {
		printf("Found %d at (%d, %d).\n", val, center.col, center.row);
		return (true);
	}

	/*
	 * If the value that were looking for is less than the center value,
	 * then check out the second qudrant.  If the value is greater than
	 * the center value, check out the fourth quadrant.
	 */
	if ((val < center_val && search(quadrant2(mp, &tmp, center), val)) ||
	    (val > center_val && search(quadrant4(mp, &tmp, center), val)))
			return (true);

	/*
	 * It's possible still for it to be in either the first or third
	 * quadrants.  If we have not had any luck yet, check those.
	 */
	return (search(quadrant1(mp, &tmp, center), val) ||
	    search(quadrant3(mp, &tmp, center), val));
}

int main(int argc, char **argv)
{
	int i;
	map_t *map;
	map_t test;
	int cols, rows;

	assert(argc == 3);

	cols = atoi(argv[1]);
	rows = atoi(argv[2]);

	map = map_create(cols, rows);
	assert(map != NULL);
	print_map(*map);

	printf("\n");
	pair_t loc = get_center(map);

	for (i = 0; i <= 24; i++) {
		if (!search(map, i))
			printf("Did not find %d.\n", i);
	}
	return (0);
}
