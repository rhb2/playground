#include <iostream>
#include <string>

using namespace std;


string
compress(string &str)
{
	int i;
	string result;
	pair<char, int> p;

	p.first = str[0];
	p.second = 1;

	for (i = 1; i < str.size(); i++) {
		if (p.first == str[i]) {
			p.second++;
			continue;
		}

		result += to_string(p.second) + p.first;
		p.first = str[i];
		p.second = 1;
	}

	result += to_string(p.second) + p.first;
	return (result.size() < str.size() ? result : str);
}

int main(int argc, char **argv)
{
	string s(argv[1]);
	cout << compress(s) << endl;
	return (0);
}
