#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "tree.h"


void
list_of_depths_helper(node_t *pn, node_t **lists, int depth)
{
	if (pn == NULL)
		return;

	pn->next = lists[depth];
	lists[depth] = pn;

	list_of_depths_helper(pn->left, lists, depth + 1);
	list_of_depths_helper(pn->right, lists, depth + 1);
}

void
list_of_depths(tree_t *pt, node_t **lists)
{

	assert(pt != NULL && lists != NULL);

	list_of_depths_helper(pt->root, lists, 0);
}

void
print_list(node_t *pn)
{
	node_t *tmp;

	assert(pn != NULL);

	for (; pn != NULL; pn = pn->next)
		printf("%d ", pn->val);

	printf("\n");

}

void
print_lists(node_t **array, int len)
{
	int i;
	assert(array != NULL);

	for (i = 0; i < len; i++)
		print_list(array[i]);

}

int main(int argc, char **argv)
{
	int elems, i;
	tree_t tree;
	int height;
	node_t **array;

	assert(argc == 2);

	elems = atoi(argv[1]);
	(void) bzero(&tree, sizeof (tree_t));

	for (i = 0; i < elems; i++)
		tree_insert(&tree, i);

	tree_print(&tree);

	height = tree_get_height(tree.root);

	if ((array = malloc(sizeof (node_t *) * height)) == NULL) {
		printf("Memory allocation failure!\n");
		return (-1);
	}

	(void) bzero(array, sizeof (node_t *) * height);
	list_of_depths(&tree, array);
	print_lists(array, height);

	return (0);
}
