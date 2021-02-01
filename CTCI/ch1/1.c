#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool
dupes(char *str, int len)
{
	int hashmap[128];
	int i;
	int index;

	memset(hashmap, 0, sizeof (hashmap));

	for (i = 0; i < len; i++) {
		index = str[i];
		if (hashmap[index] > 0)
			return (true);

		hashmap[index]++;
	}
	return (false);
}

int main(int argc, char **argv)
{
	char *str = "abcdefGgG";

	if (dupes(str, strlen(str)))
		printf("freddy dupes\n");

	return (0);
}
