#ifndef	ARRAY_H
#define	ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


void int_array_print(int *, int);
int *int_array_random(int, int);
int *int_array_sorted(int, int);
int *int_array_sequential(int);
int *int_array_zalloc(int);

void swap_int(int *, int, int);
void quicksort(int *, int, int);

void
swap_int(int *array, int x, int y)
{
	assert(array != NULL);
	array[x] = (array[x] + array[y]) - (array[y] = array[x]);
}

void
quicksort(int *array, int left, int right)
{
	int i, last;

	if (left >= right)
		return;

	assert(array != NULL);

	last = left;
	swap_int(array, left, (left + right) / 2);

	for (i = left + 1; i <= right; i++)
		if (array[i] < array[left])
			swap_int(array, ++last, i);

	swap_int(array, left, last);
	quicksort(array, left, last - 1);
	quicksort(array, last + 1, right);
}

void
int_array_print(int *array, int len)
{
	int i;

	assert(array != NULL);

	for (i = 0; i < len; i++)
		printf("%d ", array[i]);

	printf("\n");	
}

int *
int_array_random(int len, int range)
{
	int i;
	int *array = malloc(sizeof (int) * len);

	assert(array != NULL);

	for (i = 0; i < len; i++)
		array[i] = rand() % range;

	return (array);
}

int *
int_array_sorted(int len, int range)
{
	int *array = int_array_random(len, range);
	quicksort(array, 0, len - 1);
	return (array);
}

int *
int_array_sequential(int len)
{
	int i;
	int *array = malloc(sizeof (int) * len);

	assert(array != NULL);

	for (i = 0; i < len; i++)
		array[i] = i;

	return (array);
}

int *
int_array_zalloc(int len)
{
	int *array;

	array = malloc(sizeof (int) * len);

	assert(array != NULL);

	(void) bzero(array, sizeof (int) * len);
	return (array);
}

#endif	/* ARRAY_H */
