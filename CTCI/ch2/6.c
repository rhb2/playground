#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "../util/linkedlist.h"


bool
is_palindrome(linked_list_t *pl)
{
	int i, len;
	linked_list_t tmp;
	node_t *pn1;
	node_t *pn2;
	bool ret = true;

	(void) bzero(&tmp, sizeof (linked_list_t));

	assert(pl != NULL);

	
	len = ll_length(pl);

	if (len == 0 || len == 1)
		return (true);

	for (i = 0; i < len / 2; i++) {
		node_t *pn;
		(void) ll_remove_head(pl, &pn);
		ll_insert(&tmp, pn);
	}

	pn1 = len % 2 ? pl->head->next : pl->head;
	pn2 = tmp.head;

	while (pn1 != NULL) {
		if (pn1->val != pn2->val) {
			ret = false;
			break;
		}

		pn1 = node_step(pn1, 1);
		pn2 = node_step(pn2, 1);
	}

	/* Put the list back together. */
	for (i = 0; i < len / 2; i++) {
		node_t *pn;
		(void) ll_remove_head(&tmp, &pn);
		ll_insert(pl, pn);
	}

	return (ret);	
}

int main(int argc, char **argv)
{
	int i;
	linked_list_t *mylist;

	mylist = ll_create(0, true);

	for (i = 0; i < 5; i++)
		ll_insert_int(mylist, i);

	for (i = 3; i >= 0; i--)
		ll_insert_int(mylist, i);

	ll_print(mylist);

	if (is_palindrome(mylist))
		printf("It is a palindrome.\n");

	return (0);
}
