#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>


void
array_print(char **array, int len)
{
	int i;

	for (i = 0; i < len; i++)
		printf("%s\n", array[i]);
}

void
swap(char **array, int x, int y)
{
	char *tmp = array[x];
	array[x] = array[y];
	array[y] = tmp;
}

/*
 * Given two strings, confirm whether or not they are anagrams.  Two strings
 * are considered to be anagrams if one can be rearranged to equal another.
 */
bool
anagram(char *a, char *b)
{
	int i;
	int len;
	int map[128]; /* A bitmap can be used to conserve storage. */

	assert(a != NULL && b != NULL);

	len = strlen(a);

	if (strlen(b) != len)
		return (false);

	(void) bzero(map, sizeof (map));

	for (i = 0; i < len; i++)
		map[a[i]]++;

	for (i = 0; i < len; i++)
		map[b[i]]--;

	for (i = 0; i < 128; i++)
		if (map[i] != 0)
			return (false);

	return (true);
}

/*
 * This is a variation of the quicksort algorithm where I created a custom
 * comparator which simply tests two given elements to see if they are
 * anagrams.  If they are, then they will essentially be deemed as equal and
 * end up next to each other during the process of sorting.
 */
void
group_anagrams(char **array, int left, int right)
{
	int i, last;

	if (left >= right)
		return;

	swap(array, left, (left + right) / 2);
	last = left;

	for (i = left + 1; i <= right; i++)
		if (anagram(array[i], array[left]))
			swap(array, ++last, i);

	swap(array, left, last);
	group_anagrams(array, left, last - 1);
	group_anagrams(array, last + 1, right);
}

int main(int argc, char **argv)
{
	int i;
	int len;
	char **array = malloc(sizeof (char *) * 7);

	array[0] = "wall-e";
	array[1] = "loves";
	array[2] = "food";
	array[3] = "e-wall";
	array[4] = "slove";
	array[5] = "dofo";
	array[6] = "-llawe";

	array_print(array, 7);
	printf("\n");

	group_anagrams(array, 0, 7 - 1);
	array_print(array, 7);
	return (0);
}
