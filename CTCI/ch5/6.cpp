#include <iostream>
#include <bitset>

using namespace std;

int get_delta(int x, int y)
{
	int count = 0;
	int map = (x ^ y);

	while (map != 0) {
		map = (map & (map - 1));
		count++;
	}

	return (count);
}

int main(void)
{
	int x = 31;
	int y = 53;
	bitset<32> bs1, bs2;
	int delta;

	bs1 = x;
	bs2 = y;

	cout << bs1 << endl << bs2 << endl;
	delta = get_delta(x, y);
	cout << "delta = " << delta << endl;
	return (0);
}
