#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "../util/lqueue.h"
#include "../util/graph.h"


/*
 * Roll through the graph and remove and dependencies that other projects have
 * on the one supplied by the caller.  This should be called when the project
 * `project' is finally built.
 */
void
satisfy(graph_t *gp, char project)
{
	int i;
	linked_list_t *pl;
	char p = project - 'a';

	assert(gp != NULL);

	for (i = 0; i < gp->total; i++) {
		pl = &gp->nodes[i];
		(void) ll_remove_int(pl, p);
	}

	printf("%c ", project);
}

bool
build_impl(graph_t *gp, int project, int visited)
{
	node_t *pn;

	assert(gp != NULL);

	/* Loop detected.  This series of projects can't be built. */
	if (visited > gp->total)
		return (false);

	for (pn = gp->nodes[project].head; pn != NULL; pn = pn->next)
		if (!build_impl(gp, pn->val, ++visited))
			return (false);

	satisfy(gp, project + 'a');
	return (true);
}

bool
build(graph_t *gp)
{
	int i;
	linked_list_t *pl;

	assert(gp != NULL);

	/*
	 * First, find all nodes that have no dependencies and build them first.
	 */
	for (i = 0; i < gp->total; i++) {
		pl = &gp->nodes[i];
		if (pl->head == NULL)
			satisfy(gp, i + 'a');
	}

	for (i = 0; i < gp->total; i++) {
		if (gp->nodes[i].head != NULL)
			if (!build_impl(gp, i, 1))
				return (false);
	}

	return (true);
}

int main(int argc, char **argv)
{
	graph_t *graph;

	graph = graph_create(6);
	assert(graph != NULL);

	/* 'd' depends on 'a' */
	graph_add_edge_alpha(graph, 'd', 'a');

	/* 'b' depends on 'f' */
	graph_add_edge_alpha(graph, 'b', 'f');

	/* 'd' depends on 'b' */
	graph_add_edge_alpha(graph, 'd', 'b');

	/* 'a' depends on 'f' */
	graph_add_edge_alpha(graph, 'a', 'f');

	/*
	 * Uncomment this line to add a circular dependency and break the
	 * build.  A circular project dependency means that the series of
	 * project as a whole can not be built.
	 */
	//graph_add_edge_alpha(graph, 'f', 'a');

	/* 'c' depends on 'd' */
	graph_add_edge_alpha(graph, 'c', 'd');

	printf("Project depdency graph:\n");
	graph_print_alpha(graph);
	printf("\n");

	if (!build(graph))
		printf("\nProject can not be built.\n");
	else
		printf("\nProject successfully built.\n");	

	return (0);
}
