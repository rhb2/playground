#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

bool
string_to_bool(string &s)
{
	return (s == "1");
}

string
bool_to_string(bool b)
{
	return (b ? "1" : "0");
}

string
substring(string &s, int left, int right)
{
	string result(s.begin() + left, s.begin() + right);
	return (result);
}

int
count_eval_impl(string s, bool result, map<string, int> &m)
{
	int i;
	int ways = 0;
	string tmp = bool_to_string(result) + s;

	if (s.size() == 0)
		return (0);

	if (s.size() == 1)
		return (string_to_bool(s) == result ? 1 : 0);

	if (m.find(tmp) != m.end())
		return (m[tmp]);

	for (i = 1; i < s.size(); i += 2) {
		char c = s[i];
		string left = substring(s, 0, i);
		string right = substring(s, i + 1, s.size());
		int ltrue = count_eval_impl(left, true, m);
		int lfalse = count_eval_impl(left, false, m);
		int rtrue = count_eval_impl(right, true, m);
		int rfalse = count_eval_impl(right, false, m);
		int total = (ltrue + lfalse) * (rtrue + rfalse);

		int total_true = 0;

		if (c == '^') {
			total_true = ltrue * rfalse + lfalse * rtrue;
		} else if (c == '&') {
			total_true = ltrue * rtrue;
		} else if (c == '|') {
			total_true = ltrue * rtrue + lfalse * rtrue +
			    ltrue * rfalse;
		}

		int sub_ways = result ? total_true :  total - total_true;
		ways += sub_ways;
	}
	m[tmp] = ways;
	return (ways);
}

int
count_eval(string &s, bool result)
{
	map<string, int> m;

	return (count_eval_impl(s, result, m));
}

int main(int argc, char **argv)
{
	string expr(argv[1]);
	int result = atoi(argv[2]);
	bool b = (result > 0);
	cout << count_eval(expr, b) << endl;

	return (0);
}
