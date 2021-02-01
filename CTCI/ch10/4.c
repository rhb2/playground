#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>


typedef struct listy {
	int *data;	/* Storage for numbers (in sorted order). */
	int capacity;	/* Can not be directly accessed by the caller. */
} listy_t;

listy_t *listy_create(int);
int listy_get(listy_t *, int);

listy_t *
listy_create(int capacity)
{
	int i;
	listy_t *lp;

	if ((lp = malloc(sizeof (listy_t))) == NULL)
		return (NULL);

	(void) bzero(lp, sizeof (listy_t));

	if ((lp->data = malloc(sizeof (int) * capacity)) == NULL) {
		free(lp);
		return (NULL);
	}

	lp->capacity = capacity;

	for (i = 0; i < capacity; i++)
		lp->data[i] = i;

	return (lp);
}

/*
 * While I'm not 100% sure, I think this is the O(1) method that the problem
 * is describing.  It's not doing any searching, just returning a value if
 * it's located at a legitimate index, otherwise -1 if the caller-supplied
 * index is beyond the bounds of the array.
 */
int
listy_get_impl(listy_t *lp, int index)
{
	assert(lp != NULL);

	if (index >= lp->capacity || index < 0)
		return (-1);

	return (lp->data[index]);
}

/*
 * Isolate the logic for number comparison so that it doesn't make our
 * algorithm for binary search appear overly complicated.  Often times with
 * problems like these, the best approach is to keep functionality simple,
 * concise, clean, and with a single purpose.
 */
bool
lte(int x, int y)
{
	if (x >= 0 && y == -1)
		return (true);

	if (x == -1 && y >= 0)
		return (false);

	return (x <= y);
}

/*
 * Returns a value that is the first power of 2 greather than the actual
 * length of the list.
 */
int
listy_get_size(listy_t *lp)
{
	int i = 1;

	while (listy_get_impl(lp, i) != -1)
		i <<= 1;

	return (i);
}

int
binary_search_impl(listy_t *lp, int left, int right, int val)
{
	int middle;

	if (left == right)
		return (lp->data[left] == val ? left : -1);

	middle = (left + right) / 2;

	if (lte(val, listy_get_impl(lp, middle)))
		return (binary_search_impl(lp, left, middle, val));
	else
		return (binary_search_impl(lp, middle + 1, right,val));
}

int
binary_search(listy_t *lp, int val)
{
	int len;

	assert(lp != NULL && val >= 0);

	len = listy_get_size(lp);
	
	return (binary_search_impl(lp, 0, len, val));
}

void
test_listy(listy_t *lp, int elems)
{
	int val;
	int index;

	for (val = 0; val < elems; val++) {
		index = binary_search(lp, val);
		if (index >= 0)
			printf("%d is located at index: %d\n", val, index);
		else
			printf("%d was not found.\n", val);
	}
}

int main(int argc, char **argv)
{
	listy_t *lp;
	int capacity;

	assert(argc == 2);

	capacity = atoi(argv[1]);
	lp = listy_create(capacity);

	assert(lp != NULL);

	test_listy(lp, capacity * 2);

	return (0);
}
