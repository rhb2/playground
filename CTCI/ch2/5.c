#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "../util/linkedlist.h"


linked_list_t *
string_to_list(char *num)
{
	int i;
	int len;
	node_t *pn;
	linked_list_t *pl;

	assert(num != NULL);

	len = strlen(num);

	if ((pl = malloc(sizeof (linked_list_t))) == NULL)
		return (NULL);

	(void) bzero(pl, sizeof (linked_list_t));

	for (i = len - 1; i >= 0; i--) {
		char digit[2];
		digit[0] = num[i];
		digit[1] = '\0';

		if ((pn = node_alloc(atoi(digit))) == NULL) {
			ll_destroy(pl);
			return (NULL);
		}

		ll_insert(pl, pn);
	}

	return (pl);
}

bool
add(int a, int b, int *sum, int *carry)
{
	assert(sum != NULL && carry != NULL);

	if (a >= 10 || b >= 10)
		return (false);

	*sum = (a + b + *carry) % 10;
	*carry = (a + b + *carry) / 10;
	return (true);
}

/*
 * This takes two lists and sums them together as if they were integers.  In
 * essence, we are creating an addition function where lists can have an
 * unspecified number of digits.  The problem originally presented asked what
 * we would do if the lists provided were reversed.  For us, the follow on
 * question is elementary because we have a function to reverse a linked list
 * already.
 */
linked_list_t *
sum_lists(linked_list_t *num1, linked_list_t *num2)
{
	int carry = 0;
	int sum;
	node_t *pn1;
	node_t *pn2;
	linked_list_t *result;

	assert(num1 != NULL && num2 != NULL);

	result = malloc(sizeof (linked_list_t));
	assert(result != NULL);
	(void) bzero(result, sizeof (linked_list_t));

	ll_reverse(num1);
	ll_reverse(num2);

	pn1 = num1->head;
	pn2 = num2->head;

	while (pn1 != NULL || pn2 != NULL) {
		int d1 = pn1 ? pn1->val : 0;
		int d2 = pn2 ? pn2->val : 0;

		if (!add(d1, d2, &sum, &carry))
			return (NULL);

		ll_insert_int(result, sum);

		pn1 = node_step(pn1, 1);
		pn2 = node_step(pn2, 1);

	}

	if (carry != 0)
		ll_insert_int(result, carry);

	return (result);
}

int main(int argc, char **argv)
{
	linked_list_t *num1;
	linked_list_t *num2;
	linked_list_t *sum;

	assert(argc == 3);

	num1 = string_to_list(argv[1]);
	num2 = string_to_list(argv[2]);

	sum = sum_lists(num1, num2);
	ll_print(sum);
	return (0);
}
