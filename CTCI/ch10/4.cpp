#include <iostream>
#include <vector>

using namespace std;

class Listy {
public:
	Listy(void) {};
	Listy(int, int);
	~Listy(void){};

	int elementAt(int);
	int indexOf(int);

	vector<int> v;

private:
	int get_at(int);
};

ostream &
operator<<(ostream &out, const Listy &l)
{
	int i;

	for (i = 0; i < l.v.size(); i++)
		out << l.v[i] << " ";

	return (out);
}

Listy::Listy(int start, int end)
{
	int i;

	for (i = start; i <= end; i++)
		v.push_back(i);
}

int
Listy::get_at(int i)
{
	if (i >= v.size())
		return (-1);

	return (v[i]);
}

int
Listy::indexOf(int i)
{
	int left = 0;
	int right = INT_MAX;

	/*
	 * It's important to note that this loop must continue until either
	 * the value is found or left == right.  For that reason, remember to
	 * use the <= operator, not the < operator.  Failure to understand the
	 * difference in this algorithm will result in success for arrays that
	 * are of odd lengths only.
	 */
	while (left <= right) {
		/* Has to be done the hard way to prevent overflow. */
		int middle = ((right - left) / 2) + left;
		int elem = get_at(middle);

		if (elem == i)
			return (middle);

		if (elem == -1 || elem > i)
			right = middle - 1;
		else
			left = middle + 1;
	}

	return (-1);
}


int main(int argc, char **argv)
{
	int i;
	Listy l(0, 20);

	for (i = 0; i < 30; i++)
		cout << l.indexOf(i) << endl;

	return (0);
}
