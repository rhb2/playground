#include <iostream>
#include <vector>


using namespace std;

ostream &
operator<<(ostream &out, const vector<int> &v)
{
	int i;

	for (i = 0; i < v.size(); i++)
		out << "(" << v[i] << ", " << i << ") ";

	return (out);
}

bool
is_safe(int row, int col, vector<int> &placed)
{
	int i;
	int r, c;

	for (r = 0; r < placed.size(); r++) {
		c = placed[r];
		int delta_row = abs(r - row);
		int delta_col = abs(c - col);
		if (delta_row == delta_col || col == c)
			return (false);
	}
	return (true);
}

bool
place_queen(vector<int> &placed, int row)
{
	int col;

	if (placed.size() == 8)
		return (true);

	for (col = 0; col < 8; col++) {
		if (!is_safe(row, col, placed))
			continue;

		placed.push_back(col);

		if (place_queen(placed, row + 1))
			return (true);

		/*
		 * Well that apprently didn't work.  We will need to try
		 * moving the current queen over by a column.  Take it
		 * out of the "placed" list.
		 */
		placed.pop_back();
	}

	return (false);
}

int main(void)
{
	vector<int> placed;
	(void) place_queen(placed, 0);
	cout << placed << endl;
	return (0);
}
