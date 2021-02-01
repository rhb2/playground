#ifndef	_BITMAP_H
#define	_BITMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>


#define	BITS_PER_BYTE	8

typedef struct bitmap {
	uint8_t *data;
	int num_bits;
	int num_bytes;
} bitmap_t;

bitmap_t *bitmap_create(int);
void bitmap_destroy(bitmap_t *);
void bitmap_print(bitmap_t *);
bool bitmap_set(bitmap_t *, uint32_t);
bool bitmap_clear(bitmap_t *, uint32_t);

/* Utility functions that perform bit operations on a single byte. */
static void print_byte(uint8_t);
static bool get_bit(uint8_t, uint8_t index);
static void set_bit(uint8_t *, uint8_t index);
static void clear_bit(uint8_t *, uint8_t index);

bitmap_t *
bitmap_create(int len)
{
	bitmap_t *map;
	int num = len - 1;
	int bytes = 0;

	assert(num > 0);

	/* Round up to the nearest multiple of 8. */
	bytes = num / BITS_PER_BYTE;
	if (num % BITS_PER_BYTE)
		bytes++;

	if ((map = malloc(sizeof (bitmap_t))) == NULL)
		return (NULL);

	(void) bzero(map, sizeof (bitmap_t));

	if ((map->data = malloc(bytes)) == NULL) {
		free(map);
		return (NULL);
	}

	(void) bzero(map->data, bytes);
	map->num_bits = len;
	map->num_bytes = bytes;
	return (map);
}

void
bitmap_destroy(bitmap_t *map)
{
	assert(map != NULL);

	free(map->data);
	free(map);
}

void
bitmap_print(bitmap_t *map)
{
	int i;

	assert(map != NULL);

	for (i = 0; i < map->num_bytes; i++) {
		print_byte(map->data[i]);
		printf("%c", ' ');
	}
	printf("\n");
}

/*
 * Returns the previous value for this bit in case a caller would like to know
 * what the value was prior to this operation.
 */
bool
bitmap_set(bitmap_t *map, uint32_t index)
{
	bool ret;
	int byte = index / BITS_PER_BYTE;
	uint8_t bit = index % BITS_PER_BYTE;

	assert(map != NULL);
	assert(index < map->num_bits);

	ret = get_bit(map->data[byte], bit);
	set_bit(&map->data[byte], bit);
	return (ret);
}

/*
 * Returns the previous value for this bit in case a caller would like to know
 * what the value was prior to this operation.
 */
bool
bitmap_clear(bitmap_t *map, uint32_t index)
{
	bool ret;
	int byte = index / BITS_PER_BYTE;
	uint8_t bit = index % BITS_PER_BYTE;

	assert(map != NULL);
	assert(index < map->num_bits);

	ret = get_bit(map->data[byte], bit);
	clear_bit(&map->data[byte], bit);
	return (ret);
}

static void
print_byte(uint8_t byte)
{
	int i;

	for (i = BITS_PER_BYTE - 1; i >= 0; i--)
		printf("%d", get_bit(byte, i) ? 1 : 0);
}

static bool
get_bit(uint8_t byte, uint8_t index)
{
	assert(index >= 0 && index < BITS_PER_BYTE);

	return ((byte & (1 << index)) != 0);
}

static void
set_bit(uint8_t *byte, uint8_t index)
{
	assert(byte != NULL);
	assert(index >= 0 && index < BITS_PER_BYTE);

	*byte = (*byte | (1 << (BITS_PER_BYTE - index - 1)));
}

static void
clear_bit(uint8_t *byte, uint8_t index)
{
	assert(byte != NULL);
	assert(index >= 0 && index < BITS_PER_BYTE);

	*byte = (*byte & ~(1 << (BITS_PER_BYTE - index - 1)));
}

#endif	/* _BITMAP_H */
