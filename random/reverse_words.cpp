#include <iostream>
#include <map>
#include <string>

using namespace std;

void
reverse_range(string &s, int left, int right)
{
	while (left < right) {
		s[left] = (s[left] + s[right]) - (s[right] = s[left]);
		left++;
		right--;
	}
}

int main(void)
{
	int i = 0;
	int last = 0;
	map<char, int> m;
	string s = "abcd efg hijk lmnop qrs tuv w x y z";

	reverse_range(s, 0, s.size() - 1);

	while ((i = s.find(' ', i)) != -1) {
		reverse_range(s, last, i - 1);
		i++;
		last = i;
	}

	reverse_range(s, last, s.size() - 1);
	cout << s << endl;

	return (0);
}
