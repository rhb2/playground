#include <iostream>
#include <map>
#include <cassert>

using namespace std;

bool
perms(char *str1, char *str2)
{
	int i;
	int len = strlen(str1);
	map<char, int> m;

	assert(str1 != NULL && str2 != NULL);

	if (len != strlen(str2))
		return (false);

	for (i = 0; i < len; i++)
		m[str1[i]]++;

	for (i = 0; i < len; i++) {
		m[str2[i]]--;
		if (m[str2[i]] == 0)
			m.erase(str2[i]);
	}

	return (m.empty());
}

int main(int argc, char **argv)
{
	char *str1 = argv[1];
	char *str2 = argv[2];

	if (perms(str1, str2))
		cout << str1 << " is a permutation of " << str2 << endl;
	else
		cout << str1 << " is not a permutation of " << str2 << endl;

	return (0);
}
