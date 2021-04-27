#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

#define	ABS(x)	((x) < 0 ? ((x) * -1) : (x))

ostream &
operator<<(ostream &out, const vector<string> &vs)
{
	int i;

	for (i = 0; i < vs.size(); i++)
		out << vs[i] << endl;

	return (out);
}

bool
is_one_away(string &longer, string &shorter)
{
	int i;

	if (longer.size() - shorter.size() != 1)
		return (false);

	for (i = 0; i < longer.size(); i++) {
		string tmp = longer;
		tmp.erase(tmp.begin() + i);
		if (tmp == shorter)
			return (true);
	}
	return (false);
}

bool
compare(const string &lhs, const string &rhs)
{
	return (lhs.size() < rhs.size());
}

int
longest_chain_impl(vector<string> &vs, int offset, vector<string> &ss)
{
	int len = 0;
	int i;

	if (offset >= vs.size())
		return (ss.size());

	if (ss.size() == 0 || is_one_away(vs[offset], ss[ss.size() - 1])) {
		vector<string> tmp = ss;
		tmp.push_back(vs[offset]);
		len = longest_chain_impl(vs, offset + 1, tmp);
	}

	return (std::max(longest_chain_impl(vs, offset + 1, ss), len));
}

int
longest_chain(vector<string> &vs)
{
	vector<string> tmp;

	std::sort(vs.begin(), vs.end(), compare);
	return (longest_chain_impl(vs, 0, tmp));
}

int main(int argc, char **argv)
{
	int i, j;
	string s1 = "abcdefg";
	string s2 = "abcdef";
	vector<string> vs1 = {
		"bdca",
		"a",
		"bca",
		"b",
		"ba",
		"bda"
	};

	vector<string> vs2 = {
		"xbc",
		"pcxbcf",
		"xb",
		"cxbc",
		"pcxbc"
	};

	cout << longest_chain(vs2) << endl;

	return (0);
}
