#include <iostream>
#include <vector>

using namespace std;


int count_steps(int, int, vector<int> &);

ostream &
operator <<(ostream &out, const vector<int> &steps)
{
	int i;

	for (i = 0; i < steps.size(); i++)
		cout << steps[i] << " ";

	return (out);
}

int count_steps_impl(int total, int cur, int step, vector<int> &steps)
{
	int sum;
	steps.push_back(step);
	sum = count_steps(total, cur + step, steps);
	steps.pop_back();
	return (sum);
}

/*
 * I decided to take this problem a step further and not just count the number
 * of different ways that it can be done, but show them as well.  This helps
 * me to better understand exactly how it's happening.
 */
int
count_steps(int total, int cur, vector<int> &steps)
{
	int sum;

	if (cur > total)
		return (0);

	if (cur == total) {
		cout << steps << endl;
		return (1);
	}

	sum = count_steps_impl(total, cur, 1, steps);
	sum += count_steps_impl(total, cur, 2, steps);
	sum += count_steps_impl(total, cur, 3, steps);
	return (sum);
}

int main(int argc, char **argv)
{
	int total = atoi(argv[1]);
	vector<int> steps;

	cout << "Number of different ways: " << endl
	    << count_steps(total, 0, steps)
	    << endl;
	return (0);
}
