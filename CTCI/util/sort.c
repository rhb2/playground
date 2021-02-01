#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


void
swap(char *array, int a, int b)
{
	int x = array[a];
	array[a] = array[b];
	array[b] = x;
}

void
print_array(char *array, int len)
{
	int i;

	for (i = 0; i < len; i++)
		printf("%d ", array[i]);
	printf("\n");
}

void
quicksort(char *array, int left, int right)
{
	int i, last;

	if (left >= right)
		return;

	swap(array, left, (left + right) / 2);

	last = left;
	for (i = left + 1; i <= right; i++) {
		if (array[i] < array[left]) {
			last++;
			swap(array, i, last);
		}
	}

	swap(array, left, last);
	quicksort(array, left, last - 1);
	quicksort(array, last + 1, right);
}
