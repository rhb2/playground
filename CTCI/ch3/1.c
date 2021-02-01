#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>


/*
 * This is a simple stack.  Three of these will be stored in an array and
 * should have flexible boundaries to allow for the entire piece of
 * underlying storage to be completely used. Important features of this
 * structure: push, pop, and shift (in either direction).  The other noteworthy
 * characteristic is that this kind of stack can grow from either left->right
 * or right->left.  The direction of its growth is based on the `inc' member.
 * That is, it will increment by one if growing from left to right and it will
 * increment by negative 1 if growing from right to left.
 */
typedef struct stk {
	int *bottom;
	int *top;
	int inc;
	int capacity;
} stk_t;

typedef enum direction {
	LEFT,
	RIGHT
} direction_t;

typedef enum stack_type {
	STACK_LEFT,
	STACK_MIDDLE,
	STACK_RIGHT
} stack_type_t;

/* Stk methods */
void stk_init(stk_t *, int *, int, int);
bool stk_push(stk_t *, int);
bool stk_pop(stk_t *, int *);
int stk_count(stk_t *);
bool stk_full(stk_t *);
bool stk_empty(stk_t *);
void stk_shift(stk_t *, direction_t);
void stk_print(stk_t *);

/*
 * This is the data structure that maintains 3 different stacks with flexible
 * boundaries inside of a single array.
 */
typedef struct stacks {
	int *data;
	int capacity;
	stk_t left;
	stk_t middle;
	stk_t right;
} stacks_t;

/* Stacks methods */
bool stacks_init(stacks_t *, int);
bool stacks_push(stacks_t *, stack_type_t, int);
bool stacks_pop(stacks_t *, stack_type_t, int *);

bool
stacks_init(stacks_t *sp, int capacity)
{
	int *data;

	assert(sp != NULL);

	(void) bzero(sp, sizeof (stacks_t));

	if ((data = malloc(sizeof (int) * capacity)) == NULL)
		return (false);

	(void) bzero(data, sizeof (int) * capacity);
	sp->data = data;
	sp->capacity = capacity;

	stk_init(&sp->left, data, 1, capacity);
	stk_init(&sp->middle, data + (capacity / 3), 1, capacity);
	stk_init(&sp->right, data + capacity - 1, -1, capacity);
	return (true);
}

bool
stacks_full(stacks_t *sp)
{
	return ((&sp->left.top + 1 == &sp->middle.bottom) &&
	    &sp->middle.top + 1 == &sp->right.top);
}

bool
stacks_push(stacks_t *sp, stack_type_t stype, int elem)
{
	stk_t *stkp;

	assert(sp != NULL);

	/* No room left anywhere. */
	if (stacks_full(sp))
		return (false);

	/*
	 * Push the element on to the caller-specified stack.  At this point,
	 * there is room in the array somewhere, so this operation really
	 * can't fail.  The only question is whether or not we will need to
	 * shift around the contents of the middle stack to make room elsewhere
	 * in the array before the push.
	 */
	if (stype == STACK_LEFT) {
		stkp = &sp->left;
		/*
		 * If we are bumping up against the middle stack, then we need
		 * to shift it to the right to make room for the left stack.
		 */
		if (sp->left.top == sp->middle.bottom)
			stk_shift(&sp->middle, RIGHT);
	}

	if (stype == STACK_MIDDLE) {
		stkp = &sp->middle;
		/*
		 * If we are bumping up against the top of the right stack
		 * (keep in mind, the right stack grows from right to left
		 * which is why we would eventually hit the top of it), we
		 * need to shift ourselves by one place in order to make room
		 * to push the next element.
		 */
		if (sp->middle.top == sp->right.top)
			stk_shift(&sp->middle, LEFT);
	}

	if (stype == STACK_RIGHT) {
		stkp = &sp->right;
		/*
		 * If the right is bumping up against the top of the left
		 * stack, we need to shift the left stack to the left to make
		 * room.
		 */
		if (sp->middle.top == sp->right.top)
			stk_shift(&sp->middle, LEFT);
	}

	return (stk_push(stkp, elem));
}

bool
stacks_pop(stacks_t *sp, stack_type_t stype, int *elem)
{
	stk_t *stkp;

	assert(sp != NULL);

	switch (stype) {
	case (STACK_LEFT):
		stkp = &sp->left;
		break;
	case (STACK_MIDDLE):
		stkp = &sp->middle;
		break;
	case (STACK_RIGHT):
		stkp = &sp->right;
		break;
	default:
		return (false);
	}

	return (stk_pop(stkp, elem));
}

