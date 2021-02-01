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

bool
should_skip(int *array, int start, int cur)
{
	int i;

	assert(array != NULL);

	for (i = start; i < cur; i++) {
		if (array[i] == array[cur])
			return (true);
	}

	return (false);
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
		/*
		 * What we are trying to say here is that if the current
		 * character matches any character between the current offset
		 * and that character, do not move forward with any recursion.
		 * This will prevent us from ever computing a duplicate
		 * string.  As an example, if you have an array:
		 *
		 *               ['a', 'b', 'a', 'c']
		 *
		 * And `offset' is currently 0, while `i' is 2, we will scan
		 * all elements in the array between 0 and 2 (exclusive of 2).
		 * We will compare each character to `array[2]'.  And if we
		 * find a match (i.e. a duplicate), we will skip it as opposed
		 * to making further recursive calls.  In the example above,
		 * we will find that `array[0]' matches `array[2]' and we
		 * will therefore not move forward with that sequence.  Once
		 * we get to the next element `c', located in `array[3]', we
		 * will see that no other character like it exists between
		 * `array[offset]' and `array[2]' and so we will move forward.
		 */
		if (should_skip(array, offset, i))
			continue;

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
		array[i] = (i % 2) ? 'a' : 'b';

	permutations(array, len, 0);
	
	return (0);
}
