#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "../util/linkedlist.h"


int main(int argc, char **argv)
{
	int i;
	int len;
	node_t *pn;
	linked_list_t *mylist;

	assert(argc == 2);

	len = atoi(argv[1]);
	assert(len >= 3);

	mylist = ll_create(len, true);
	ll_print(mylist);

	for (i = 1; i < len - 1; i++) {
		(void) ll_remove(mylist, i, &pn);
		printf("Removed %d\n", pn->val);
		ll_print(mylist);
	}

	return (0);
}
