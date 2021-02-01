#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>


void
array_print(int *array, int len)
{
	int i;

	for (i = 0; i < len; i++)
		printf("%d ", array[i]);

	printf("\n");
}

void
swap(int *array, int x, int y)
{
	array[x] = (array[x] + array[y]) - (array[y] = array[x]);
}

void
quicksort(int *array, int left, int right)
{
	int i, last;

	if (left >= right)
		return;

	swap(array, left, (left + right) / 2);
	last = left;

	for (i = left + 1; i <= right; i++)
		if (array[i] < array[left])
			swap(array, ++last, i);

	swap(array, left, last);
	quicksort(array, left, last - 1);
	quicksort(array, last + 1, right);
}

/*
 * Take two arrays of different size, `a' is presumbed to have enough storage
 * to hold both its own contents and that of `b', where all extra storage in
 * `a' is at the end, merge `b' in to `a'.
 * Note: While not absolutely necessary, I created a second pointer to `a' which
 * is referred to as `result'.  This was done only to improve clarity,
 * especially in the case where we are copying an element from `a' to itself.
 */
void
merge_sorted(int *a, int *b, int len)
{
	int a_pos = len - 1;
	int b_pos = a_pos;
	int *result = a;
	int r_pos = 2 * len - 1;

	assert(a != NULL && b != NULL);

	/*
	 * The heuristic is similar to that of the merge component in
	 * mergesort, except instead of starting at the front of the two
	 * arrays, we start at the back.  We continue merging these two
	 * until we have made it through all of the elements of one, at
	 * which point, the expression driving the loop will no longer
	 * evaluate to true and we will break.
	 */
	while (a_pos >= 0 && b_pos >= 0) {
		if (a[a_pos] >= b[b_pos])
			result[r_pos--] = a[a_pos--];
		else
			result[r_pos--] = b[b_pos--];
	}

	/*
	 * At this point, the state of affairs is that we've finished
	 * processing one of the two arrays.  We don't know which of the two
	 * is done and we don't much care.  If there is nothing left but
	 * elements in `b', then we copy them in now without worrying about
	 * anything remaining from `a'.  If it's the case that we've finished
	 * all elements from `b' then the below loop won't even run and there
	 * is no need to worry about the elements in `a' at that point because
	 * they were there before we entered this function.  We're done.
	 */
	while (b_pos >= 0)
		result[r_pos--] = b[b_pos--];
}

int main(int argc, char **argv)
{
	int i;
	int len;
	int *a;
	int *b;

	assert(argc == 2);

	len = atoi(argv[1]);

	a = malloc(sizeof (int) *(len) * 2);
	assert(a != NULL);

	b = malloc(sizeof (int) * len);
	assert(b != NULL);

	for (i = 0; i < len; i++)
		a[i] = rand() % (len * 3);

	for (i = 0; i < len; i++)
		b[i] = rand() % (len * 3);

	quicksort(a, 0, len - 1);
	quicksort(b, 0, len - 1);

	array_print(a, len);
	array_print(b, len);

	merge_sorted(a, b, len);

	array_print(a, len * 2);
	return (0);
}
