#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>


#define	ABS(x)		((x) < 0 ? (0 - (x)) : (x))
#define	MIN(x, y)	((x) < (y) ? (x) : (y))
#define	MAX(x, y)	((x) > (y) ? (x) : (y))

int
recursive_multiply_impl(int x, int y)
{
	if (y == 0)
		return (0);

	return (x + recursive_multiply_impl(x, y - 1));
}

int
recursive_multiply_impl_faster(int min, int max)
{
	int s;
	int half;

	if (min == 0)
		return (0);

	if (min == 1)
		return (max);

	s = (min >> 1);

	half = recursive_multiply_impl_faster(s, max);

	/*
	 * If `min' was an odd valued number (take for example 5), then after
	 * halfing it above) and passing it to the recursive call, we would
	 * be passing 2.  This means that will be short by 1 count of max, so
	 * add it on ourselves.  Otherwise, we can just return `half' + `half'.
	 */
	if (min % 2) {
		return (half + half + max);
	} else {
		return (half + half);
	}
}

int
recursive_multiply(int x, int y)
{
	int sign = 1;
	int product;
	int min = MIN(ABS(x), ABS(y));
	int max = MAX(ABS(x), ABS(y));

	if ((x > 0 && y < 0) || (x < 0 && y > 0))
		sign = -1;

	product = recursive_multiply_impl_faster(min, max);

	return (sign > 0 ? product : 0 - product);	
}

int main(int argc, char **argv)
{
	int x, y;

	x = 5;
	y = 12;
	printf("%d * %d = %d\n", x, y, recursive_multiply(x, y));

	x = -5;
	y = 12;
	printf("%d * %d = %d\n", x, y, recursive_multiply(x, y));

	x = 5;
	y = -12;
	printf("%d * %d = %d\n", x, y, recursive_multiply(x, y));

	x = -5;
	y = -12;
	printf("%d * %d = %d\n", x, y, recursive_multiply(x, y));
	return (0);
}
