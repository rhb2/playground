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

	printf(": %d\n", val);
}

int
count_bits_set(int val)
{
	int count = 0;	

	while (val) {
		val &= (val - 1);
		count++;
	}
	return (count);
}

int
number_of_differences(int val1, int val2)
{
	int xor = (val1 ^ val2);
	return (count_bits_set(xor));
}

void
test_differences(int val1, int val2)
{
	print_binary(val1);
	print_binary(val2);

	printf("Differ by: %d\n", number_of_differences(val1, val2));
	
}

int main(int argc, char **argv)
{
	test_differences(10, 3);
	printf("\n");
	test_differences(7, 2);
	printf("\n");
	test_differences(15, 4);

	return (0);
}
