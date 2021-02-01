#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "../util/lstack.h"


void
stack_spill_until(lstack_t *dst, lstack_t *src, int num)
{
	int elem;

	for (;;) {
		/*
		 * If the source source stack is empty, or the top of the stack
		 * is a number smaller than `elem', then break.
		 */
		if (!lstack_peek(src, &elem) || num >= elem)
			break;

		(void) lstack_pop(src, &elem);
		(void) lstack_push(dst, elem);
	}
}

void
stack_sort(lstack_t *sp)
{
	int elem;
	lstack_t minstack;

	assert(sp != NULL);

	lstack_init(&minstack);

	for (;;) {
		if (!lstack_pop(sp, &elem))
			break;

		stack_spill_until(sp, &minstack, elem);
		(void) lstack_push(&minstack, elem);
	}

	/*
	 * Spill the contents of `minstack' back in to the caller-supplied
	 * stack (which should be completely empty at this point.  This will
	 * achieve the desired effect of a stack that has the smallest items
	 * on top and the largest at the bottom.
	 */
	while (!lstack_empty(&minstack)) {
		(void) lstack_pop(&minstack, &elem);
		(void) lstack_push(sp, elem);
	}
}

int main(int argc, char **argv)
{
	int i, elems;
	lstack_t stack;

	assert(argc == 2);

	lstack_init(&stack);
	elems = atoi(argv[1]);

	for (i = 0; i < elems; i++)
		(void) lstack_push(&stack, rand() % (elems * 3));

	lstack_print(&stack);

	stack_sort(&stack);
	lstack_print(&stack);

	return (0);
}
