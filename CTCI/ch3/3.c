#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "../util/lstack.h"


#define	STACKSET_DEFAULT	20 /* A stackset can have up to 20 stacks. */
#define	STACKSET_STACK_LIMIT	3  /* Each stack can hold 3 elements. */ 

typedef struct stackset {
	lstack_t **stacks;	/* Storage for stack pointers. */
	int stack_limit;	/* Max elements allowed per stack. */
	int stack_count;	/* Total number of stacks. */
	int capacity;		/* Total allowable number of stacks */
} stackset_t;

bool stackset_init(stackset_t *);
bool stackset_push(stackset_t *, int);
bool stackset_pop(stackset_t *, int *);
bool stackset_pop_at(stackset_t *, int, int *);
bool stackset_empty(stackset_t *);
void stackset_print(stackset_t *);

bool
stackset_init(stackset_t *ssp)
{
	lstack_t **stacks;

	assert(ssp != NULL);

	(void) bzero(ssp, sizeof (stackset_t));

	if ((stacks = malloc(sizeof (lstack_t *) * STACKSET_DEFAULT)) == NULL)
		return(false);

	(void) bzero(stacks, sizeof (lstack_t *) * STACKSET_DEFAULT);
	ssp->stacks = stacks;
	ssp->stack_limit = STACKSET_STACK_LIMIT;
	ssp->capacity = STACKSET_DEFAULT;
	return (true);
}

/*
 * Call this if we have reached our capacity.  This will double it or die
 * trying.
 */
bool
stackset_expand_capacity(stackset_t *ssp)
{
	lstack_t **stacks;

	assert(ssp != NULL);

	printf("Attempt to Expand capacity from %d to %d.\n", ssp->capacity,
	    2 * ssp->capacity);

	if ((stacks = malloc(sizeof (lstack_t *) * 2 * ssp->capacity)) == NULL)
		return (false);

	(void) bzero(stacks, sizeof (lstack_t *) * 2 * ssp->capacity);
	(void) memcpy(stacks, ssp->stacks, sizeof (lstack_t *) * ssp->capacity);
	free(ssp->stacks);
	ssp->stacks = stacks;
	ssp->capacity = ssp->capacity * 2;
	return (true);
}

bool
stackset_push(stackset_t *ssp, int elem)
{
	int stacknum;
	lstack_t *lsp;

	assert(ssp != NULL);

	stacknum = ssp->stack_count;

	/*
	 * If we have reached capacity and we fail to allocate more, then we
	 * are done, unfortunately.  Fail the operation.
	 */
	if (stacknum == ssp->capacity && !stackset_expand_capacity(ssp))
		return (false);

	lsp = ssp->stacks[stacknum];

	if (lsp == NULL) {
		lsp = malloc(sizeof (lstack_t));
		if (lsp == NULL)
			return false;

		lstack_init(lsp);
		ssp->stacks[stacknum] = lsp;
	}

	(void) lstack_push(lsp, elem);

	if (lstack_size(lsp) == STACKSET_STACK_LIMIT)
		ssp->stack_count++;

	return (true);
}

/*
 * Pop the most recently added element from the stackset.  Note, this can
 * probably become a wrapper for `stackset_pop_at()', but this function was
 * written first.  It will remain here for educational purposes, but for what
 * it's worth, the same result can be achieved simply by calling:
 *
 * stackset_pop_at(ssp, ssp->stack_count, &elem);
 */
bool
stackset_pop(stackset_t *ssp, int *elem)
{
	lstack_t *lsp;

	assert(ssp != NULL && elem != NULL);

	if (stackset_empty(ssp))
		return (false);

	/*
	 * If we are in a state where we just finished filling up the stack
	 * before us, then we should be pointing at a location which is NULL.
	 * In that case, rewind to the stack before us and pop from that.
	 */
	if ((lsp = ssp->stacks[ssp->stack_count]) == NULL) {
		ssp->stack_count--;
		lsp = ssp->stacks[ssp->stack_count];
	}

	/*
	 * Whether we had to rewind or not, `lsp' is a stack that we can pop
	 * from and get something.
	 */
	(void) lstack_pop(lsp, elem);

	/*
	 * If we just emptied out the stack, then free whatever was there and
	 * set the pointer to NULL.
	 */
	if (lstack_empty(lsp)) {
		free(lsp);
		ssp->stacks[ssp->stack_count] = NULL;
	}

	return (true);
}

