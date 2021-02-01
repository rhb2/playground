#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "../util/linkedlist.h"


int main(int argc, char **argv)
{
	int i;
	int len;
	node_t *pn;
	linked_list_t mylist;
	linked_list_t ordered_list;

	assert(argc == 2);

	len = atoi(argv[1]);
	(void) bzero(&mylist, sizeof (linked_list_t));
	(void) bzero(&ordered_list, sizeof (linked_list_t));

	for (i = 0; i < len; i++) {
		pn = node_alloc(rand() % (len / 2));

		assert(pn != NULL);

		ll_insert(&mylist, pn);
	}

	ll_print(&mylist);

	while (ll_remove_head(&mylist, &pn)) {
		/*
		 * Perform an ordered insert on the linked list.  The third
		 * argument supplied, being set to `true' states that we only
		 * want to allow the addition of unique elements in to the list.
		 * If we observe that an insert failed, that means that it is
		 * not unique.  We should free the memory of the duplicate node
		 * in that case.
		 */
		if (!ll_insert_ordered(&ordered_list, pn, true))
			free(pn);
	}

	ll_print(&ordered_list);
	
	return (0);
}
