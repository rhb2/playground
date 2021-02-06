#include <iostream>
#include <vector>
#include <map>

using namespace std;


int
find_ways_impl(vector<int> &denoms, int amount, int offset,
    map<pair<int, int>, int> &m)
{
	int i;
	int ways = 0;
	pair<int, int> p(offset, amount);

	/* Dynamic programming for the win! */
	if (m.find(p) != m.end())
		return (m[p]);

	if (amount == 0)
		return (1);

	if (amount < 0 || offset >= denoms.size())
		return (0);

	for (i = 0; i * denoms[offset] <= amount; i++) {
		int sub_amt = i * denoms[offset];
		int new_amt = amount - sub_amt;
		ways += find_ways_impl(denoms, new_amt, offset + 1, m);
	}

	m[p] = ways;
	return (ways);
}

int
find_ways(vector<int> &denoms, int amount)
{
	int i;
	map<pair<int, int>, int> m;

	return (find_ways_impl(denoms, amount, 0, m));
}

int main(int argc, char **argv)
{
	int amount = atoi(argv[1]);
	vector<int> denoms = {1, 5, 10, 25};

	cout << find_ways(denoms, amount) << endl;
	return (0);
}
