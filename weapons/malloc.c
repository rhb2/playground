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
		union header *ptr;
		unsigned size;
	} s;
	long align;
} header_t;

#define	HDR_SIZE	(sizeof (header_t))

static header_t base;
static header_t *freep = NULL;

void
myfree(void *ap)
{
	header_t *bp, *p;

	bp = (header_t *)ap - 1;

	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break;

	if (bp + bp->s.size == p->s.ptr) {
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	} else {
		bp->s.ptr = p->s.ptr;
	}

	if (p + p->s.size == bp) {
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else {
		p->s.ptr = bp;
	}

	freep = p;
}

static void *
morecore(unsigned nunits)
{
	header_t *nu;
	char *cp;

	cp = mmap(NULL, HDR_SIZE * nunits, PROT_READ | PROT_WRITE,
	    MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);

	if (cp == MAP_FAILED)
		return (NULL);

	nu = (header_t *)cp;
	nu->s.size = nunits;
	myfree((void *)(nu + 1));
	return (freep);
}

void *
mymalloc(unsigned nbytes)
{
	header_t *p, *prevp;
	unsigned nunits = ((HDR_SIZE + nbytes - 1) / HDR_SIZE) + 1;

	if ((p = freep) == NULL) {
		freep = prevp = base.s.ptr = &base;
		base.s.size = 0;
	}

	for  (p = freep->s.ptr; ;prevp = p, p = p->s.ptr) {
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

		if (p == freep && ((p = morecore(nunits)) == NULL))
			return (NULL);
	}
}

int main(int argc, char **argv)
{
	int i;
	int len = atoi(argv[1]);
	int *array = mymalloc(sizeof (int) * len);

	srand(time(0));

	for (i = 0; i < len; i++)
		array[i] = i;//rand() % (len * 10);

	print_array(array, len);
	myfree(array);

	return (0);
}
