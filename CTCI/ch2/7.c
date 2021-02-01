#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "../util/linkedlist.h"

node_t *
intersection(linked_list_t *pl1, linked_list_t *pl2)
{
	int len1, len2;
	node_t *pn1;
	node_t *pn2;

	assert(pl1 != NULL && pl2 != NULL);

	len1 = ll_length(pl1);
	len2 = ll_length(pl2);

	pn1 = pl1->head;
	pn2 = pl2->head;

	if (len1 > len2)
		pn1 = node_step(pn1, len1 - len2);

	if (len2 > len1)
		pn2 = node_step(pn2, len2 - len1);

	while (pn1 != NULL) {
		if (pn1 == pn2)
			return (pn1);

		pn1 = node_step(pn1, 1);
		pn2 = node_step(pn2, 1);
	}

	return (NULL);
}

int main(int argc, char **argv)
{
	int len1;
	int len2;
	linked_list_t *pl1;
	linked_list_t *pl2;
	node_t *tail;
	linked_list_t *common;
	node_t *pn;

	assert(argc == 3);

	len1 = atoi(argv[1]);
	len2 = atoi(argv[2]);

	pl1 = ll_create(len1, false);
	pl2 = ll_create(len2, false);
	common = ll_create(5, true);

	assert(pl1 != NULL && pl2 != NULL && common != NULL);

	/*
	 * Point the tail of both lists at the head of common.
	 */
	tail = ll_tail(pl1);
	tail->next = common->head;

	tail = ll_tail(pl2);
	tail->next = common->head;

	if ((pn = intersection(pl1, pl2)) != NULL) {
		printf("They intersect at %d\n", pn->val);
	}

	ll_print(pl1);
	ll_print(pl2);
	ll_print(common);

	return (0);
}
