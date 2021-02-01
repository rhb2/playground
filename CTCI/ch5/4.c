#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>


#define	BITS_PER_INT	(sizeof (int) * 8)

void print_binary(int);

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
update_bit(int *val, int index, int bitval)
{
	assert(val != NULL);
	assert(bitval == 0 || bitval == 1);

	if (bitval == 0)
		clear_bit(val, index);
	else
		set_bit(val, index);
}

void
swap_bits(int *val, int index1, int index2)
{
	int x = get_bit(*val, index1);
	int y = get_bit(*val, index2);

	update_bit(val, index1, y);
	update_bit(val, index2, x);
}

int
next_largest(int val)
{
	int i;
	int offset = 0;
	int last;
	int next = val;

	for (i = 0; i < BITS_PER_INT - 1; i++) {
		if (get_bit(next, i) == 1 && get_bit(next, i + 1) == 0) {
			swap_bits(&next, i, i + 1);
			last = i + 1;
			break;
		}
	}

	if (i == BITS_PER_INT - 1)
		return (-1);

	/*
	 * Take any remaining ones to the right of the bit that just got set
	 * and use our old friend from the partition sorting algorithm to
	 * concentrate them all at the beginning.
	 */
	for (i = 0; i < last; i++) {
		if (get_bit(next, i) == 1) {
			swap_bits(&next, offset, i);
			offset++;
		}
	}

	return (next);
}

int
next_smallest(int val)
{
	int i;
	int offset = 0;
	int last;
	int next = val;

	for (i = 0; i < BITS_PER_INT - 1; i++) {
		if (get_bit(next, i) == 0 && get_bit(next, i + 1) == 1) {
			swap_bits(&next, i, i + 1);
			last = i;
			break;
		}
	}

	if (i == BITS_PER_INT - 1)
		return (-1);

	/*
	 * Take any remaining ones to the right of the bit that just got set
	 * and use our old friend from the partition sorting algorithm to
	 * concentrate them all at the beginning.
	 */
	for (i = 0; i < last; i++) {
		if (get_bit(next, i) == 0) {
			swap_bits(&next, offset, i);
			offset++;
		}
	}

	return (next);
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

int main(int argc, char **argv)
{
	int val = 7;
	int ret;
	int i;

	for (i = 0; i < 10; i++) {
		val = next_largest(val);
		printf("Next largest value: %d\n", val);
		print_binary(val);
	}

	printf("\n\n");

	for (i = 0; i < 10; i++) {
		val = next_smallest(val);
		printf("Next largest value: %d\n", val);
		print_binary(val);
	}
	return (0);
}
