#include <iostream>
#include <string>

using namespace std;

bool
validate_for_length(string &s, string &tmp)
{
	int i;

	for (i = 0; i < s.size(); i += tmp.size()) {
		string s2 = string(s.begin() + i, s.begin() + i + tmp.size());
		if (tmp != s2)
			return (false);
	}	

	return (true);
}

int
patterned_string(string &s)
{
	int i;
	string tmp;

	for (i = 1; i < s.size(); i++) {
		string tmp(s.begin(), s.begin() + i);
		cout << tmp << endl;

		if (validate_for_length(s, tmp))
			break;
	}

	return (i);
}

int main(int argc, char **argv)
{
	//string s = "ABCABCABC";
	string s = "AAABAAAB";

	cout << patterned_string(s) << endl;

	return (0);
}
