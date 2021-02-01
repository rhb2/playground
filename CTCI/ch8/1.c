#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>


int triple_step_impl(int n, int current, int *cache)
{
	assert(cache != NULL);

	if (current == n)
		return (1);

	if (current > n)
		return (0);

	if (cache[current] != 0)
		return (cache[current]);

	cache[current] = triple_step_impl(n, current + 1, cache) +
	    triple_step_impl(n, current + 2, cache) +
	    triple_step_impl(n, current + 3, cache);

	return (cache[current]);
}

int
triple_step(int n)
{
	int *cache = malloc(sizeof (int) * n);

	assert(cache != NULL);

	(void) bzero(cache, sizeof (int) * n);
	return (triple_step_impl(n, 0, cache));
}

int main(int argc, char **argv)
{
	int n = triple_step(atoi(argv[1]));
	printf("%d\n", n);
	return (0);
}
