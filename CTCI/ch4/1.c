#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "../util/lqueue.h"
#include "../util/graph.h"


/*
 * Utility function to add all immediate children of a node in the graph to
 * a queue which we are using to perform a breadth-first traversal of a
 * graph.
 */
void
add_all_children(lqueue_t *pq, linked_list_t *lp)
{
	node_t *pn;
	bool ret;

	assert(pq != NULL && lp != NULL);

	for (pn = lp->head; pn != NULL; pn = pn->next) {
		ret = lqueue_insert(pq, pn->val);
		assert(ret);
	}
}

/*
 * Use breadth first search to find a path between the source and destination.
 * Note, breadth first search is necessary because if one were to go the the
 * route of depth-first, it could get ugly if there is a cycle somewhere in
 * the graph.
 */
bool
find_route(graph_t *gp, int src, int dst)
{
	lqueue_t queue;
	int current;
	int i;

	assert(gp != NULL);
	assert(src < gp->total && dst < gp->total);

	lqueue_init(&queue);

	(void) lqueue_insert(&queue, src);

	while (lqueue_remove(&queue, &current)) {
		i++;

		/*
		 * If we have visited something more times than there are
		 * total nodes in the graph then that means there is a cycle.
		 * Put another way, the destination is not reachable from the
		 * source.
		 */
		if (i > gp->total)
			return (false);

		/* We have arrived.  Bail out. */
		if (current == dst)
			return (true);

		add_all_children(&queue, &gp->nodes[current]);
	}

	return (false);
}

int main(int argc, char **argv)
{
	graph_t *graph;

	graph = graph_create(6);
	assert(graph != NULL);

	graph_add_edge(graph, 0, 1);
	graph_add_edge(graph, 0, 3);

	graph_add_edge(graph, 1, 0);

	graph_add_edge(graph, 2, 3);

	graph_add_edge(graph, 3, 5);
	graph_add_edge(graph, 4, 0);
	graph_add_edge(graph, 5, 4);

	graph_print(graph);

	if (find_route(graph, 0, 5)) {
		printf("Path exists.\n");
	} else {
		printf("No path exists.\n");
	}

	return (0);
}
