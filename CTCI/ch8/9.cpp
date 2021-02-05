#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cassert>

using namespace std;


ostream &
operator<<(ostream &out, vector<string> &v)
{
	int i;

	for (i = 0; i < v.size(); i++)
		out << v[i] << " ";

	return (out);
}

string
insert_paren(string s, int degree)
{
	int i;
	int left = 0;
	string result = s;

	if (degree ==  0)
		return ("()" + result);

	for (i = 0; i < result.size(); i++) {
		if (result[i] == '(' && ++left == degree)
			break;
	}
	result.insert(i + 1, "()");
	return (result);
}

void
get_next(vector<string> &cur, vector<string> &next, int iteration)
{
	set<string> ss;
	string tmp;
	int i, j;

	for (i = 0; i < cur.size(); i++) {
		/*
		 * We can generate the next various strings in the next round
		 * by adding another pair of parens immediately after the first,
		 * second, third, ..., nth left parenthese that we find, and
		 * finally, adding one at the beginning.  For example:
		 *  (()) -> (()())
		 *       -> ((()))
		 *       -> ()(())
		 * Note: This algorithm actually adds the first pair to the
		 * beginning before doing the others.  This algorithm is
		 * straight outta CTCI.
		 */
		for (j = 0; j <= iteration; j++) {
			tmp = insert_paren(cur[i], j);

			if (ss.find(tmp) != ss.end())
				continue;

			ss.insert(tmp);
			next.push_back(tmp);
		}
	}
}

vector<string>
parens(int num)
{
	int i;
	vector<string> cur, next;

	cur.push_back("()");

	for (i = 1; i < num; i++) {
		get_next(cur, next, i);
		cur = next;
		next.clear();
	}

	return (cur);
}

int main(int argc, char **argv)
{
	vector<string> v;
	int total = atoi(argv[1]);

	v = parens(total);
	cout << v << endl;

	return (0);
}
