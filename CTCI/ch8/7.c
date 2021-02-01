#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

void
swap(int *array, int x, int y)
{
	int tmp;

	assert(array != NULL);

	tmp = array[x];
	array[x] = array[y];
	array[y] = tmp;
}

void
array_print(int *array, int len)
{
	int i;

	assert(array != NULL);

	for (i = 0; i < len; i++)
		printf("%c ", (char)array[i]);
	printf("\n");
}

void
permutations(int *array, int len, int offset)
{
	int i;

	assert(array != NULL);

	if (offset == len) {
		array_print(array, len);
		return;
	}

	for (i = offset; i < len; i++) {
		swap(array, offset, i);
		permutations(array, len, offset + 1);
		swap(array, offset, i);
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
	(void) bzero(array, sizeof (int) * len);

	for (i = 0; i < len; i++)
		array[i] = i + 'a';

	permutations(array, len, 0);
	
	return (0);
}
