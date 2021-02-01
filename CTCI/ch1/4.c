#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>


int
to_index(char c)
{
	int index = tolower(c);
	return (index - 'a');
}

bool
is_palindrome_perm(char *str)
{
	int len, i, index;
	int odd_occ = 0;
	int map[26];

	assert(str != NULL);

	len = strlen(str);
	(void) memset(map, 0, sizeof (map));

	for (i = 0; i < len; i++) {
		/* Ignore anything other than a-z, A-Z. */
		if ((index = to_index(str[i])) == -1)
			continue;

		map[index]++;
	}

	for (i = 0; i < 26; i++) {
		if (map[i] % 2)
			odd_occ++;

		if (odd_occ > 1)
			return (false);
	}

	return (true);
}	


int main(int argc, char **argv)
{
	assert(argv[1] != NULL);

	printf("%s\n", is_palindrome_perm(argv[1]) ? "yes" : "no");

	return (0);
}
