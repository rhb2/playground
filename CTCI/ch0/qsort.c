#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>


void
print_array(int *array, int len)
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
quicksort(int *array, int left, int right)
{
	int i, last;

	if (left >= right)
		return;

	swap(array, left, (left + right) / 2);

	last = left;

	for (i = left + 1; i <= right; i++)
		if (array[i] <= array[left])
			swap(array, ++last, i);

	swap(array, left, last);
	quicksort(array, left, last - 1);
	quicksort(array, last + 1, right);
}


int main(int argc, char **argv)
{
	int len = atoi(argv[1]);
	int *array = malloc(sizeof (int) * len);
	int i;

	for (i = 0; i < len; i++)
		array[i] = rand() % 100;

	print_array(array, len);
	quicksort(array, 0, len - 1);
	print_array(array, len);
	return (0);
}