/*
 * Pop an element from a stack within the stackset.  If a particular stack is
 * emptied out as a result of this operation, we will free the underlying
 * structure itself and close up the hole in the array behind it.  A note of
 * caution: If this is performed frequently on various stacks without
 * completely emptying them, the result will (eventually) be that we will
 * have many more stacks than necessary.  At some point, it will be worth it
 * to consolidate our elements so that we have (at most) only one stack in
 * the set that has not reached capacity as opposed to the likely several.
 */
bool
stackset_pop_at(stackset_t *ssp, int index, int *elem)
{
	lstack_t *lsp;
	int remaining;

	assert(ssp != NULL && elem != NULL);
	assert(index < ssp->capacity);

	/* If the stackset is entirely empty, then return. */
	if (stackset_empty(ssp))
		return (false);

	/*
	 * If we were supplied with an index in the array that is within
	 * our capacity, but beyond the number of existing stacks, seek
	 * backwards until we find our newest stack.
	 */
	if ((lsp = ssp->stacks[index]) == NULL) {
		int tmp = index;

		while (lsp == NULL) {
			tmp--;
			lsp = ssp->stacks[tmp];
		}

		/* This is probably the trickest line in the whole program. */
		ssp->stack_count = tmp;
	}

	/*
	 * This can't fail since we have a stack within the set that is not
	 * empty.
	 */
	(void) lstack_pop(lsp, elem);

	/*
	 * If the stack that we just popped from still is not empty, then
	 * we are free to return.
	 */
	if (!lstack_empty(lsp))
		return (true);

	/*
	 * If this happened to be either the youngest stack in the set or
	 * the only stack in the set, then just free the underlying structure
	 * and nullify its entry in the array.  No * additional book keeping is
	 * necessary.
	 */
	if (ssp->stack_count == 0 || lsp == ssp->stacks[ssp->stack_count]) {
		free(lsp);
		ssp->stacks[ssp->stack_count] = NULL;
		return (true);
	}

	/*
	 * On the other hand, if the stack is empty, then we need to perform
	 * a little book keeping by removing it from our stackset and shifting
	 * everything to the right of it left by one.
	 */
	remaining = ssp->stack_count - index;
	(void) memmove(&ssp->stacks[index], &ssp->stacks[index + 1],
	    remaining * sizeof (lstack_t *));

	free(lsp);
	ssp->stacks[ssp->stack_count] = NULL;
	ssp->stack_count--;

	return (true);
}

bool
stackset_empty(stackset_t *ssp)
{
	assert(ssp != NULL);

	/*
	 * If there is anything in the stackset at all, ever, then the
	 * first index (i.e. ssp->stacks[0]) will never be NULL.
	 */
	return (ssp->stacks[0] == NULL);
}

void
stackset_print(stackset_t *ssp)
{
	int i;
	lstack_t *lsp;

	assert(ssp != NULL);

	if (stackset_empty(ssp))
		return;

	for (i = 0; i <= ssp->stack_count; i++) {
		if ((lsp = ssp->stacks[i]) != NULL)
			lstack_print(lsp);
	}
}

int main(int argc, char **argv)
{
	int i, elem, elems;
	stackset_t stackset1, stackset2;
	bool init;

	assert(argc == 2);

	elems = atoi(argv[1]);

	init = stackset_init(&stackset1);
	init &= stackset_init(&stackset2);

	assert(init == true);

	for (i = 0; i < elems; i++) {
		stackset_push(&stackset1, i);
		stackset_push(&stackset2, i);
	}

	printf("Stack Set 1:\n");
	stackset_print(&stackset1);
	printf("\n");

	printf("Stack Set 2:\n");
	stackset_print(&stackset2);
	printf("\n");

	/* Test `stackset_pop()'. */
	while (stackset_pop(&stackset1, &elem)) {
		printf("Stack Set 1: just popped: %d\n", elem);
		stackset_print(&stackset1);
		printf("\n");
	}

	printf("\n");

	/* Test `stackset_pop_at()'. */
	while (stackset_pop_at(&stackset2, stackset2.stack_count, &elem)) {
		printf("Stack Set 2: just popped: %d\n", elem);
		stackset_print(&stackset2);
		printf("\n");
	}

	return (0);
}
