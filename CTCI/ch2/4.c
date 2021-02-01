#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "../util/linkedlist.h"


void
node_swap(node_t *p1, node_t *p2)
{
	int tmp;

	assert(p1 != NULL && p2 != NULL);

	tmp = p1->val;
	p1->val = p2->val;
	p2->val = tmp;
}

/*
 * Very similar to part of the quick sort algorithm.
 */
void
partition(linked_list_t *pl, int partition)
{
	node_t *pn;
	node_t *last;

	assert(pl != NULL);

	last = pl->head;

	for (pn = pl->head; pn != NULL; pn = pn->next) {
		/*
		 * Advance `pn' and `last' together as long as we have not
		 * yet seen an element that is greater than or equal to our
		 * partition.
		 */
		if (pn->val < partition && last == pn) {
			last = last->next;
			continue;
		}

		/*
		 * If we see an element which is less in value than that of
		 * the partition, and last != pn, that means that we have
		 * already passed over some elements that are greater than
		 * the partition.  Swap `pn' with the first known element that
		 * is greather than our partition.
		 */
		if (pn->val < partition && last != pn) {
			node_swap(pn, last);
			last = last->next;
		}
	}
}

int main(int argc, char **argv)
{
	int len;
	linked_list_t *mylist;

	assert(argc == 2);

	len = atoi(argv[1]);

	mylist = ll_create(len, false);
	ll_print(mylist);

	printf("Partition = %d\n", len / 2);

	/*
	 * Choose a partition that is about half the length of the list in
	 * value.  That should make it reasonably interesting.
	 */
	partition(mylist, len / 2);
	ll_print(mylist);
	return (0);
}