void
stk_init(stk_t *sp, int *data, int inc, int cap)
{
	assert(sp != NULL && data != NULL);
	sp->bottom = sp->top = data;
	sp->inc = inc;
	sp->capacity = cap;
}

bool
stk_push(stk_t *sp, int elem)
{
	assert(sp != NULL);

	if (stk_full(sp))
		return (false);

	*sp->top = elem;
	sp->top += sp->inc;
	return (true);
}

/*
 * Pop off the top of the stack.  This function writes a zero in place of
 * where the popped element was.  This isn't necessary, but it helps when
 * printing the entire underlying array for debugging purposes to make
 * visually identifying where the top of each stack is more conveniently.
 */
bool
stk_pop(stk_t *sp, int *elem)
{
	assert(sp != NULL && elem != NULL);

	if (stk_empty(sp))
		return (false);

	sp->top -= sp->inc;
	*elem = *(sp->top);
	*(sp->top) = 0;
	return (true);
}

int
stk_count(stk_t *sp)
{
	assert(sp != NULL);

	if (sp->inc == -1)
		return (sp->bottom - sp->top);

	return (sp->top - sp->bottom);
}

bool
stk_full(stk_t *sp)
{
	assert(sp != NULL);

	return (stk_count(sp) == sp->capacity);
}

bool
stk_empty(stk_t *sp)
{
	assert(sp != NULL);

	return (sp->bottom == sp->top);
}

void
stk_shift(stk_t *sp, direction_t dir)
{
	int count;
	void *src;
	void *dst;
	int *last;
	int inc = dir == LEFT ? -1 : 1;

	assert(sp != NULL);

	count = stk_count(sp);
	src = sp->inc == -1 ? sp->top + 1 : sp->bottom;
	dst = dir == LEFT ? src - sizeof (int) : src + sizeof (int);
	(void) memmove(dst, src, count * sizeof (int));

	sp->top += inc;
	sp->bottom += inc;

	/*
	 * Similar to stk_pop(), we write a zero out to the location that we
	 * just freed up by shifting.  This isn't necessary, but it makes
	 * visualizing the stacks location in the underlying array a lot
	 * easier.
	 */
	if (dir == LEFT) {
		last = (int *) src;
		last += count - 1;
		*last = 0;
	} else {
		last = (int *) src;
		*last = 0;
	}
}

void
stk_print(stk_t *sp)
{
	int *elem;
	int count;
	int i;

	assert(sp != NULL);

	if (stk_empty(sp))
		return;

	count = stk_count(sp);
	elem = sp->top - sp->inc;

	for (i = 0; i < count; i++) {
		printf("%d ", *elem);
		elem -= sp->inc;
	}

	printf("\n");
}

void
print_array(int *array, int len)
{
	int i;

	assert(array != NULL);

	for (i = 0; i < len; i++)
		printf("%d ", array[i]);

	printf("\n");
}

int main(int argc, char **argv)
{
	int i, num;
	stacks_t mystacks;
	int elem;

	assert(argc == 2);

	num = atoi(argv[1]);

	(void) stacks_init(&mystacks, num);

	for (i = 0; i < 5; i++) {
		stacks_push(&mystacks, STACK_LEFT, i + 1);
		stacks_push(&mystacks, STACK_MIDDLE, i + 1);
		stacks_push(&mystacks, STACK_RIGHT, i + 1);
	}

	stacks_push(&mystacks, STACK_LEFT, 6);
	stacks_push(&mystacks, STACK_LEFT, 7);
	stacks_push(&mystacks, STACK_LEFT, 8);
	stacks_push(&mystacks, STACK_LEFT, 9);

	print_array(mystacks.data, num);

	while (stacks_pop(&mystacks, STACK_LEFT, &elem)) {
		printf("Just popped: %d\n", elem);
		print_array(mystacks.data, num);
	}

	while (stacks_pop(&mystacks, STACK_MIDDLE, &elem)) {
		printf("Just popped: %d\n", elem);
		print_array(mystacks.data, num);
	}

	while (stacks_pop(&mystacks, STACK_RIGHT, &elem)) {
		printf("Just popped: %d\n", elem);
		print_array(mystacks.data, num);
	}

	return (0);
}
