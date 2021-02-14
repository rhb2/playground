#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

int
binsearch(int *array, int len, int val)
{
	int low, mid, high;

	low = 0;
	high = len - 1;

	while (low <= high) {
		mid = (low + high) / 2;

		if (val < array[mid])
			high = mid - 1;
		else if (val > array[mid])
			low = mid + 1;
		else
			return (mid);
	}

	return (-1);
}

int main(int argc, char **argv)
{
	int i;
	int len = atoi(argv[1]);
	int *array;

	array = malloc(sizeof (int) * len);

	assert(array != NULL);

	for (i = 0; i < len; i++)
		array[i] = i;

	printf("%d\n", binsearch(array, len, 11));
	return (0);
}
