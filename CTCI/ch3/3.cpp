#include <iostream>
#include <vector>
#include <stack>

using namespace std;

template <class T>
class set_of_stacks {
public:
	set_of_stacks(void);
	set_of_stacks(int);
	~set_of_stacks(void);

	void push(T);
	void pop(void);
	void pop_at(int);
	int size(void);
	int size_at(void);

	template <class U>
	friend ostream &operator <<(ostream &, const set_of_stacks<U> &);

	int threshold;
	vector<vector<T>> stacks;
};

template <class T>
set_of_stacks<T>::set_of_stacks(void)
{
	threshold = 5;
}

template <class T>
set_of_stacks<T>::set_of_stacks(int thresh)
{
	threshold = thresh;
}

template <class T>
set_of_stacks<T>::~set_of_stacks(void)
{

}

template <class T>
void
set_of_stacks<T>::push(T elem)
{
	int i, j;


	if (stacks.size() == 0 || stacks.back().size() == threshold) {
		vector<T> newstack;
		stacks.push_back(newstack);
	}

	stacks.back().push_back(elem);
}

template <class T>
void
set_of_stacks<T>::pop(void)
{
	if (stacks.size() == 0)
		return;

	stacks.back().pop_back();

	if (stacks.back().size() == 0)
		stacks.erase(stacks.begin() + (stacks.size() - 1));
}

template <class T>
void
set_of_stacks<T>::pop_at(int index)
{
	/* lol */
	if (index < 0 || stacks.size() < index)
		return;

	stacks.at(index).pop_back();

	if (stacks.at(index).size() == 0)
		stacks.erase(stacks.begin() + index);
}

template <class U>
ostream &
operator <<(ostream &out, const set_of_stacks<U> &ss)
{
	int i, j;

	for (i = 0; i < ss.stacks.size(); i++) {
		out << "Stack #" << i << ": ";

		for (j = 0; j < ss.stacks.at(i).size(); j++)
			cout << ss.stacks.at(i).at(j) << " ";

		cout << endl;
	}

	return (out);
}

int main(int argc, char **argv)
{
	int total = atoi(argv[1]);
	int i;
	set_of_stacks<int> ss;

	for (i = 0; i < total; i++)
		ss.push(i);

	cout << ss << endl;

	for (i = 0; i < total; i++) {
		ss.pop_at(0);
		cout << ss << endl;
	}
	return (0);
}
