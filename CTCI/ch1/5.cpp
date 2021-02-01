#include <iostream>
#include <cassert>

using namespace std;

bool
one_away(char *s1, char *s2)
{
	char *larger;
	char *smaller;
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	int len;
	int i, j;
	bool strike = false;

	if (abs(len1 - len2) > 1)
		return (false);

	larger = len1 >= len2 ? s1 : s2;
	smaller = larger == s1 ? s2 : s1;

	i = j = 0;

	while (i < strlen(smaller)) {
		if (smaller[i] != larger[j]) {
			if (strike)
				return (false);

			/*
			 * That's strike one!  Better not let it happen
			 * again!
			 */
			strike = true;
			j++;
			if (len1 == len2)
				i++;
			continue;
		}

		i++;
		j++;
	}
	return (true);
}

int main(int argc, char **argv)
{
	char *s1 = argv[1];
	char *s2 = argv[2];

	if (one_away(s1, s2))
		cout << s1 << " is one edit away from " << s2 << endl;
	else
		cout << s1 << " is NOT one edit away from " << s2 << endl;

	return (0);
}
