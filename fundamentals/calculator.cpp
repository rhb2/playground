/*
 * Calculator program will parse and evaluate a parenthesized expression and
 * give an output in the form of a single number which is the result of the
 * evaluation.
 *
 * The equation is supplied in the form of a single string where operators and
 * operands are arranged in infix form.  The easiest way to solve this problem
 * is to convern the expression in to reverse polish notation, and from there,
 * solve it using a stack.  By far the most difficult part is converting from
 * infix to postfix, but ones that's done, it's pretty straight forward.  For
 * more information on how to do that, see "Data Structures and Algorithm
 * Analysis in C++" by Mark Allen Weiss, page 105.
 */
#include <iostream>
#include <vector>
#include <stack>

using namespace std;


int
get_pri(char c)
{
	int pri = 0;

	switch (c) {
	case '+':
	case '-':
		pri = 1;
		break;
	case '*':
	case '/':
		pri = 2;
		break;
	case '(':
		pri = 3;
		break;
	}

	return (pri);
}

bool
is_operator(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/' ||
	    c == '(' || c == ')');
}

void
push_operator(char op, stack<char> &stack, vector<string> &output)
{
	int pri = get_pri(op);

	if (op == ')') {
		while (stack.top() != '(') {
			output.push_back(string(1, stack.top()));
			stack.pop();
		}

		stack.pop();
		return;
	}

	while (!stack.empty() && pri <= get_pri(stack.top()) &&
	    stack.top() != '(') {
		output.push_back(string(1, stack.top()));
		stack.pop();
	}

	stack.push(op);
}

int
parse_value(vector<char> &input, int pos, string &term)
{
	while (isdigit(input[pos]))
		term += input[pos++];

	return (term.size());
}

vector<string>
infix_to_postfix(vector<char> input)
{
	int i;
	vector<string> output;
	stack<char> stack;

	for (i = 0; i < input.size(); i++) {
		char c = input[i];
		string term;

		if (is_operator(c)) {
			push_operator(c, stack, output);
		} else {
			i += parse_value(input, i, term) - 1;
			output.push_back(term);
		}
	}

	while (!stack.empty()) {
		output.push_back(string(1, stack.top()));
		stack.pop();
	}

	return (output);
}

void
perform_op(char op, stack<int> &stack)
{
	int left, right, result;

	assert(stack.size() >= 2);

	/*
	 * Note to self: Be very careful when determining which operand is
	 * on the left and which is on the right.  The one that's on the top
	 * of the stack will always be on the right since it was the one that
	 * was most recently seen.
	 */
	right = stack.top();
	stack.pop();

	left = stack.top();
	stack.pop();

	switch (op) {
	case '-':
		result = left - right;
		break;
	case '+':
		result = left + right;
		break;
	case '*':
		result = left * right;
		break;
	case '/':
		result = left / right;
		break;
	}

	stack.push(result);
}

int
evaluate_expr(vector<string> &expr)
{
	stack<int> stack;

	for (string s: expr) {
		if (is_operator(s[0])) {
			perform_op(s[0], stack);
		} else {
			stack.push(stoi(s));
		}
	}

	return (stack.top());
}

int main(int argc, char **argv)
{
	int i;
	//string strexpr("10+3*2+(9*13+17)*2");
	string strexpr("9*9+3");
	vector<char> expr(strexpr.begin(), strexpr.end());
	vector<string> output = infix_to_postfix(expr);

	cout << "Infix:   " << strexpr << endl;

	cout << "Postfix: ";
	for (i = 0; i < output.size(); i++)
		cout << output[i] << " ";
	cout << endl;

	cout << "Result:  " << evaluate_expr(output) << endl;

	return (0);
}
