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
print_binary(uint8_t val)
{
	int i;
	int bits = 8;

	for (i = bits - 1; i >= 0; i--)
		printf("%d", get_bit(val, i));

	printf("\n");
}

uint8_t
reverse(uint8_t b)
{
	b = (((b & 0xF0) >> 4) | ((b & ~0xF0) << 4));
	b = (((b & 0xCC) >> 2) | ((b & ~0xCC) << 2));
	b = (((b & 0xAA) >> 1) | ((b & ~0xAA) << 1));
	return (b);
}

void
test_reverse(uint8_t b)
{
	uint8_t reversed = reverse(b);

	print_binary(b);
	print_binary(reversed);
}

int main(int argc, char **argv)
{
	test_reverse(0xAA);
	test_reverse(0xCA);

	return (0);
}
