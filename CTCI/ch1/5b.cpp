#include <iostream>


using namespace std;


bool
one_away_diff_len(char *s, char *l)
{
	int i, j;

	for (i = 0, j = 0; i < strlen(s); i++, j++)
		if (s[i] != l[j] && ++j > i + 1)
			return (false);

	return (true);
}

bool
one_away_same_len(char *s1, char *s2)
{
	int i, diffs;
	int len = strlen(s1);

	if (strncmp(s1, s2, len) == 0)
		return (false);

	for (i = 0, diffs = 0; i < len; i++)
		if (s1[i] != s2[i] && ++diffs > 1)
			return (false);

	return (true);
}

bool
one_away(char *s1, char *s2)
{
	char *l, *s;
	int len1, len2;
	int delta;

	len1 = strlen(s1);
	len2 = strlen(s2);

	if (len1 == len2)
		return (one_away_same_len(s1, s2));

	if ((delta = abs(len1 - len2)) > 1)
		return (false);

	l = len1 > len2 ? s1 : s2;
	s = len1 > len2 ? s2 : s1;

	return (one_away_diff_len(s, l));
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
