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
set_bit(int *val, int index)
{
	int mask = (1 << index);

	*val = (*val | mask);
}

void
clear_bit(int *val, int index)
{
	int mask = ~(1 << index);

	*val = (*val & mask);
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

/*
 * Given a value, and a range where `i' is less significant than `j', clear
 * all bits between them (inclusive).
 */
void
clear_range(int *val, int i, int j)
{
	int mask = -1;
	int range = j - i + 1;
	mask = (mask << range) | ~(-1 << i);

	*val = (*val & mask);
}

/*
 * Insert a string of bits inside of another string of bits within the range
 * of `i' and `j'.
 */
void
insert(int *val, int bits, int i, int j)
{
	/* First clear a window for the bits that we will insert. */
	clear_range(val, i, j);

	/* Now perform a bitwise OR with the bits that we want to set. */
	*val = (*val | (bits << i));
}

int main(int argc, char **argv)
{
	int val = 0b10000000000;
	int bits = 0b10011;

	insert(&val, bits, 2, 6);
	print_binary(val);
	return (0);
}
