#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>


int
find_boundary(int *array, int left, int right)
{
	int middle;

	assert(array != NULL);

	if (left + 1 == right)
		return (left);

	middle = (left + right) / 2;

	if (array[middle] < array[left])
		return (find_boundary(array, left, middle));
	else
		return (find_boundary(array, middle, right));
}

int
binary_search(int *array, int left, int right, int val)
{
	int middle;

	assert(array != NULL);
	assert(left <= right);

	if (left == right)
		return (array[left] == val ? left: -1);

	middle = (left + right) / 2;

	if (val == array[middle])
		return (middle);

	if (val > array[middle])
		return (binary_search(array, middle + 1, right, val));
	else
		return (binary_search(array, left, middle - 1, val));
}

/*
 * For rotated search, we can just identify where the array rotation point is
 * and either search one half or the other using the above function.
 */
int
search_rotated(int *array, int len, int val)
{
	int i;
	int start;

	/* Finding the bounday is done in O(log n) time.  Don't worry. */
	i = find_boundary(array, 0, len - 1);

	/*
	 * Depending on which side of the boundary we search in, we will have
	 * a different starting point.
	 */
	if (val >= array[0] && val <= array[i]) {
		/* Between 0 and boundary (inclusive). */
		start = 0;
		len = i + 1;
	} else {
		/* Between the boundary (exclusive) and the end. */
		start = i + 1;
	}

	return (binary_search(array, start, len - 1, val));
}

void
test_search_rotated(int *array, int len, int val)
{
	int index = search_rotated(array, len, val);

	if (index == -1)
		printf("%d was not found\n", val);
	else
		printf("%d is located at %d\n", val, index);
}

void
print_array(int *array, int len)
{
	int i;

	assert(array != NULL);

	for (i = 0; i < len; i++)
		printf("%d ", array[i]);

	printf("\n");
}

void
shift_array_right(int *array, int len)
{
	int i, tmp;

	tmp = array[len - 1];

	for (i = len - 1; i > 0; i--)
		array[i] = array[i - 1];

	array[0] = tmp;
}

int main(int argc, char **argv)
{
	int i, j;
	int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	for (i = 0; i < 10; i++) {
		print_array(array, 10);

		for (j = 0; j < 10; j++)
			test_search_rotated(array, 10, j);

		printf("\n");
		shift_array_right(array, 10);
	}
	return (0);
}
