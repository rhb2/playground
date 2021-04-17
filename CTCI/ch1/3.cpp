#include <iostream>
#include <cassert>

using namespace std;

void
swap(char *str, int x, int y)
{
	assert(str != NULL);

	str[x] = (str[x] + str[y]) - (str[y] = str[x]);
}

int
seek_left(char *str, int cur)
{
	int i;

	assert(str != NULL);

	for (i = cur; i > 0; i--)
		if (str[i] != ' ')
			break;

	return (i);
}

void
urlify(char *str, int len)
{
	int i;
	int last, cur;

	last = len - 1;

	assert(str != NULL);

	for (cur = seek_left(str, last); cur > 0; cur = seek_left(str, last)) {
		while (str[cur] != ' ')
			swap(str, cur--, last--);

		last -= 3;
		(void) memcpy(str + last + 1, "%20", 3);
	}
}

int main(int argc, char **argv)
{
	char *str = "Mr John Smith    ";
	char *str2 = (char *) malloc(strlen(str));
	(void) memcpy(str2, str, strlen(str));

	urlify(str2, strlen(str2));

	printf("%s\n", str2);
	return (0);
}
