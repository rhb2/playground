#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

ostream &
operator<<(ostream &out, const vector<int> &v)
{
	int i;

	for (i = 0; i < v.size(); i++)
		out << v[i] << " ";

	return (out);
}

void
merge(vector<int> &primary, vector<int> &secondary)
{
	int last = primary.size() - 1;
	int p_off = primary.size() - secondary.size() - 1;
	int s_off = secondary.size() - 1;

	while (p_off >= 0 && s_off >= 0) {
		if (primary[p_off] >= secondary[s_off])
			primary[last--] = primary[p_off--];
		else
			primary[last--] = secondary[s_off--];
	}

	while (s_off >= 0)
		primary[last--] = secondary[s_off--];
}

int main(int argc, char **argv)
{
	vector<int> empty(5);
	vector<int> primary;
	vector<int> secondary;
	int i;

	for (i = 0; i < 5; i++)
		primary.push_back(i * 2);

	for (i = 0; i < 5; i++)
		secondary.push_back(i * 3);

	primary.insert(primary.end(), empty.begin(), empty.end());
	cout << primary << endl << secondary << endl;

	merge(primary, secondary);

	cout << primary << endl;
	return (0);
	
}
