#include <iostream>
#include <bitset>

using namespace std;

int
flip_to_win(int x)
{
	int cur, prev, max;

	if (x == 0)
		return (0);

	cur = prev = 0;
	max = 1;

	while (x != 0) {
		if (x & 1) {
			cur++;
		} else {
			prev = (x & 0b10) ? cur : 0;
			cur = 0;
		}
		max = std::max(prev + cur + 1, max);
		x = (x >> 1);
	}

	return (max);
}

int main(int argc, char **argv)
{
	int x = 0b1111110011;
	int longest;

	longest = flip_to_win(x);
	cout << longest << endl;

	return (0);
}
