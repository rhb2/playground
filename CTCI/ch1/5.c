#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>


int
strlencmp(char *s1, char *s2, char **small, char **big)
{
	int l1, l2, diff;

	assert(s1 && s2 && small && big);

	l1 = strlen(s1);
	l2 = strlen(s2);
	diff = l1 - l2;

	/* Strings are equal in length. */
	if (diff == 0)
		return (0);

	/* Strings differ in length by 1. */
	if (diff == -1 || diff == 1) {
		if (l1 > l2) {
			*big = s1;
			*small = s2;
		} else {
			*big = s2;
			*small = s1;
		}
		return (1);
	}

	/*
	 * By process of elimination, the length disparity between the two
	 * strings must be more than 2.
	 */
	return (-1);
	
}

bool
one_away(char *s1, char *s2, bool equal_len)
{
	int len;
	int i = 0;
	int j = 0;
	int diffs = 0;

	assert(s1 && s2);

	len = strlen(s2);

	while (j < len) {
		if (s1[i] == s2[j]) {
			i++;
			j++;
		} else {
			diffs++;
			j++;
			if (equal_len)
				i++;
		}

		/*
		 * If we have already diverged by more than one character then
		 * we are done.  No point in even continuing.
		 */
		if (diffs > 1)
			return (false);
	}
	return (diffs == 1);
}

int main(int argc, char **argv)
{
	char *small = NULL;
	char *big = NULL;
	int ret;

	assert(argv[1] != NULL && argv[2] != NULL);

	if ((ret = strlencmp(argv[1], argv[2], &small, &big)) == -1) {
		printf("False\n");
		return (0);
	}

	/*
	 * If they are equal in length then it really doesn't matter which one
	 * is declared as the larger or the smaller.
	 */
	if (ret == 0) {
		small = argv[1];
		big = argv[2];
	}

	printf("%s\n", one_away(small, big, ret == 0) ? "True" : "False");
	return (0);
}
