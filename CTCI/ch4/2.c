#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "tree.h"


void
array_print(int *array, int len)
{
	int i;	

	assert(array != NULL);

	for (i = 0; i < len; i++)
		printf("%d ", array[i]);

	printf("\n");
}

/*
 * Helper function for `array_tree_print()'.
 */  
static void
print_node(int *tree, int n, int level, int len)
{
	int i;
	int left = 2 * n + 1;
	int right = 2 * n + 2;

	assert(tree != NULL);

	if (n >= len)
		return;

	print_node(tree, right, level + 1, len);

	for (i = 0; i < level; i++)
		printf("   ");
	printf("%d\n", tree[n]);
	
	print_node(tree, left, level + 1, len);
}

/*
 * Given an array, print it as if it were a tree.  That is, the root node is
 * at index 0 and its left and right children are at 2n + 1 and 2n + 2.
 */
void
array_tree_print(int *tree, int len)
{
	int left, right;

	assert(tree != NULL);

	print_node(tree, 0, 0, len);	
}

/*
 * Given an array of sorted numbers, turn them in to a BST.
 */
void
array_to_tree_array(int *array, int *tree, int left, int right, int child)
{
	int middle;

	if (left > right)
		return;

	middle = (left + right) / 2;

	tree[child] = array[middle];
	array_to_tree_array(array, tree, left, middle - 1, (child * 2) + 1);
	array_to_tree_array(array, tree, middle + 1, right, (child * 2) + 2);	
}

static void
array_to_tree_helper(int *array, int left, int right, node_t **root)
{
	node_t *pn;
	int middle;

	if (left > right)
		return;

	middle = (left + right) / 2;

	pn = node_alloc(array[middle]);
	assert(pn != NULL);

	*root = pn;

	array_to_tree_helper(array, left, middle - 1, &pn->left);
	array_to_tree_helper(array, middle + 1, right, &pn->right);
}

void
array_to_tree(int *array, int left, int right, tree_t *pt)
{
	assert(array != NULL && pt != NULL);

	if (left > right)
		return;

	array_to_tree_helper(array, left, right, &pt->root);
}

int main(int argc, char **argv)
{
	int len, i;
	int *array;
	int *tree_array;
	tree_t tree;

	assert(argc == 2);

	len = atoi(argv[1]);

	(void) bzero(&tree, sizeof (tree_t));

	if ((array = malloc(sizeof (int) * len)) == NULL) {
		printf("Array allocation failed!\n");
		return (-1);
	}

	tree_array = malloc(sizeof (int) * len);
	
	for (i = 0; i < len; i++)
		array[i] = i;

	array_to_tree_array(array, tree_array, 0, len - 1, 0);
	array_print(array, len);
	array_print(tree_array, len);
	array_tree_print(tree_array, len);

	array_to_tree(array, 0, len - 1, &tree);
	tree_print(&tree);

	return (0);
}
