#include <iostream>
#include <stack>

using namespace std;

ostream &
operator<<(ostream &out, const stack<int> &s)
{
	stack<int> tmp = s;

	while (!tmp.empty()) {
		out << tmp.top() << " ";
		tmp.pop();
	}

	return (out);
}

/*
 * Moves one disc from one tower to another.
 */
void
move(stack<int> &src, stack<int> &dst)
{
	dst.push(src.top());
	src.pop();
}

void
towers(int n, stack<int> &src, stack<int> &dst, stack<int> &buffer)
{
	if (n <= 0)
		return;

	/* Move all discs but the bottom one to buffer. */
	towers(n - 1, src, buffer, dst);

	/* Take the final disc and place it on its intended destination. */
	move(src, dst);

	/*
	 * Finally, take the n - 1 discs that are sitting on buffer currently,
	 * and move them to dst.  Since src is empty, it can now be used as the
	 * the new buffer.
	 */
	towers(n - 1, buffer, dst, src);
}

int main(int argc, char **argv)
{
	int i;
	stack<int> s1, s2, s3;

	for (i = atoi(argv[1]) - 1; i >= 0; i--)
		s1.push(i);

	towers(s1.size(), s1, s2, s3);

	cout << s2 << endl;
	return (0);
}
