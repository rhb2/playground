#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>


static void
swap(int *array, int x, int y)
{
	array[x] = (array[x] + array[y]) - (array[y] = array[x]);
}

static bool
is_member(int *array, int len, int elem, int *idx)
{
	int i;

	for (i = 0; i < len; i++)
		if (array[i] == elem) {
			*idx = i;
			return (true);
		}

	return (false);
}

/*
 * Circular queue.  This is the primary data structure used in all page
 * replacement algorithms below, although its only really treated as a
 * circular queue for the FIFO algorithm.  For the other algorithms, once
 * the queue has reached capacity, the order of the elements (i.e. page
 * numbers) can change that violate the FIFO pattern depending on whether
 * we sustain a hit or a page fault.  For example, in LRU, the pages are
 * ordered from coldest to hottest.  Whenever there is a page hit, that
 * particular page is shifted to the hot end of the array.  When using
 * the optimal page replacement algorithm, if we experience a page fault
 * a victim page is selected for replacement and that page can be anywhere
 * within the array.
 */
typedef struct queue {
	int *data;	/* Holds the list of frame numbers. */
	int front;	/* Front of the queue (when used as one). */
	int depth;	/* Total number of pages in memory (working set). */
	int capacity;	/* Maximum number of "frames". */
} queue_t;

queue_t *
queue_create(int capacity)
{
	queue_t *pq;

	if ((pq = malloc(sizeof (queue_t))) == NULL)
		return (NULL);

	bzero(pq, sizeof (queue_t));
	pq->capacity = capacity;

	if ((pq->data = malloc(sizeof (int) * capacity)) == NULL) {
		free(pq);
		return (NULL);
	}

	return (pq);
}

void
queue_print(queue_t *pq)
{
	int i;

	assert(pq != NULL);

	for (i = 0; i < pq->depth; i++)
		printf("%d ", pq->data[i]);

	printf("\n");
}

static void
page_hit_miss(queue_t *pq, int *faults, bool hit, bool show_work)
{
	assert(pq != NULL && faults != NULL);

	if (hit) {
		if (show_work)
			printf("%s", "hit\n");
		return;
	}

	(*faults)++;

	if (show_work) {
		printf("%s", "page fault ");
		queue_print(pq);
	}
}

void
queue_reset(queue_t *pq)
{
	pq->depth = 0;
	pq->front = 0;
}

static int
fifo_in_memory(queue_t *pq, int elem)
{
	int i;
	int cur;

	cur = pq->depth == pq->capacity ? (pq->front) : 0;

	for (i = 0; i < pq->depth; i++) {
		if (pq->data[cur] == elem)
			return (cur);

		cur = (cur + 1) % pq->capacity;
	}
	return (-1);
}

static bool
fifo_insert(queue_t *pq, int elem)
{
	int i;
	int current = pq->front;

	assert(pq != NULL);

	if (fifo_in_memory(pq, elem) != -1)
		return (true);

	pq->data[pq->front] = elem;
	pq->front = (pq->front + 1) % pq->capacity;

	if (pq->depth < pq->capacity)
		pq->depth++;

	return (false);
}

int
fifo(queue_t *pq, int *array, int len, bool show_work)
{
	int i;
	bool hit;
	int faults = 0;

	assert(pq != NULL);

	queue_reset(pq);

	for (i = 0; i < len; i++) {
		if (show_work)
			printf("%d: ", array[i]);

		/*
		 * `fifo_insert()' returns false if the element was not
		 * already in memory.  That is, we have experienced a page
		 * fault.
		 */
		hit = fifo_insert(pq, array[i]);
		page_hit_miss(pq, &faults, hit, show_work);
	}

	return (faults);
}

/*
 * Under no circumstances should this function ever be called unless the
 * the queue is full.  Call under any other circumstances and there will be
 * unintended consequences.
 */
