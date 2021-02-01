#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>


#define	MIN(x, y)	((x) < (y) ? (x) : (y))
#define	MAX(x, y)	((x) > (y) ? (x) : (y))

/*
 * With the assurance that elements in the list are all unique, this is a
 * binary search problem with a worst case complexity of O(log(n)).
 */
int
magic_index(int *array, int left, int right)
{
	int middle;
	int l = -1;
	int r = -1;

	if (left > right)
		return (-1);

	middle = (left + right) / 2;
	if (array[middle] == middle)
		return (middle);

	if (middle > array[middle])
		return (magic_index(array, middle + 1, right));
	else
		return (magic_index(array, left, middle - 1));
}

/*
 * This comes down to a wost cast complexity of O(n * log(n)).  There are
 * optimizations that were made (observe the use of the MIN/MAX macros below,
 * but ultimately, they may only help trivially.
 */
int
magic_index_not_unique(int *array, int left, int right)
{
	int middle;
	int midval;
	int l = -1;
	int r = -1;

	if (left > right)
		return (-1);

	middle = (left + right) / 2;
	midval = array[middle];

	if (midval == middle)
		return (middle);

	if ((l = magic_index(array, left, MIN(midval, middle - 1))) != -1)
		return (l);

	if ((r = magic_index(array, MAX(midval, middle + 1), right)) != -1)
		return (r);

	return (-1);
}

int main(int argc, char **argv)
{
	int n;
	int unique[] = {-40, -20, -1, 1, 2, 3, 5, 7, 9, 12, 13};
	int non_unique[] = {-10, -5, 2, 2, 2, 3, 4, 7, 9, 12, 13};

	n = magic_index(unique, 0, 10);
	printf("%d\n", n);

	n = magic_index_not_unique(non_unique, 0, 10);
	printf("%d\n", n);
	return (0);
}
