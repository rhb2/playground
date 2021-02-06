#include <iostream>
#include <vector>
#include <string>

using namespace std;

ostream &
operator<<(ostream &out, const string &s)
{
	int i;

	for (i = 0; i < s.size(); i++)
		cout << s[i] << " ";

	return (out);
}

void
get_next(string &vs, vector<string> &ps, int iteration)
{
	int i;
	vector<string> tmp = ps;

	for (i = 0; i < tmp.size(); i++)
		tmp[i] += vs[iteration];

	ps.insert(ps.end(), tmp.begin(), tmp.end());
}

void
powerset(string &s)
{
	int i;
	vector<string> ps = {""};

	for (i = 0; i < s.size(); i++) {
		get_next(s, ps, i);
	}

	for (i = 0; i < ps.size(); i++)
		cout << ps[i] << endl;
}

int main(int argc, char **argv)
{
	string s(argv[1]);
	cout << s << endl << endl;
	powerset(s);
	return (0);
}
