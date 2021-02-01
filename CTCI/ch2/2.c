#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "../util/linkedlist.h"


node_t *
get_kth(linked_list_t *pl, int k)
{
	node_t *pn1;
	node_t *pn2;
	int len;
	int i;

	if (ll_length(pl) <= k)
		return (NULL);

	pn1 = pn2 = pl->head;

	for (i = 0; i < k; i++)
		pn1 = pn1->next;

	while (pn1->next != NULL) {
		pn1 = pn1->next;
		pn2 = pn2->next;
	}

	return (pn2);
}

int main(int argc, char **argv)
{
	int i;
	int len;
	int k;
	node_t *pn;
	linked_list_t *mylist;

	assert(argc == 3);

	len = atoi(argv[1]);
	k = atoi(argv[2]);

	/*
	 * Supplying `false' as the second argument will result in random
	 * values being inserted in to the list as opposed to an ordered set.
	 */
	mylist = ll_create(len, false);
	ll_print(mylist);

	if ((pn = get_kth(mylist, k)) == NULL) {
		printf("Not enough elements for that.\n");
		return (0);
	}
	
	printf("The kth element from the end is: %d\n", pn->val);
	return (0);
}
