#include <iostream>
#include <bitset>

using namespace std;


unsigned int
bitswap(unsigned int x)
{
	unsigned int mask = 0xAAAAAAAA;
	unsigned int evens = ((x & mask) >> 1);
	unsigned int odds = ((x & ~mask) << 1);

	return (evens | odds);
}

int main(void)
{
	bitset<32> bs;
	unsigned int x = 0b0000011001100110;

	bs = x;
	cout << bs << endl;

	bs = bitswap(x);
	cout << bs << endl;

	return (0);
}
