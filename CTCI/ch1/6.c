#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

typedef struct pair {
	char c;
	int n;
} pair_t;

int
get_digits(int val)
{
	char buf[20];

	(void) bzero(buf, sizeof (buf));
	return (sprintf(buf, "%d", val));
}

void
compress(char *str)
{
	int i;
	int len;
	int offset;
	int comp_len = 0;
	pair_t *counts;

	assert(str != NULL);

	len = strlen(str);
	counts = malloc(sizeof (pair_t) * len);
	assert(counts != NULL);

	(void) bzero(counts, sizeof (pair_t) * len);

	offset = 0;
	counts[0].c = str[0];
	counts[0].n++;

	for (i = 1; i < len; i++) {
		if (str[i] != str[i - 1]) {
			offset++;
			counts[offset].c = str[i];
		}

		counts[offset].n++;
	}

	for (i = 0; i <= offset; i++)
		comp_len += 1 + get_digits(counts[i].n);

	if (comp_len >= len)
		return;

	(void) bzero(str, len);

	for (i = 0; i <= offset; i++)
		str += sprintf(str, "%c%d", counts[i].c, counts[i].n);

	free(counts);
}

int main(int argc, char **argv)
{
	char *str;
	assert(argv[1] != NULL);

	str = strdup(argv[1]);
	compress(str);
	printf("%s\n", str);
	return (0);
}
