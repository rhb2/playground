#include <iostream>
#include <bitset>

using namespace std;

int
get_next(int x)
{
	int index, i, mask;
	int ones = 0;
	bool seen_one = false;

	/*
	 * First, we need to find the index of our first non-trailing zero.
	 * This is the bit that we will set to 1.  We also need to keep track
	 * of how many ones we've seen up until this point.  We will need that
	 * information further down below.
	 */
	for (index = 0, i = 1; index < 32; index++) {
		if (i & x) {
			ones++;
			seen_one = true;
		} else if (seen_one) {
			break;
		}
		i = (i << 1);
	}

	/* Set the bit that we obtained above to 1. */
	x = (x | (1 << index));

	/*
	 * Now, zero out all bits to the right of the one that we just set to 1.
	 */	
	mask = -1;
	mask = (mask << index);
	x = (x & mask);

	/*
	 * Starting from the far right and moving left,  set exactly
	 * `ones - 1` bits to be 1.  The reason why we use `ones - 1` is
	 * because we need one less bit than we had before since we set one
	 * earlier.
	 */
	mask = -1;
	mask = (mask << (ones - 1));
	mask = ~mask;
	x = (x | mask);

	return (x);
}

int
get_previous(int x)
{
	int index, i, mask;
	int ones = 0;
	int last_zero;
	bool seen_zero = false;

	for (index = 0, i = 1; index < 32; index++) {
		if ((i & x) == 0) {
			seen_zero = true;
			last_zero = index;
		} else {
			ones++;
			if (seen_zero)
			break;
		}
		i = (i << 1);
	}

	/* Clear the bit that we obtained above. */
	mask = (1 << index);
	mask = ~mask;
	x = (x & mask);

	/* Now, set the bit at the last observed zero. */
	x = (x | (1 << last_zero));

	ones--;

	if (ones == 0)
		return (x);

	/* Zero out all values to the right of the bit that we just set. */
	mask = -1;
	mask = (mask << (last_zero - 1));
	x = (x & mask);

	/* Create a mask with the number of ones that we need. */
	mask = -1;
	mask = (mask << ones);
	mask = ~mask;

	/* Shift the fucking mask by the exact amount require */
	mask = (mask << (last_zero - ones));

	x = (x | mask);
	return (x);
}

int main(int argc, char **argv)
{
	int i;
	int cur = 7;
	bitset<32> bs;

	for (i = 0; i < 10; i++) {
		cout << cur << endl;
		cur = get_next(cur);
	}
	cout << cur << endl << endl;

	for (i = 0; i < 10; i++) {
		cout << cur << endl;
		cur = get_previous(cur);
	}
	cout << cur << endl << endl;
	return (0);
}
