#include <iostream>
#include <queue>
#include <cassert>

using namespace std;

typedef struct pair {
	int num;
	char c;
} pair_t;

char *
compress(char *str, int len)
{
	int i;
	pair_t p;
	char *s = str;
	queue<pair_t> q;

	assert(str != NULL);
	
	bzero(&p, sizeof (pair_t));
	len = strlen(str);

	p.c = str[0];
	p.num++;

	for (i = 1; i < len; i++) {
		if (str[i] == str[i - 1]) {
			p.num++;
			continue;
		}

		q.push(p);
		p.c = str[i];
		p.num = 1;
	}
	q.push(p);

	if (2 * q.size() >= len)
		return (str);

	while (!q.empty()) {
		p = q.front();
		s += sprintf(s, "%c%d", p.c, p.num);
		q.pop();
	}

	return (str);
}

int main(int argc, char **argv)
{
	int len = strlen(argv[1]);
	char *str = (char *) malloc(sizeof (len));
	
	assert(str != NULL);

	(void) memcpy(str, argv[1], len);
	compress(str, len);

	cout << str << endl;
	return (0);
}
