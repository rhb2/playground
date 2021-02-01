#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "../util/array.h"
#include "../util/heap.h"

/*
 * This program demonstrates how to merge any number of sorted arrays in to
 * a single one.  The more arrays there are, the more important it is to find
 * the next smallest element offered by all of them efficiently.  A min-heap
 * is used to give us that information in constant time as opposed to linear
 * time.  One major application of this approach is used in an external sorting
 * procedure.
 */
int main(int argc, char **argv)
{
	int i;
	int num_arrays;
	int **arrays;
	int array_len;
	int *offsets;
	heap_t *hp;
	heap_elem_t elem;

	assert(argc == 3);

	num_arrays = atoi(argv[1]);
	array_len = atoi(argv[2]);

	hp = heap_create(num_arrays);
	assert(hp != NULL);

	/* Create a list of arrays. */
	arrays = malloc(sizeof (int *) * num_arrays);
	assert(arrays != NULL);

	/*
	 * Populate our list of arrays from above with `num_arrays' different
	 * arrays.  Each array will be of length `array_len', but will contain
	 * randomly generated values in increasing order.
	 */
	for (i = 0; i < num_arrays; i++)
		arrays[i] = int_array_sorted(array_len, array_len * 10);

	/*
	 * An array which maintains our current offset within each of the
	 * allocated ararys (above).  As we merge these arrays, our offsets
	 * within each respective array need to be tracked.
	 */
	offsets = int_array_zalloc(num_arrays);

	/* Print each array. */
	for (i = 0; i < num_arrays; i++) {
		printf("Array %d: ",  i);
		int_array_print(arrays[i], array_len);
	}

	printf("\n%d-way merge!: ", num_arrays);

	/*
	 * Time for the merge.  Kick off the process by storing the first
	 * element from each array in the min-heap.
	 */
	for (i = 0; i < num_arrays; i++) {
		elem.val = arrays[i][0];
		elem.key = i;
		offsets[i]++;
		heap_insert(hp, elem);
	}

	/* 
	 * Perform the merge.  The value `elem.key' is how we figure out which
	 * array the value that we just removed from the min-heap came from.
	 * Without that information, there is no way to tie it back to the
	 * original array.  This is necessary because upon removal from the
	 * heap, we will want to take the next element from _that_ array and
	 * insert it back in to the heap...unless of course there are no more
	 * elements in that array.
	 */
	while (heap_remove(hp, &elem)) {
		int array_num = elem.key;
		int offset = offsets[array_num];

		printf("%d ", elem.val);

		/*
		 * As mentioned above, the array that this element originally
		 * came from has more elements, grab the next one and insert it
		 * in to the heap.
		 */
		if (offset < array_len) {
			heap_elem_t tmp;
			tmp.val = arrays[array_num][offset];
			tmp.key = array_num;;
			offsets[array_num]++;
			heap_insert(hp, tmp);
		}
	}

	return (0);
}
