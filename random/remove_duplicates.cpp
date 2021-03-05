#include <iostream>
#include <string>
#include <vector>

using namespace std;


bool
remove_duplicates_impl(string &s, int k)
{
	int i, j;
	vector<pair<char, int>> v;
	pair<char, int> p;
	bool need_trim = false;
	string result;

	if (s.size() == 0)
		return (false);

	p.first = s[0];
	p.second = 1;

	for (i = 1; i < s.size(); i++) {
		if (s[i] == p.first) {
			p.second++;
			continue;
		}

		if (p.second >= k)
			need_trim = true;

		v.push_back(p);
		p.first = s[i];
		p.second = 1;
	}

	v.push_back(p);

	for (i = 0; i < v.size(); i++) {
		if (v[i].second >= k) {
			while (v[i].second >= k)
				v[i].second -= k;
		}
	}

	if (!need_trim)
		return (false);

	/* Construct the new string. */
	for (i = 0; i < v.size(); i++) {
		if (v[i].second == 0)
			continue;

		for (j = 0; j < v[i].second; j++)
			result += v[i].first;
	}

	s = result;
	return (true);
}

string
remove_duplicates(string &s, int k)
{
	while (remove_duplicates_impl(s, k));
	return (s);
}

int main(int argc, char **argv)
{
	string s(argv[1]);
	int k = atoi(argv[2]);

	cout << remove_duplicates(s, k) << endl;
	
	return (0);
}
