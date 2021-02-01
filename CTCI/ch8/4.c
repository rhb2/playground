#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "../util/linkedlist.h"


void
powerset_impl(linked_list_t *pl, int val)
{
	linked_list_t *handle = NULL;
	linked_list_t *tmp;
	linked_list_t *tail;

	assert(pl != NULL);

	/* Clone all lists that we have so far. */
	for (tmp = pl; tmp != NULL; tmp = tmp->next) {
		linked_list_t *clone = ll_clone(tmp);

		assert(clone != NULL);

		clone->next = handle;
		handle = clone;

		/*
		 * Save the location of the last list.  We use it further
		 * down below.
		 */
		if (tmp->next == NULL)
			tail = tmp;
	}

	/*
	 * Roll through the new set of lists and add `val' to each of them.
	 */
	for (tmp = handle; tmp != NULL; tmp = tmp->next)
		(void) ll_insert_int(tmp, val);

	/*
	 * Finally, connect our new set of lists to the ones that were passed
	 * to us.
	 */
	tail->next = handle;
}

linked_list_t *
powerset(int *array, int len)
{
	int i;
	linked_list_t *pl;

	assert(array != NULL);

	pl = ll_alloc();

	assert(pl != NULL);

	for (i = 0; i < len; i++)
		powerset_impl(pl, array[i]);

	return (pl);
}

void
print_lists(linked_list_t *pl)
{
	linked_list_t *tmp;

	assert(pl != NULL);

	for (tmp = pl; tmp != NULL; tmp = tmp->next)
		ll_print(tmp);

	printf("\n");
}

int main(int argc, char **argv)
{
	int len, i;
	int *array;
	linked_list_t *list;

	assert(argc == 2);

	len = atoi(argv[1]);
	array = malloc(sizeof (int) * len);

	for (i = 0; i < len; i++)
		array[i] = i;

	list = powerset(array, len);
	print_lists(list);

	return (0);
}
