#include <iostream>
#include <vector>
#include <string>

using namespace std;

void
add_parens(vector<string> &vs, string str, int lcount, int rcount)
{
	if (lcount < 0 || rcount < lcount)
		return;

	if (lcount == 0 && rcount == 0) {
		vs.push_back(str);
		return;
	}

	add_parens(vs, str + '(', lcount - 1, rcount);
	add_parens(vs, str + ')', lcount, rcount - 1);
}

vector<string>
parens(int count)
{
	vector<string> result;
	string s;

	add_parens(result, s, count, count);
	return (result);
}

int main(int argc, char **argv)
{
	int num = atoi(argv[1]);
	int i;
	vector<string> vs = parens(num);

	for (i = 0; i < vs.size(); i++)
		cout << vs[i] << endl;

	return (0);
}

