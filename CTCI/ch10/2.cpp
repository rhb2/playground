#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

/*
 * This function will be used as the "less than" relational operation by
 * the stl sort function.  This is not much different than the "less-than"
 * operator which would be used by default, but we need to hijack that
 * operation with a custom one of our own that sorts the characters in both
 * strings before doing the normal comparison.  This essentially gaurantees
 * that strings that are anagrams of each other will be viewed as equal
 * value elements when doing the less-than-comparison, thus resulting in a
 * vector where all anagrams are next to each other.
 */
bool
less_than(string s1, string s2)
{

	std::sort(s1.begin(), s1.end());
	std::sort(s2.begin(), s2.end());

	return (s1 < s2);
}

int main(void)
{
	int i;

	vector<string> vs = {
		"wall-e",
		"loves",
		"food",
		"e-wall",
		"slove",
		"dofo",
		"doof",
		"ovesl",
		"-llawe",
	};

	sort(vs.begin(), vs.end(), less_than);

	for (i = 0; i < vs.size(); i++)
		cout << vs[i] << endl;
 
	return (0);
}
