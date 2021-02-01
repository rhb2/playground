#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "../util/linkedlist.h"


/*
 * Introduce a loop to the linked list by assigning the next pointer of the
 * tail node to be the address of some node in the middle of the list.
 */
void
corrupt_list(linked_list_t *pl)
{
	int len;
	node_t *midpoint;
	node_t *tail;

	assert(pl != NULL);

	len = ll_length(pl);
	midpoint = node_step(pl->head, len / 2);
	printf("Loop starts at %d\n", midpoint->val);
	tail = ll_tail(pl);
	tail->next = midpoint;
}

node_t *
find_loop(linked_list_t *pl)
{
	node_t *pn;
	node_t *runner;

	assert(pl != NULL);

	pn = runner = pl->head;

	/*
	 * This loop will end one way or another.  Either we will find the end
	 * of the list, or we will detect the loop.
	 */
	for (;;) {
		pn = node_step(pn, 1);
		runner = node_step(runner, 2);

		if (runner == NULL)
			return (NULL);

		if (runner == pn)
			break;
	}

	/*
	 * If you reset pn to be at the head of the list, both the runner and
	 * pn are both the same distance from the loop.
	 */
	pn = pl->head;

	for (;;) {
		if (pn == runner)
			return (pn);

		pn = node_step(pn, 1);
		runner = node_step(runner, 1);		
	}
}

int main(int argc, char **argv)
{
	int len;
	node_t *pn;
	linked_list_t *mylist;

	assert(argc == 2);

	len = atoi(argv[1]);

	mylist = ll_create(len, true);
	ll_print(mylist);

	corrupt_list(mylist);
	pn = find_loop(mylist);
	node_print(pn);
	
	return (0);
}
