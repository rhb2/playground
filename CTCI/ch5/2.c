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

void
print_double(double val)
{
	int i;
	int count = 0;
	char binary[32]; /* Extra character for the decimal point. */

	(void) bzero(binary, sizeof (binary));

	if (val >= 1 || val <= 0) {
		printf("ERROR\n");
		return;
	}

	while (val > 0) {
		double lol = val * 2;

		if (count >= 32) {
			printf("ERROR\n");
			return;
		}

		if (lol >= 1) {
			binary[count] = '1';
			val = lol - 1;
		} else {
			binary[count] = '0';
			val = lol;
		}
		count++;
	}
	printf(".%s\n", binary);
}

int main(int argc, char **argv)
{
	double val = .625;

	print_double(val);
	return (0);
}
