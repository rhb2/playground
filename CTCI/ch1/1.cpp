#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <cassert>

using namespace std;

/*
 * This is the easy way.  Use the hashmap.  O(n).
 */
bool
has_dupes(char *str, int len)
{
	int i;
	map<char, int> m;

	assert(str != NULL);	

	for (i = 0; i < len; i++) {
		if (m.find(str[i]) != m.end())
			return (true);

		m[str[i]] = 1;
	}

	return (false);
}

/*
 * This is the hard way.  In place, no auxiliary data structures.  Sort it
 * first, then scan linearly for dupes.  O(n * log n) + n.
 */
bool
has_dupes_hard(char *str, int len)
{
	int i;

	assert(str != NULL);

	sort(str, str + len);

	for (i = 1; i < len; i++) {
		if (str[i] == str[i - 1])
			return (true);
	}

	return (false);
}

int main(int argc, char **argv)
{
	int i;
	char *str = argv[1];

	if (has_dupes_hard(str, strlen(str)))
		cout << str << " has dupes." << endl;
	else
		cout << str << " does not have dupes." << endl;

	return (0);
}
