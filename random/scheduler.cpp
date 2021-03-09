/*
 * Given a characters array tasks, representing the tasks a CPU needs to do,
 * where each letter represents a different task. Tasks could be done in any
 * order. Each task is done in one unit of time. For each unit of time, the CPU
 * could complete either one task or just be idle.
 *
 * However, there is a non-negative integer n that represents the cooldown
 * period between two same tasks (the same letter in the array), that is that
 * there must be at least n units of time between any two same tasks.
 *
 * Return the least number of units of times that the CPU will take to finish
 * all the given tasks.
 */

#include <iostream>
#include <vector>
#include <map>

using namespace std;

ostream &
operator<<(ostream &out, pair<char, int> &p)
{
	out << p.first << " " << p.second;
	return (out);
}

ostream &
operator<<(ostream &out, vector<pair<char, int>> &v)
{
	int i;

	for (auto p: v)
		out << p << endl;

	return (out);
}

int
least_interval(vector<char> &tasks, int n)
{
	map<char, int> m;
	int largest = 0;
	int character;
	int idle_cycles;

	if (n == 0)
		return (0);

	for (char c : tasks) {
		m[c]++;
		largest = std::max(largest, m[c]);
	}

	for (auto p : m) {
		if (p.second == largest) {
			character = p.first;
			break;
		}
	}

	idle_cycles = n * (largest - 1);

	for (auto p : m) {
		if (p.first == character)
			continue;

		idle_cycles -= std::min(largest - 1, p.second);
	}

	return (tasks.size() + std::max(idle_cycles, 0));
}

int main(int argc, char **argv)
{
	string s(argv[1]);
	int n = atoi(argv[2]);
	vector<char> v(s.begin(), s.end());

	cout << least_interval(v, n) << endl;
	return (0);
}
