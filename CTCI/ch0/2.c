#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

void
print_sums(int *array, int len, int offset, int sum)
{
	int i;

	assert(array != NULL);

	if (offset == len)
		return;

	for (i = offset; i < len; i++) {
		if (array[i] + array[offset] == sum)
			printf("(%d, %d)\n", array[i], array[offset]);
	}

	print_sums(array, len, offset + 1, sum);
}

void
array_print(int *array, int len)
{
	int i;

	assert(array != NULL);

	for (i = 0; i < len; i++)
		printf("%d ", array[i]);

	printf("\n");
}

int main(int argc, char **argv)
{
	int i;
	int len;
	int sum;
	int *array;

	assert(argc == 3);

	len = atoi(argv[1]);
	sum = atoi(argv[2]);
	array = malloc(sizeof (int) * len);
	for (i = 0; i < len; i++)
		array[i] = rand() % (len * 2);

	array_print(array, len);

	print_sums(array, len, 0, sum);
	return (0);
}
