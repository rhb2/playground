#include <iostream>
#include <map>
#include <vector>

using namespace std;


typedef struct pair {
	char c;
	int n;
} pair_t;

bool
compare(pair_t &p1, pair_t &p2)
{
	return (p1.n > p2.n);
}

int
distribute(vector<pair_t> &v, char *str, int offset, int len)
{
	int i;

	for (i = 0; i < v.size(); i++) {
		str[offset] = v[i].c;
		v[i].n--;
		offset++;

		if (v[i].n == 0)
			v.erase(v.begin() + i);
	}

	return (offset);
}

void
rearrange(char *str, int len)
{
	int i;
	map<char, int> m;
	map<char, int>::iterator im;
	vector<pair_t> v;
	int offset = 0;

	for (i = 0; i < len; i++) {
		if (m.find(str[i]) == m.end())
			m[str[i]] = 1;
		else
			m[str[i]]++;
	}

	for (im = m.begin(); im != m.end(); im++) {
		pair_t p;

		p.c = im->first;
		p.n = im->second;
		v.push_back(p);
	}

	std::sort(v.begin(), v.end(), compare);

	while (v.size() != 0)
		offset = distribute(v, str, offset, len);
}

int main(void)
{
	char str[] = {'a', 'a', 'b', 'b', 'b', 'b', 'c', 'c', 'c', '\0'};

	rearrange(str, strlen(str) - 1);
	cout << str << endl;

	return (0);
}
