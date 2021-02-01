#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

int
get_digits(int val)
{
	char buf[100];

	(void) bzero(buf, sizeof (buf));
	return  (sprintf(buf, "%d", val));
	//return (strlen(buf));
}

int main(int argc, char **argv)
{
	int val = atoi(argv[1]);
	printf("Number of digits in %d = %d\n", val, get_digits(val));
	return (0);
}
