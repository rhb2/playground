#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


bool
little_endian(void)
{
	int num = 1;
	char *array = (char *)&num;
	return (array[0] == 1);
}

int main()
{
	if (little_endian())
		printf("System is little endian.\n");
	else
		printf("System is big endian.\n");
}
