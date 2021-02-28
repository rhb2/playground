#include <iostream>
#include <vector>
#include <string>

using namespace std;


int
get_mid(vector<string> &vs, int left, int right)
{
	int l, r;
	int mid = (left + right) / 2;

	if (!vs[mid].empty())
		return (mid);

	l = mid - 1;
	r = mid + 1;

	while (l >= left && r <= right) {
		if (!vs[l].empty())
			return (l);

		if (!vs[r].empty())
			return (r);

		l--;
		r++;
	}

	return (-1);
}

int
sparse_search(vector<string> &vs, string &s)
{
	int left = 0;
	int right = vs.size() - 1;
	int mid;

	while (left <= right) {
		if ((mid = get_mid(vs, left, right)) == -1)
			return (-1);

		if (s == vs[mid])
			return (mid);

		if (s < vs[mid])
			right = mid - 1;
		else
			left = mid + 1;
	}

	return (-1);
}

int main(int argc, char **argv)
{
	int i;
	vector<string> vs = {"at", "", "", "", "", "ball", "", "", "car", "",
	    "", "dad", "", ""};

	vector<string> ts = {"at", "ball", "car", "test", "wall-e", "candy"};

	for (i = 0; i < ts.size(); i++) {
		cout << ts[i] << ": " << sparse_search(vs, ts[i]) << endl;
	}

	return (0);
}
