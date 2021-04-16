#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define	ALIGN_UP(num, align)	(((num) + ((align) - 1)) & ~((align) - 1))
#define	ALIGN_DOWN(num, align)	((num) & (~((align) - 1)))

typedef uint16_t offset_t;
#define	OFFSET_SIZE	sizeof (offset_t)

void *
aligned_malloc(size_t align, size_t nbytes)
{
	void *p, *ptr;
	size_t padding = OFFSET_SIZE + align;
	size_t total = padding + ALIGN_UP(nbytes, align);

	if (align == 0 || size == 0)
		return (NULL);

	assert((align & (align - 1)) == 0);

	p = malloc(total);
	if (p == NULL)
		return (NULL);

	ptr = (void *) ALIGN_UP((uintptr_t)p + OFFSET_SIZE, align);
	*((offset_t *)ptr - 1) = (offset_t)((uintptr_t)ptr - (uintptr_t)p);

	printf("malloc: %p %p\n", p, ptr);

	return (ptr);
}

void
aligned_free(void *ptr)
{
	void *p;
	offset_t offset;

	offset = *((offset_t *)ptr - 1);
	p = (void *)((uint8_t *)ptr - offset);

	printf("Free:   %p %p\n\n", p, ptr);

	free(p);
}

#define	FLASH_DMA_ALIGN		4
#define	FLASH_DMA_MAX_SIZE	20

ssize_t
hal_flash_read(uint32_t addr, void *bud, size_t len)
{
	return (len);
}

/*
 * For academic purposes only.  This is how you perform an aligned read from
 * flash when given a flash address that may not be properly aligned.
 */
ssize_t
flash_read(uint32_t flash_addr, void *buf, size_t len)
{
	size_t size = len > FLASH_DMA_MAX_SIZE ? FLASH_DMA_MAX_SIZE : len;
	uint32_t start = ALIGN_DOWN(flash_addr, FLASH_DMA_ALIGN);
	uint32_t skip1 = flash_addr - start;
	uint32_t total = ALIGN_UP(flash_addr + size, FLASH_DMA_ALIGN) - start;
	uint32_t skip2 = total - size - skip1;

	assert(buf != NULL);

	void *aligned_buf = aligned_malloc(total, FLASH_DMA_ALIGN);
	if (aligned_buf == NULL)
		return (-1);

	ssize_t ret = hal_flash_read(start, aligned_buf, total);
	if (ret < 0)
		return (-1);

	(void) memcpy(buf, (uint8_t *)aligned_buf + skip1, size);
	aligned_free(aligned_buf);

	return (size);
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

//	test_align_down(8);
//	test_align_up(8);

	for (i = 1; i < 10; i++) {
		void *p = aligned_malloc(8, 1);
		aligned_free(p);
	}
	printf("\n\n");

/*
	for (i = 1; i < 10; i++) {
		printf("%p\n", (void *)malloc(1));
	}
*/

	return (0);
}
