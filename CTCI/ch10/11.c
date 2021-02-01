#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>


void
array_print(int *array, int len)
{
	int i;

	for (i = 0; i < len; i++)
		printf("%d ", array[i]);

	printf("\n");
}

void
swap(int *array, int x, int y)
{
	array[x] = (array[x] + array[y]) - (array[y] = array[x]);
}

void
merge(int *array, int *tmp, int l_pos, int r_pos, int r_end)
{
	int i;
	int elems = r_end - l_pos + 1;
	int l_end = r_pos - 1;
	int tmp_pos = l_pos;

	assert(array != NULL && tmp != NULL);

	while (l_pos <= l_end && r_pos <= r_end) {
		if (array[l_pos] <= array[r_pos])
			tmp[tmp_pos++] = array[l_pos++];
		else
			tmp[tmp_pos++] = array[r_pos++];
	}

	while (l_pos <= l_end)
		tmp[tmp_pos++] = array[l_pos++];

	while (r_pos <= r_end)
		tmp[tmp_pos++] = array[r_pos++];

	for (i = 0; i < elems; i++, r_end--)
		array[r_end] = tmp[r_end];
}

void
peaks_and_valleys_impl(int *array, int *tmp, int left, int right)
{
	int middle = (left + right) / 2;

	assert(array != NULL && tmp != NULL);

	if (left >= right)
		return;

	peaks_and_valleys_impl(array, tmp, left, middle);
	peaks_and_valleys_impl(array, tmp, middle + 1, right);
	merge(array, tmp, left, middle + 1, right);	
}

/*
 * Take an unordered list of numbers and rearrange them such that every other
 * entry is a peak and a valley (successively).  As example, a sequence of
 * numbers such as:
 *
 *    [22, 34, 23, 38, 40, 17, 24, 8, 8]
 *
 * Can be rearranged so that the resulting output is:
 *
 *    [23, 8, 24, 8, 34, 17, 38, 22, 40]
 *
 * As it can be seen in the example sequence, the resulting array is a series
 * repeated rises and falls.  Every odd index is smaller than the values on
 * either side and every even index is larger than the values on either side.
 */
void
peaks_and_valleys(int *array, int len)
{
	int i;
	int middle = len / 2;
	int offset = 0;
	int *left;
	int *right;
	int *tmp = malloc(sizeof (int) * len);

	assert(tmp != NULL);

	/*
	 * First sort the numbers (yes, this is merge sort).  Strictly speaking,
	 * any O(n log n) sorting algorithm will do, but since we are using
	 * auxiliary storage and frankly, I wanted to practice mergesort, it
	 * seemed like a reasonable approach.
	 */
	peaks_and_valleys_impl(array, tmp, 0, len - 1);

	/*
	 * Now that the array is sorted, take `tmp' which should be a carbon
	 * copy of `array' at this point and split it in half, and use the
	 * reference `left' to refer to the first half and the reference
	 * `right' to refer to the second half.  Prepare to weave the lists
	 * together.
	 */
	left = tmp;
	right = &tmp[middle];

	/*
	 * If the original array is off in length, then that means that `left'
	 * has one more element than `right'.  Insert it in the result array
	 * now and increment our `right' pointer by one unit, making the
	 * left and right arrays equal in size.
	 */
	if (len % 2 == 1) {
		array[0] = right[0];
		right++;
		offset++;
	}

	/* Finally, perform the weave. */
	for (i = 0; i < middle; i++) {
		array[offset++] = left[i];
		array[offset++] = right[i];
	}
}

int main(int argc, char **argv)
{
	int i;
	int len;
	int *array;

	assert(argc == 2);

	len = atoi(argv[1]);
	array = malloc(sizeof (int) * len);

	for (i = 0; i < len; i++)
		array[i] = rand() % (len * 5);

	printf("Original array:\n");
	array_print(array, len);

	peaks_and_valleys(array, len);

	printf("\nPeaks and valleys\n");
	array_print(array, len);
	return (0);
}
