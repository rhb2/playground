#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


void
swap(char *array, int a, int b)
{
	int x = array[a];
	array[a] = array[b];
	array[b] = x;
}

/*
 * Given a string and the current offset, seek to find the next non, whitespace
 * character in the string.  Return the index of the offset.
 */
int
seek_left(char *str, int offset)
{
	int i;

	for (i = offset; i > 0; i--) {
		if (str[i] != ' ')
			return (i);
	}

	return (i);
}

void
urlify(char *str)
{
	int next, last, i, len;

	len = strlen(str);
	last = len - 1;

	for (next = seek_left(str, last); next > 0;
	    next = seek_left(str, next)) {
		while (str[next] != ' ' && next > 0) {
			swap(str, next, last);
			next--;
			last--;
		}

		str[last--] = '%';
		str[last--] = '0';
		str[last--] = '2';

		if (str[last] != ' ')
			break;
	}
}

int main(int argc, char **argv)
{
	int len = strlen(argv[1]);
	char *str = malloc(len);
	(void) memset(str, 0, len);
	(void) strlcpy(str, argv[1], len + 1);
	urlify(str);
	printf("%lu\n%s\n", strlen(str), str);
	return (0);
}
