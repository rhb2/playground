#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "heap.h"

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
	assert(array != NULL);

	array[x] = (array[x] + array[y]) - (array[y] = array[x]);
}

void
quicksort(int *array, int left, int right)
{
	int i, last;

	assert(array != NULL);

	if (left >= right)
		return;

	swap(array, left, (left + right) / 2);
	last = left;

	for (i = left + 1; i <= right; i++)
		if (array[i] < array[left])
			swap(array, ++last, i);

	swap(array, left, last);
	quicksort(array, left, last - 1);
	quicksort(array, last + 1, right);
}

int *
create_ordered(int len, int range)
{
	int i;
	int *array;

	if ((array = malloc(sizeof (int) * len)) == NULL)
		return (NULL);

	for (i = 0; i < len; i++)
		array[i] = rand() % range;

	quicksort(array, 0, len - 1);
	return (array);
}

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

	arrays = malloc(sizeof (int *) * num_arrays);
	assert(arrays != NULL);

	offsets = malloc(sizeof (int) * num_arrays);
	(void) bzero(offsets, sizeof (int) * num_arrays);

	for (i = 0; i < num_arrays; i++) {
		int *array = create_ordered(array_len, array_len * 10);
		assert(array != NULL);

		arrays[i] = array;
	}

	for (i = 0; i < num_arrays; i++) {
		printf("Array %d: ",  i);
		array_print(arrays[i], array_len);
	}

	printf("\n%d-way merge!: ", num_arrays);

	for (i = 0; i < num_arrays; i++) {
		elem.val = arrays[i][0];
		elem.meta = (void *)i;
		offsets[i]++;
		heap_insert(hp, elem);
	}

	while (heap_remove(hp, &elem)) {
		int meta = (int)elem.meta;

		printf("%d ", elem.val);

		if (offsets[meta] < array_len) {
			heap_elem_t tmp;
			int offset = offsets[meta];
			tmp.val = arrays[meta][offset];
			tmp.meta = (void *)meta;
			
			heap_insert(hp, tmp);
			offsets[meta]++;
		}
	}

	heap_print(hp);

	return (0);
}
