#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "lstack.h"
#include "lqueue.h"


int main(int argc, char **argv)
{
	int i, elem, elems;
	lstack_t mystack;
	lqueue_t myqueue;

	assert(argc == 2);

	elems = atoi(argv[1]);

	lstack_init(&mystack);
	lqueue_init(&myqueue);

	for (i = 0; i < elems; i++) {
		(void) lstack_push(&mystack, i);
		(void) lqueue_insert(&myqueue, i);
	}

	lstack_print(&mystack);
	while (lstack_pop(&mystack, &elem)) {
		printf("Just popped: %d\n", elem);
		lstack_print(&mystack);
		ll_print_stats(&mystack.list);
		printf("\n");
	}


	lqueue_print(&myqueue);
	while (lqueue_remove(&myqueue, &elem)) {
		printf("Just removed: %d\n", elem);
		lqueue_print(&myqueue);
		ll_print_stats(&myqueue.list);
		printf("\n");
	}

	return (0);
}