static int
clock_find_victim(queue_t *pq, bool *flags)
{
	int i;
	int current;

	assert(pq != NULL && flags != NULL);

	/*
	 * Start with the oldest page first.  It is assumed that the queue
	 * is burting at the seams at this point, so `pq->front' will be
	 * pointing to the oldest element in the array by nature of the fact
	 * that it is full and it is circular.
	 */
	current = pq->front;

	/*
	 * Wrap aound the queue clock-wise until we find a victim.  If we
	 * persist, we eventually will.  Worst case, we iterate through the
	 * loop n + 1 times where n is the capacity.
	 */
	for (;;) {
		if (flags[current] == false)
			break;

		flags[current] = false;
		current = (current + 1) % pq->capacity;
	}

	return (current);
}

static bool
clock_insert(queue_t *pq, int elem, bool *flags)
{
	int i;
	int index;
	int current = pq->front;

	assert(pq != NULL && flags != NULL);

	if ((index = fifo_in_memory(pq, elem)) != -1) {
		flags[index] = true;
		return (true);
	}

	if (pq->depth < pq->capacity) {
		pq->data[pq->front] = elem;
		flags[pq->front] = false;
		pq->front = (pq->front + 1) % pq->capacity;
		pq->depth++;
		return (false);
	}

	index = clock_find_victim(pq, flags);
	pq->data[index] = elem;
	flags[index] = false;
	pq->front = (index + 1) % pq->capacity;
	return (false);	
}

static void
print_flags(bool *array, int len)
{
	int i;

	assert(array != NULL);

	for (i = 0; i < len; i++)
		printf("%d ", array[i] ? 1 : 0);

	printf("\n");
}

int
clock(queue_t *pq, int *array, int len, bool show_work)
{
	int i;
	int hit;
	int faults = 0;
	bool flags[pq->capacity];

	assert(pq != NULL);

	queue_reset(pq);
	bzero(flags, sizeof (flags));

	for (i = 0; i < len; i++) {
		if (show_work) {
			printf("PASS: %d\n", i + 1);
			printf("%d: ", array[i]);
		}

		hit = clock_insert(pq, array[i], flags);
		page_hit_miss(pq, &faults, hit, show_work);

		if (show_work) {
			print_flags(flags, pq->capacity);
			printf("Pointer = %d\n\n", pq->front);
		}
	}

	return (faults);
}

static bool
lru_in_memory(queue_t *pq, int elem)
{
	int i;
	int j;

	for (i = 0; i < pq->depth; i++) {
		if (pq->data[i] == elem)
			break;
	}

	/* Page number not found. */
	if (i == pq->depth)
		return (false);

	/*
	 * In the LRU implemention, the array of page numbers is ordered from
	 * coldest (at offset 0) to hottest (at offset `pq->depth'.  We have
	 * just experienced a hit, so that page needs to be moved to the (hot)
	 * end of the array.
	 */
	for (; i < pq->depth - 1; i++)
		swap(pq->data, i, i + 1);

	return (true);
}

static bool
lru_insert(queue_t *pq, int elem)
{
	int i;

	if (lru_in_memory(pq, elem))
		return (true);

	if (pq->depth == pq->capacity) {
		(void) memcpy(pq->data, &pq->data[1],
		    sizeof (int) * (pq->depth - 1));
		pq->depth--;
	}

	pq->data[pq->depth] = elem;
	pq->depth++;
	return (false);
}

int
lru(queue_t *pq, int *array, int len, bool show_work)
{
	int i;
	bool hit;
	int faults = 0;

	queue_reset(pq);

	for (i = 0; i < len; i++) {
		if (show_work)
			printf("%d: ", array[i]);

		hit = lru_insert(pq, array[i]);
		page_hit_miss(pq, &faults, hit, show_work);
	}
	return (faults);
}

static bool
optimal_in_memory(queue_t *pq, int *array, int len, int index)
{
	int i;
	int j;
	int tmp[pq->depth];

	for (i = 0; i < pq->depth; i++) {
		if (pq->data[i] == array[index])
			break;
	}

	/* If i < depth, that means we found a match. */
	return (i < pq->depth);
}

/*
 * Scan the reference string from the current index to the end.  Record the
 * first index (and only the first) of any page number currently in memory.
 * The page that has the highest index in the reference string will be the
 * one that is chosen for eviction.  The only caveat to this heuristic is if
 * we find that one (or more) of the pages in our current working set never
 * occurs again in the reference string, at which point, that is the one that
 * we should obviously replace first.
 */
