#include <iostream>
#include <bitset>

using namespace std;


/*
 * Of course, this function could be greatly shortened, but it is written
 * this way for education purposes so that I can review this later and easily
 * understand exactly how to zero out a window.
 */
int
create_window_zeros(int least, int most)
{
	int len = abs(most - least);
	int x = -1;

	x = (x << len);
	x = ~x;
	x = (x << least);
	x = ~x;
	return (x);
}

int
insertion(int x, int y, int least, int most)
{
	int window_mask = create_window_zeros(least, most);
	x = (x & window_mask);
	x = (x | (y << least));
	return (x);
}

int main(int argc, char **argv)
{
	int j = (1 << 30);
	bitset<32> bs;

	j = -1;//INT_MAX;
	bs = (j >>> 1);
	cout << bs << endl;
	return (0);
}
