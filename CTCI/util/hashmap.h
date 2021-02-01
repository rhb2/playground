#ifndef	_LSTACK_H
#define	_LSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "linkedlist.h"

typedef struct hashmap {
	linked_list_t *buckets;
	int num_buckets;
} hashmap_t;

hashmap_t *hash_map_create(int);
void hashmap_insert(hashmap_t *, int);
bool hashmap_remove(hashmap_t *, int);

#define	ABS(x)	((x) < 0 ? ((x) * -1) : (x))

hashmap_t *
hashmap_create(int buckets)
{
	hashmap_t *hp;

	if ((hp = malloc(sizeof (hashmap_t))) == NULL)
		return (NULL);

	(void) bzero(hp, sizeof (hashmap_t));
	hp->num_buckets = buckets;

	if ((hp->buckets = malloc(sizeof (linked_list_t) * buckets)) == NULL) {
		free(hp);
		return (NULL);
	}

	(void) bzero(hp->buckets, sizeof (linked_list_t) * buckets);
	return (hp);
}

void
hashmap_insert(hashmap_t *hp, int val)
{
	int index;
	linked_list_t *pl;

	assert(hp != NULL);

	index = ABS(val) % hp->num_buckets;
	pl = &hp->buckets[index];

	(void) ll_insert_int(pl, val);
}

bool
hashmap_remove(hashmap_t *hp, int val)
{
	int index;
	linked_list_t *pl;

	assert(hp != NULL);

	index = ABS(val) % hp->num_buckets;
	pl = &hp->buckets[index];

	return (ll_remove_int(pl, val));
}

int
hashmap_contains(hashmap_t *hp, int val)
{
	int index;
	linked_list_t *pl;
	node_t *pn;
	int count = 0;

	assert(hp != NULL);

	index = ABS(val) % hp->num_buckets;
	pl = &hp->buckets[index];

	for (pn = pl->head; pn != NULL; pn = pn->next) {
		if (pn->val == val)
			count++;
	}

	return (count);
}

#endif	/* _LSTACK_H */
