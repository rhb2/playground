#include <iostream>
#include <string>
#include <cassert>

using namespace std;

bool
is_rotation(string s1, string s2)
{
	string ss = s2 + s2;

	return (ss.find(s1) != string::npos);
}


int main(int argc, char **argv)
{
	string s1(argv[1]);
	string s2(argv[2]);

	if (is_rotation(s1, s2))
		cout << s1 << " is a rotation of " << s2 << endl;
	else
		cout << s1 << " is not a rotation of " << s2 << endl;

	return (0);
}
