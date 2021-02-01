#include <iostream>
#include <string>
#include <bitset>

using namespace std;

string
binary_to_string(double x)
{
	string s;

	if (x >= 1 || x < 0)
		return ("Error");

	s = s + '.';

	while (x > 0) {
		if (s.size() > 64)
			return ("Error");

		double tmp = x * 2;

		if (tmp >= 1) {
			s.append("1");
			x = tmp - 1;
		} else {
			s.append("0");
			x = tmp;
		}
	}

	return (s);	
}

int main(void)
{
	double x = .15625;

	cout << binary_to_string(x) << endl;
	return (0);
}
