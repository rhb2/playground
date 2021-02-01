#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>


#define	BITS_PER_INT	(sizeof (int) * 8)

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

int
flip_bit_to_win(int val)
{
	int i;
	int offset;
	int array[32];
	int radius;
	int max = 0;

	(void) bzero(array, sizeof (array));

	/*
	 * First, rack up the locations of all zeros in the value.  Store them
	 * in `array[]' which is being used as a hashmap.  It's worth
	 * mentioning that `offset' will be the index of the first available
	 * spot in the map.  That is `offset - 1' will be the index of the
	 * last recorded zero in the string.
	 */
	for (i = 0; i < BITS_PER_INT; i++) {
		if (get_bit(val, i) == 0) {
			array[offset] = i;
			offset++;
		}
	}

	/*
	 * If we do not have any zeros in the value, then clearly, there is
	 * nothing that we can flip to create the longest bit string.
	 */
	if (offset == 0)
		return (0);

	/*
	 * If there is only one zero in the entire bit sequence, then just
	 * return 32 and save ourselves the effort of doing any real work.
	 */
	if (offset == 1)
		return (BITS_PER_INT);

	/*
	 * Initilize `max' to our first value.  This is essential the length
	 * of the string if the bit located at `array[0]' got flipped to 1.
	 * Put another way, we initialize max to the number of bits between
	 * the start of the bit string and whatever index is stored in
	 * `array[1]'.
	 */
	max = array[1];

	for (i = 1; i < offset - 1; i++) {
		radius = array[i + 1] - array[i - 1] - 1;

		if (radius > max)
			max = radius;
	}

	radius = BITS_PER_INT - array[i - 1];
	if (radius > max)
		max = radius;

	return (max);
}

int main(int argc, char **argv)
{
	int val = 0b11101111000111111111;
	int len = flip_bit_to_win(val);

	assert(len = 10);

	print_binary(val);

	printf("The longest sequence of 1s created by setting a bit: %d\n",
	    len);

	return (0);
}
