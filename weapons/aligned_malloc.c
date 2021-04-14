#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define	ALIGN_UP(num, align)	(((num) + ((align) - 1)) & ~((align) - 1))
#define	ALIGN_DOWN(num, align)	((num) & (~((align) - 1)))

typedef uint16_t offset_t;
#define	PTR_OFFSET_SZ	sizeof (offset_t)

void *
aligned_malloc(size_t align, size_t size)
{
	void *ptr = NULL;
	void *p;
	uint32_t hdr_size;

	/* Must be a power of 2. */
	assert((align & (align - 1)) == 0);

	if (!align || !size)
		return (NULL);

	hdr_size = PTR_OFFSET_SZ + (align - 1);

	if ((p = malloc(size + hdr_size)) != NULL) {
		ptr = (void *) ALIGN_UP(((uintptr_t)p + PTR_OFFSET_SZ), align);
		*((offset_t *)ptr - 1) =
		    (offset_t)((uintptr_t)ptr - (uintptr_t)p);

		printf("%lu\n", (uintptr_t)ptr - (uintptr_t)p);
		printf("%lu\n", (void *)ptr - (void *)p);
	}

	return (ptr);
}

void
aligned_free(void *ptr)
{
	void *p;
	offset_t offset;

	offset = *(offset_t *)ptr - 1;
	p = (void *)((uint8_t *)ptr - offset);
	free(p);
}

void
test_align_up(int align)
{
	int i;

	for (i = 0; i < 100; i++)
		printf("%d: %d\n", i, ALIGN_UP(i, align));

	printf("\n");
}

void
test_align_down(align)
{
	int i;

	for (i = 0; i < 100; i++)
		printf("%d: %d\n", i, ALIGN_DOWN(i, align));

	printf("\n");
}

int main(int argc, char **argv)
{
	unsigned int i = 0;


	for (i = 1; i < 10; i++) {
		printf("%p\n", (void *)aligned_malloc(16, 1));
	}
	printf("\n\n");
	for (i = 1; i < 10; i++) {
		printf("%p\n", (void *)malloc(1));
	}

	return (0);
}
