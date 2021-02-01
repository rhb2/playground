#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "node.h"
#include "linkedlist.h"

typedef struct graph {
	int total;
	linked_list_t *nodes;
} graph_t;

graph_t *graph_create(int);
void graph_destroy(graph_t *);
void graph_print(graph_t *);
void graph_print_alpha(graph_t *gp);
bool graph_add_edge(graph_t *, int, int);
bool graph_add_edge_alpha(graph_t *, char, char);
bool graph_remove_edge(graph_t *, int, int);
bool graph_remove_edge_alpha(graph_t *, char, char);

graph_t *
graph_create(int total)
{
	graph_t *gp;

	if ((gp = malloc(sizeof (graph_t))) == NULL)
		return (NULL);

	(void) bzero(gp, sizeof (graph_t));

	if ((gp->nodes = malloc(sizeof (linked_list_t) * total)) == NULL) {
		free(gp);
		return (NULL);
	}

	gp->total = total;
	(void) bzero(gp->nodes, sizeof (linked_list_t) * total);
	return (gp);
}

void
graph_free_chain(node_t *pn)
{
	if (pn == NULL)
		return;

	graph_free_chain(pn->next);
	free(pn);
}

void
graph_destroy(graph_t *gp)
{
	int i;
	linked_list_t *lp;

	assert(gp != NULL && gp->nodes != NULL);

	for (i = 0; i < gp->total; i++) {
		lp = &gp->nodes[i];
		graph_free_chain(lp->head);
	}
}

void
graph_print(graph_t *gp)
{
	int i;
	linked_list_t *lp;

	assert(gp != NULL && gp->nodes != NULL);

	for (i = 0; i < gp->total; i++) {
		lp = &gp->nodes[i];
		printf("%d: ", i);
		ll_print(lp);
	}
}

void
graph_print_alpha(graph_t *gp)
{
	int i;
	node_t *pn;
	linked_list_t *lp;

	assert(gp != NULL && gp->nodes != NULL);

	for (i = 0; i < gp->total; i++) {
		lp = &gp->nodes[i];
		printf("%c: ", i + 'a');
		for (pn = lp->head; pn != NULL; pn = pn->next)
			printf("%c ", (char)(pn->val + 'a'));

		printf("\n");
	}
}

/*
 * Add a directional edge going from the node at the source `src' to the
 * destination `dst'.
 */
bool
graph_add_edge(graph_t *gp, int src, int dst)
{
	linked_list_t *lp;

	assert(gp != NULL);
	assert(src < gp->total && dst < gp->total);

	lp = &gp->nodes[src];
	return (ll_insert_int(lp, dst));
}

bool
graph_add_edge_alpha(graph_t *gp, char src, char dst)
{
	int s = src - 'a';
	int d = dst - 'a';

	assert(gp != NULL);
	assert(s >= 0 && s < gp->total);
	assert(d >= 0 && d < gp->total);

	return (graph_add_edge(gp, s, d));
}

bool
graph_remove_edge(graph_t *gp, int src, int dst)
{
	linked_list_t *lp;

	assert(gp != NULL);
	assert(src < gp->total && dst < gp->total);

	lp = &gp->nodes[src];
	return (ll_remove_int(lp, dst));
}

bool
graph_remove_edge_alpha(graph_t *gp, char src, char dst)
{
	int s = src - 'a';
	int d = dst - 'a';

	assert(gp != NULL);
	return (graph_remove_edge(gp, s, d));
}
