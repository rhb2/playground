#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

bool
compare_at(char *s1, int n, char *s2)
{
	int len, i, offset;

	assert(s1 != NULL && s2 != NULL);

	len = strlen(s1);

	for (i = 0, offset = n; i < len; i++) {
		if (s1[offset] != s2[i])
			return (false);

		offset = (offset + 1) % len;
	}

	return (true);
}

/*
 * The run time complexity is O(n^2), but on the positive side, it does not
 * require additional storage to get it done.  That is, it's done in place.
 */
bool
is_rotation_1(char *s1, char *s2)
{
	int len, i;

	assert(s1 != NULL && s2 != NULL);

	len = strlen(s1);

	if (len != strlen(s2))
		return (false);

	for (i = 0; i < len; i++) {
		if (compare_at(s1, i, s2))
			return (true);
	}

	return (false);
}

/*
 * The run time complexity is O(2n) => O(n), but it requires extra storage in
 * order to get the job done.  If the data being compared is astronomically
 * large, it might be worth going with is_rotation_1() and looking for ways to
 * further optimize.
 */
bool
is_rotation_2(char *s1, char *s2)
{
	int len, i;
	char *s1s1;
	bool ret;

	assert(s1 != NULL & s2 != NULL);

	if ((len = strlen(s1)) != strlen(s2))
		return (false);

	s1s1 = malloc(len * 2);

	assert(s1s1 != NULL);

	sprintf(s1s1, "%s%s", s1, s1);

	ret = (strstr(s1s1, s2) != NULL);

	/* Don't leak.  It's not cool. */
	free(s1s1);
	return (ret);
}

int main(int argc, char **argv)
{
	assert(argv[1] != NULL && argv[2] != NULL);

	printf("%s\n", is_rotation_1(argv[1], argv[2]) ? "yes" : "no");
	printf("%s\n", is_rotation_2(argv[1], argv[2]) ? "yes" : "no");
	return (0);
}
