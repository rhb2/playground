#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "../util/lstack.h"


void
print_stacks(lstack_t *stacks, int len)
{
	int i;

	assert(stacks != NULL);

	for (i = 0; i < len; i++) {
		printf("Stack %d:  ", i);
		lstack_print_reverse(&stacks[i]);
		printf("\n");
	}
	printf("\n\n");
}

void
move_top_from_to(lstack_t *stacks, int from, int to)
{
	int elem;
	lstack_t *src = &stacks[from];
	lstack_t *dst = &stacks[to];

	assert(src != NULL && dst != NULL);

	(void) lstack_pop(src, &elem);
	(void) lstack_push(dst, elem);	
}

void
move_disks(int disks, lstack_t *stacks, int src, int dst, int buffer)
{
	if (disks <= 0)
		return;

	print_stacks(stacks, 3);
	move_disks(disks - 1, stacks, src, buffer, dst);

	move_top_from_to(stacks, src, dst);

	move_disks(disks - 1, stacks, buffer, dst, src);
}

int main(int argc, char **argv)
{
	int i;
	int disks;
	lstack_t stacks[3];
	(void) bzero(stacks, sizeof (stacks));

	assert(argc == 2);

	disks = atoi(argv[1]);

	for (i = 0; i < disks; i++)
		lstack_push(&stacks[0], disks - i);

	print_stacks(stacks, 3);

	move_disks(disks, stacks, 0, 2, 1);

	print_stacks(stacks, 3);
	return (0);
}
