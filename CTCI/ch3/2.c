#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "../util/lstack.h"


int main(int argc, char **argv)
{
	int i, n, elems;
	lstack_t mystack;
	lstack_t minstack;

	lstack_init(&mystack);
	lstack_init(&minstack);

	assert(argc == 2);

	elems = atoi(argv[1]);

	for (i = 0; i < elems; i++) {
		int tmp;
		n = rand() % (2 * elems);

		lstack_push(&mystack, n);

		/*
		 * If `minstack' is empty or we are observing a new all time
		 * low, push the element on to `minstack'.
		 */
		if (lstack_empty(&minstack) || 
		    (lstack_peek(&minstack, &tmp) && n <= tmp)) {
			lstack_push(&minstack, n);
		}
	}

	lstack_print(&mystack);
	lstack_peek(&minstack, &n);
	printf("The smallest element in the stack is: %d\n", n);

	while (lstack_pop(&mystack, &n)) {
		int tmp;

		(void) lstack_peek(&minstack, &tmp);

		/*
		 * If the item that we just popped off of our stack is equal
		 * to the current low (i.e. the item at the top of `minstack',
		 * pop it too.
		 */
		if (n == tmp)
			lstack_pop(&minstack, &tmp);

		if (!lstack_empty(&minstack)) {
			(void) lstack_peek(&minstack, &tmp);
			printf("\n");
			lstack_print(&mystack);
			printf("The smallest element in the stack is: %d\n",
			    tmp);
		}
	}

	return (0);
}
