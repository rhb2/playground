#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>


#define	ABS(x)	((x) < 0 ? ((x) * -1) : (x))

/*
 * Comparator for two strings -- phone book order.
 */
bool
strlt(char *str1, char *str2)
{
	int i, len;
	int len1, len2;

	assert(str1 != NULL && str2 != NULL);

	len1 = strlen(str1);
	len2 = strlen(str2);
	len = len1 < len2 ? len1 : len2;

	for (i = 0; i < len; i++) {
		if (str1[i] < str2[i])
			return (true);

		if (str1[i] > str2[i])
			return (false); 
	}

	return (len1 < len2);
}

/*
 * Given an array of strings, start at the mid point and scan outwards until
 * a non-NULL string is found.  Return the index of the first one found.  If
 * none are found, return -1.
 */
int
scan_for_non_null(char **strings, int left, int right)
{
	int middle;
	int l_pos, r_pos;

	assert(strings != NULL);

	l_pos = r_pos = middle = (left + right) / 2;

	/*
	 * Start at the center of the string and work our way outwards.  One
	 * very important observation is that both `l_pos' and `r_pos' are
	 * the exact same distance from the center when this function ends.
	 * So, if you need to obtain the value for the one that is _not_
	 * returned from this function, it can easily be done by calculating
	 * the distance between the center and the one that does get returned.
	 */
	while (l_pos >= left && r_pos <= right) {
		if (strlen(strings[l_pos]) > 0)
			return (l_pos);

		if (strlen(strings[r_pos]) > 0)
			return (r_pos);

		l_pos--;
		r_pos++;
	}
	return (-1);
}

/*
 * Binary search an array of strings for a match with the one supplied by the
 * caller (`str').
 */
int
binsearch(char **strings, char *str, int left, int right)
{
	int i;
	int delta, middle;

	assert(strings != NULL);

	for (;;) {
		if (left >= right)
			break;

		middle = (left + right) / 2;

		if ((i = scan_for_non_null(strings, left, right)) == -1)
			break;

		if (strcmp(str, strings[i]) == 0)
			return (i);

		delta = ABS(middle - i);

		/*
		 * As discussed in the function above, we may need to calculate
		 * the value of the index that was not returned.  In the case
		 * where where the index returned was on the right side of the
		 * array, but our current string is less than the one found,
		 * we want to set `right' to whatever the left offset was in
		 * the function before returning.  Why?  Because already know
		 * that everything from the middle to that index is an empty
		 * string, so why repeat work that has already been done?
		 * Likewise, if the first non empty string that was discovered
		 * was on the left side of the array, and it is the case that
		 * the first non empty string that was discovered was on the
		 * left half of the array is _less_ than the one that we are
		 * searching for, then we need to go right, but we can skip
		 * over everything that has already been scanned.  That is,
		 * we can resume our search by advancing `left' to the right
		 * by setting its new value to be `middle + delta'.
		 */
		if (strlt(str, strings[i]))
			right = (i > middle) ? middle - delta : i - 1;
		else
			left = (i < middle) ? middle + delta : i + 1;
	}

	return (-1);
}

void
test_binsearch(char **strings, char *str, int len)
{
	int i;

	assert(strings != NULL && str != NULL);

	if ((i = binsearch(strings, str, 0, len)) >= 0)
		printf("%s is located at index: %d\n", str, i);
	else
		printf("%s is not present in the string array.\n", str);
}

int main(int argc, char **argv)
{
	int i;
	char *array[] = {
	    "at", "", "", "", "ball", "", "", "car", "", "", "dad", ""};
	int len = (sizeof (array) / sizeof (array[0])) - 1;

	test_binsearch(array, "at", len);
	test_binsearch(array, "ball", len);
	test_binsearch(array, "car", len);
	test_binsearch(array, "dad", len);
	test_binsearch(array, "moctcmoproblems", len);
	return (0);
}
