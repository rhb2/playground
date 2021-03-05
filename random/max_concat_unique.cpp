#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <bitset>

using namespace std;


bool
string_to_bitset(string &s, bitset<26> &bs)
{
	int i;
	bitset<26> b;
	char c;

	for (i = 0; i < s.size(); i++) {
		c = s[i] - 'a';
		if (bs[c])
			return (false);

		bs.set(c);
	}

	return (true);
}

/*
 * This is the heuristic I like for generating the powerset of anything.  Each
 * invocation of this function results in two additional applications: one for
 * the rest of the sequence _with_ the current element and one for the rest of
 * the sequence _without_ it.
 */
int
get_longest_impl(int offset, vector<bitset<26>> &vbs, bitset<26> bs)
{
	int with = 0;
	int without = 0;

	if (offset == vbs.size())
		return (bs.count());

	/*
	 * Get the longest string that can be created using the current word as
	 * as part of it.
	 */
	if ((bs & vbs[offset]) == 0)
		with = get_longest_impl(offset + 1, vbs, bs | vbs[offset]);

	/*
	 * Now get the longest string that can be created without using the
	 * current word.
	 */
	without = get_longest_impl(offset + 1, vbs, bs);

	/* Return whichever one is better. */
	return (max(with, without));
}

int
get_longest_unique(vector<string> &vs)
{
	int i;
	vector<bitset<26>> vbs;
	bitset<26> bs;

	/*
	 * Initially, I rolled through the array of strings and filtered out
	 * all words that had multiple occurances of a character which makes
	 * things easier when doing the heavy lifting.  From there, I created
	 * a bit map for each word, where each one is exactly 26 bits wide.
	 * From there, comparing two words to see if they have any of the same
	 * characters can be conveniently done in a single bit wise operation
	 * as opposed to a linear one where we are comparing each character.
	 * As an added benefit, the map can easily fit in a single register
	 * since unless you're using a computer from the 90's, register width
	 * is most likely 64 bits wide.  Using the bit map approach for string
	 * comparison is ultimately what made the difference between whether or
	 * not this solution was accepted on leetcode.
	 */
	for (i = 0; i < vs.size(); i++) {
		bitset<26> b;
		/*
		 * This function will return false if the word passed to it
		 * has any duplicate characters.  What that means is, we only
		 * care what the value of the bit map is (passed by reference
		 * when calling this function), when the function below returns
		 * true.
		 */
		if (string_to_bitset(vs[i], b))
			vbs.push_back(b);
	}

	return (get_longest_impl(0, vbs, bs));
}

int main(int argc, char **argv)
{
	//vector<string> vs = {"cha", "r", "act", "ers"};
	//vector<string> vs = {"a", "abc", "d", "de", "def"};
	//vector<string> vs = {"yy","bkhwmpbiisbldzknpm"};
	//vector<string> vs = {"ab","cd","cde","cdef","efg","fgh","abxyz"};
	vector<string> vs = {"abc", "def", "ghi"};

	cout << get_longest_unique(vs) << endl;
	

	return (0);
}