static int
optimal_find_victim(queue_t *pq, int *array, int len, int cur)
{
	int i;
	int member;
	int index;
	int largest = 0;
	int tmp[pq->depth];

	bzero(tmp, sizeof (int) * pq->depth);

	for (i = cur; i < len; i++) {
		member = is_member(pq->data, pq->depth, array[i], &index);
		if (member && tmp[index] == 0)
			tmp[index] = i;
	}

	/*
	 * If a given page occurs 0 times in the future, return the index of
	 * the first one that we see in our scan.  There could be more than one
	 * that occurs zero times, in which case, it really does not matter
	 * which one is selected for eviction.
	 */
	for (i = 0; i < pq->depth; i++)
		if (tmp[i] == 0)
			return (i);

	/*
	 * If we are here, then all pages that are currently in memory are
	 * accessed again at some point in time in the future.  In a case like
	 * that, pick the one that is farthest away (i.e. has the largest index
	 * in the reference string.
	 */
	for (i = 0; i < pq->depth; i++) {
		if (tmp[i] > largest) {
			largest = tmp[i];
			index = i;
		}
	}
	return (index);
}

int
optimal(queue_t *pq, int *array, int len, bool show_work)
{
	int i;
	int faults = 0;
	bool hit;

	queue_reset(pq);

	for (i = 0; i < len; i++) {
		if (show_work)
			printf("%d: ", array[i]);

		hit = optimal_in_memory(pq, array, len, i);

		if (!hit && pq->depth < pq->capacity) {
			pq->data[pq->depth] = array[i];
			pq->depth = pq->depth + 1;
		} else if (!hit && pq->depth == pq->capacity) {
			int victim = optimal_find_victim(pq, array, len, i);
			pq->data[victim] = array[i];
		}

		page_hit_miss(pq, &faults, hit, show_work);
	}

	return (faults);
}

void
summary(queue_t *pq, char *algo, int frames, int *array, int len)
{
	int faults;
	int i;
	int (*f)(queue_t *, int *, int, bool);

	assert(pq != NULL);

	if (strncmp(algo, "FIFO", strlen("FIFO")) == 0) {
		f = fifo;
	} else if (strncmp(algo, "LRU", strlen("LRU")) == 0) {
		f = lru;
	} else if (strncmp(algo, "OPTIMAL", strlen("OPTIMAL")) == 0) {
		f = optimal;
	} else if (strncmp(algo, "CLOCK", strlen("CLOCK")) == 0) {
		f = clock;
	}

	printf("%s:\n", algo);

	(void) f(pq, array, len, true);

	printf("\nNumber of faults with fewer frames:\n");
	printf("Frames\tFaults\n");
	printf("------\t------\n");
	for (i = 1; i <= frames; i++) {
		pq->capacity = i;
		faults = f(pq, array, len, false);
		printf("%d\t%d\n", i, faults);
	}
}

//int reference[] = {1, 2, 3, 4, 2, 1, 5, 6, 2, 1, 2, 3, 7, 6, 3, 2, 1, 2, 3, 6};
//int reference[] = {0, 4, 1, 4, 2, 4, 3, 4, 2, 4, 0, 4, 1, 4, 2, 4, 3, 4};
//int reference[] = {2, 5, 10, 1, 2, 2, 6, 9, 1, 2, 10, 2, 6, 1, 2, 1, 6, 9, 5, 1};
int reference[] = {1, 2, 3, 4, 2, 3, 4, 1, 2, 1, 1, 3, 1, 4};
#define	REF_LEN	(sizeof (reference) / sizeof (reference[0]))

int main(int argc, char **argv)
{
	int frames;
	char *algo;
	queue_t *pq;
	int *array;
	int len;
	int i;

	assert(argc > 3);

	algo = argv[1];
	frames = atoi(argv[2]);

	pq = queue_create(frames);
	assert(pq != NULL);

	len = argc - 3;
	array = malloc(sizeof (int) * len);
	assert(array != NULL);

	for (i = 0; i < len; i++)
		array[i] = atoi(argv[i + 3]);
	
	//summary(pq, algo, frames, reference, REF_LEN);
	summary(pq, algo, frames, array, len);
	free(array);
	return (0);
}
