#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "../util/linkedlist.h"
#include "../util/lqueue.h"


typedef enum animal {
	DOG,
	CAT
} animal_t;

typedef struct room {
	animal_t atype;		/* Type of animal living in this room. */
	int animal_count;	/* Number of animals in the room. */
	lqueue_t occupants;	/* Ordered list of animals in the room. */
	struct room *prev;	/* Previous room in the shelter. */
	struct room *next;	/* Next room in the shelter. */
} room_t;

typedef struct shelter {
	int room_count;		/* Number of rooms in the shelter. */
	int animal_count;	/* Number of animals in the shelter. */
	room_t *head;		/* Head of the room list. */
	room_t *tail;		/* Tail of the room list. */
} shelter_t;

void shelter_init(shelter_t *);
bool shelter_add_room(shelter_t *, animal_t);
void shelter_remove_room(shelter_t *, room_t *);
room_t *shelter_get_room(shelter_t *, animal_t);
bool shelter_animal_store(shelter_t *, animal_t, int);
bool shelter_animal_rescue(shelter_t *, int *);
bool shelter_animal_rescue_type(shelter_t *, animal_t, int *);
void shelter_print(shelter_t *);
room_t *room_create(animal_t);
void room_print(room_t *);

void
shelter_init(shelter_t *sp)
{
	assert(sp != NULL);

	(void) bzero(sp, sizeof (shelter_t));
}

/*
 * Always adds to the head of the list.
 */
bool
shelter_add_room(shelter_t *sp, animal_t rtype)
{
	room_t *rp;
	bool ret;

	if ((rp = room_create(rtype)) == NULL)
		return (false);

	/* New shelter.  This is the first room. */
	if (sp->room_count == 0) {
		sp->head = sp->tail = rp;
	} else {
		rp->next = sp->head;
		sp->head->prev = rp;
		sp->head = rp;
	}

	sp->room_count++;
	return (true);
}

/*
 * Always removes from the tail of the list.
 */
void
shelter_remove_room(shelter_t *sp, room_t *rp)
{
	assert(sp != NULL && rp != NULL);

	sp->room_count--;

	/*
	 * If this is the last room in the shelter then set the head and tail
	 * to NULL.
	 */
	if (sp->room_count == 0) {
		free(rp);
		sp->head = NULL;
		sp->tail = NULL;
		return;
	}

	if (rp == sp->head) {
		sp->head = sp->head->next;
		sp->head->prev = NULL;
	} else if (rp == sp->tail) {
		sp->tail = sp->tail->prev;
		sp->tail->next = NULL;
	} else {
		rp->prev->next = rp->next;
		rp->next->prev = rp->prev;
	}

	free(rp);
}

room_t *
shelter_get_room(shelter_t *sp, animal_t atype)
{
	room_t *rp;

	assert(sp != NULL);

	for (rp = sp->tail; rp != NULL; rp = rp->prev) {
		if (rp->atype == atype)
			break;
	}

	return (rp);
}

bool
shelter_animal_store(shelter_t *sp, animal_t atype, int id)
{
	room_t *rp;

	assert(sp != NULL);

	/*
	 * If the room at the head of the list does not hold the type of
	 * animal that we are trying to house, then we need to create a new
	 * room in the shelter for that type.  If we fail to do that, then we
	 * flag failure and return.
	 */
	if ((sp->head == NULL || sp->head->atype != atype) &&
	    !shelter_add_room(sp, atype))
		return (false);

	rp = sp->head;

	/*
	 * We have a good room to store the animal.
	 */
	if (!lqueue_insert(&rp->occupants, id))
		return (false);

	rp->animal_count++;
	sp->animal_count++;
	return (true);
}

bool
shelter_animal_rescue(shelter_t *sp, int *id)
{
	assert(sp != NULL && id != NULL);

	/* Empty shelter */
	if (sp->tail == NULL)
		return (false);


	/* The room should never be empty before a remove. */
	if (!lqueue_remove(&sp->tail->occupants, id))
		return (false);

	/* Decrement global animal count. */
	sp->animal_count--;

	/*
	 * If we just removed the last animal in this room, then we can remove
	 * the room entirely.  No need to decrement the local animal count.
	 */
	if (sp->tail->animal_count == 1) {
		shelter_remove_room(sp, sp->tail);
	} else {
		sp->tail->animal_count--;
	}

	return (true);
}

bool
shelter_animal_rescue_type(shelter_t *sp, animal_t atype, int *id)
{
	room_t *rp;

	assert(sp != NULL & id != NULL);

	if ((rp = shelter_get_room(sp, atype)) == NULL)
		return (false);

	(void) lqueue_remove(&rp->occupants, id);

	sp->animal_count--;

	if (rp->animal_count == 1) {
		shelter_remove_room(sp, rp);
	} else {
		rp->animal_count--;
	}

	return (true);
}

room_t *
room_create(animal_t rtype)
{
	room_t *rp;

	if ((rp = malloc(sizeof (room_t))) == NULL)
		return (NULL);

	(void) bzero(rp, sizeof (room_t));
	rp->atype = rtype;
	return (rp);
}

void
shelter_print(shelter_t *sp)
{
	room_t *rp;

	assert(sp != NULL);

	for (rp = sp->head; rp != NULL; rp = rp->next) {
		room_print(rp);
		printf("\n");
	}
}

void
room_print(room_t *rp)
{
	assert(rp != NULL);

	printf("%s: ", rp->atype == DOG ? "DOGS" : "CATS");
	lqueue_print(&rp->occupants);
}

int main(int argc, char **argv)
{
	int i, elem, elems;
	animal_t atype;
	shelter_t shelter;

	assert(argc == 2);
	elems = atoi(argv[1]);

	shelter_init(&shelter);

	for (i = 0; i < elems; i++) {
		int num = i % 4;
		atype = num <= 1 ? DOG : CAT;
		shelter_animal_store(&shelter, atype, i);
	}

	shelter_print(&shelter);

	/* Rescue all the dogs. */
	while (shelter_animal_rescue_type(&shelter, DOG, &elem)) {
		printf("Just rescued: %d\n", elem);
	}

	/* Rescue everyone else. */
	while (shelter_animal_rescue(&shelter, &elem)) {
		printf("Just rescued: %d\n", elem);
	}

	/* Print (what should be at this point) an empty shelter. */
	shelter_print(&shelter);
	return (0);
}
