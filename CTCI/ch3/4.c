#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "../util/lstack.h"


typedef struct queue {
	lstack_t in;
	lstack_t out;
} queue_t;

void queue_init(queue_t *);
bool queue_insert(queue_t *, int);
bool queue_remove(queue_t *, int *);
bool queue_empty(queue_t *);
void queue_spill(lstack_t *dst, lstack_t *src);

void
queue_init(queue_t *pq)
{
	assert(pq != NULL);

	(void) bzero(pq, sizeof (queue_t));
}

bool
queue_empty(queue_t *pq)
{
	assert(pq != NULL);

	return (lstack_size(&pq->in) == 0 && lstack_size(&pq->out) == 0);
}

void
queue_spill(lstack_t *dst, lstack_t *src)
{
	int elem;

	assert(dst != NULL && src != NULL);

	while (lstack_pop(src, &elem))
		lstack_push(dst, elem);
}

bool
queue_insert(queue_t *pq, int elem)
{
	assert(pq != NULL);

	if (lstack_size(&pq->out) > 0)
		queue_spill(&pq->in, &pq->out);

	return (lstack_push(&pq->in, elem));
}

bool
queue_remove(queue_t *pq, int *elem)
{

	assert(pq != NULL && elem != NULL);

	if (queue_empty(pq))
		return (false);

	if (lstack_size(&pq->in) > 0)
		queue_spill(&pq->out, &pq->in);

	return (lstack_pop(&pq->out, elem));
}

int main(int argc, char **argv)
{
	int i, elem, elems;
	queue_t queue;

	assert(argc == 2);

	elems = atoi(argv[1]);
	queue_init(&queue);

	for (i = 0; i < elems; i++)
		queue_insert(&queue, i);

	for (i = 0; i < elems / 2; i++) {
		(void) queue_remove(&queue, &elem);
		printf("%d ", elem);
	}

	for (i = elems; i < elems * 2; i++)
		queue_insert(&queue, i);

	while (queue_remove(&queue, &elem))
		printf("%d ", elem);

	printf("\n");

	return (0);
}
