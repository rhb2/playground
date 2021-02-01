#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "tree.h"


void
update_sums(int *array, int depth, int val, int sign)
{
	int i;
	int amount;

	assert(array != NULL);
	assert(sign == -1 || sign == 1);

	amount = val * sign;

	for (i = 0; i <= depth; i++)
		array[i] += amount;
}

int
count_sums(int *array, int sum, int depth)
{
	int i;
	int count = 0;

	assert(array != NULL);

	for (i = 0; i <= depth; i++) {
		if (array[i] == sum)
			count++;
	}

	return (count);
}

void
paths_to_sum_helper(node_t *pn, int sum, int *array, int depth, int *count)
{
	int total;

	assert(array != NULL);

	if (pn == NULL)
		return;

	update_sums(array, depth, pn->val, 1);

	total = count_sums(array, sum, depth);
	*count = *count + total;

	paths_to_sum_helper(pn->left, sum, array, depth + 1, count);
	paths_to_sum_helper(pn->right, sum, array, depth + 1, count);

	/*
	 * Undo our counts before we move back up the stack and go in another
	 * direction.
	 */
	update_sums(array, depth, pn->val, -1);
} 

void
paths_to_sum(tree_t *pt, int sum)
{
	int longest_path;
	int count = 0;
	int *array;

	assert(pt != NULL);

	if ((longest_path = tree_get_height(pt->root)) == 0)
		return;

	array = malloc(sizeof (int) * longest_path);
	assert(array != NULL);

	(void) bzero(array, sizeof (int) * longest_path);
	paths_to_sum_helper(pt->root, sum, array, 0, &count);
	printf("Total number of paths that sum to %d: %d\n", sum, count);
	free(array);
}


int main(int argc, char **argv)
{
	int elems, i, sum;
	tree_t tree;

	assert(argc == 3);

	elems = atoi(argv[1]);
	sum = atoi(argv[2]);
	(void) bzero(&tree, sizeof (tree_t));

	/*
	 * Note: If you want to build an unbalanced tree quickly, go over to
	 * tree.h and comment out the line the performs the balance upon insert.
	 */
	for (i = 0; i < elems; i++)
		tree_insert(&tree, i);

	tree_print(&tree);
	paths_to_sum(&tree, sum);

	return (0);
}
