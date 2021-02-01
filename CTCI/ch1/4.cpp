#include <iostream>
#include <map>
#include <cassert>

using namespace std;


bool
palindrome_permutation(char *str, int len)
{
	int i;
	char tmp[len];
	map<char, int> m;

	bzero(tmp, len);

	for (i = 0; i < len; i++) {
		char c = tolower(str[i]);

		if (isalpha(c) == 0)
			continue;

		if (m.find(c) != m.end())
			m.erase(c);
		else
			m[c] = 1;
	}

	return (m.size() <= 1);
}

int main(int argc, char **argv)
{
	char *str = argv[1];

	if (palindrome_permutation(str, strlen(str)))
		cout << str << " is a permutation of a palindrome." << endl;
	else
		cout << str << " is not a permutation of a palindrome." << endl;

	return (0);
}
