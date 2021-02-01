#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "../util/matrix.h"


int
coins_impl(int *array, int len, int amount, int index, int **map)
{
	int i;
	int ways = 0;

	if (map[amount][index] > 0) {
		printf("Dynamic programming saves the day.\n");
		return (map[amount][index]);
	}

	if (amount == 0)
		return (1);

	if (index > len)
		return (0);

	for (i = 0; i * array[index] <= amount; i++) {
		int new_amt = amount - (i * array[index]);
		ways += coins_impl(array, len, new_amt, index + 1, map);
	}

	map[amount][index] = ways;
	return (ways);
}

int
coins(int cents)
{
	int i;
	int denoms[] = {25, 10, 5, 2};
	int len = sizeof (denoms) / sizeof (int);

	int **map = matrix_zalloc(cents + 1, len + 1);
	assert(map != NULL);

	return (coins_impl(denoms, len - 1, cents, 0, map));
}

int main(int argc, char **argv)
{
	int cents;

	assert(argc == 2);

	cents = atoi(argv[1]);
	printf("Ways to make %d cents: %d\n", cents, coins(cents));
	return (0);
}
