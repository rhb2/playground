#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>
#include <sys/mman.h>


void
print_array(int *array, int len)
{
	int i;

	for (i = 0; i < len; i++)
		printf("%d ", array[i]);
	printf("\n");
}

typedef union header {
	struct {
		unsigned size;
		union header *ptr;
	} s;
	long align;
} header_t;

#define	HDRSIZE	sizeof (header_t)
#define	NALLOC	1024

static header_t *freep = NULL;
static header_t base;

void
myfree(void *ap)
{
	header_t *bp, *p;

	bp = (header_t *)ap - 1;

	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break;

	/* Join with the upper block first. */
	if (bp + bp->s.size == p->s.ptr) {
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	} else {
		bp->s.ptr = p->s.ptr;
	}

	/* Join with the lower block. */
	if (p + p->s.size == bp) {
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else {
		p->s.ptr = bp;
	}

	freep = p;
}

static void *
morecore(size_t nunits)
{
	void *more;
	header_t *header;

	if (nunits < NALLOC)
		nunits = NALLOC;

	if ((more = mmap(NULL, nunits * HDRSIZE, PROT_READ | PROT_WRITE,
	    MAP_PRIVATE | MAP_ANONYMOUS, 0, 0)) == MAP_FAILED)
		return (NULL);

	header = (header_t *)more;
	header->s.size = nunits;
	myfree((void *)(header + 1));
	return (freep);
}

void *
mymalloc(size_t nbytes)
{
	header_t *p, *prevp;
	size_t nunits = ((nbytes + HDRSIZE - 1) / HDRSIZE) + 1;

	if ((prevp = freep) == NULL) {
		prevp = freep = base.s.ptr = &base;
		base.s.size = 0;
	}

	for (p = prevp->s.ptr; ;prevp = p, p = p->s.ptr) {
		if (p->s.size >= nunits) {
			if (p->s.size == nunits) {
				prevp->s.ptr = p->s.ptr;
			} else {
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;
			return ((void *)(p + 1));
		}

		if (p == freep && (p = morecore(nunits)) == NULL)
			return (NULL);
	}
}

void
test(int len, int iterations)
{
	int *array;
	int i;

	for (i = 0; i < iterations; i++) {
		int j;
		array =  mymalloc(sizeof (int) * len);

		assert(array != NULL);


		for (j = 0; j < len; j++)
			array[j] = j;

		print_array(array, len);
		myfree(array);

		len *= 2;
	}
}

int main(int argc, char **argv)
{
	int len = atoi(argv[1]);
	int iterations = atoi(argv[2]);

	//srand(time(0));
	test(len, iterations);

	return (0);
}
