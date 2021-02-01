#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


bool
is_perm(char *str1, char *str2)
{
	int map[128];
	int i;
	int len = strlen(str1);

	(void) memset(map, 0, sizeof (map));

	if (len != strlen(str2))
		return (false);

	for (i = 0; i < len; i++)
		map[str1[i]]++;

	for (i = 0; i < len; i++) {
		if (map[str2[i]] == 0)
			return (false);

		map[str2[i]]--;
	}
	return (true);
}

int main(int argc, char **argv)
{
	char *s1 = argv[1];
	char *s2 = argv[2];

	if (is_perm(s1, s2))
		printf("%s is a permutation of %s.\n", s1, s2);

	return (0);
}
