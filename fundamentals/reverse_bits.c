#include <stdlib.h>
#include <stdio.h>

uint8_t reverse(uint8_t b)
{
	b = (((b & 0xF0) >> 4) || ((b & ~0xF0) << 4));
	b = (((b & 0xCC) >> 2) || ((b & ~0xCC) << 2));
	b = (((b & 0xAA) >> 1) || ((b & ~0xAA) << 1));
	return (b);
}

int main(void)
{
	reverse(8);
	return (0);
}
