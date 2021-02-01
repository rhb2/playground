#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>


int
get_bit(int val, int index)
{
	int mask = (1 << index);
	return ((val & mask) ? 1 : 0);
}

void
print_binary(int val)
{
	int i;
	int bits = sizeof (int) * 8;

	for (i = bits - 1; i >= 0; i--)
		printf("%d", get_bit(val, i));

	printf("\n");
}

unsigned int
pairwise_swap(unsigned int val)
{
	unsigned int mask = 0xAAAAAAAA;

	unsigned int odds = ((val & mask) >> 1);
	unsigned int evens = ((val & ~mask) << 1);

	return (odds | evens);
}

void
test_pairwise(unsigned int val)
{
	int swapped = pairwise_swap(val);

	print_binary(val);
	print_binary(swapped);
}

int main(int argc, char **argv)
{
	test_pairwise(0xAAAAAAAA);
	test_pairwise(0xAAA00AAA);

	return (0);
}
