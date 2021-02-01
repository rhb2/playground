#ifndef	STACK_H_
#define	STACK_H_

#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

template <class T>
class stack {
public:
	stack(void);
	~stack(void);

	/* Accessors and modifiers */
	void push(T);
	void pop(void);
	T top(void);
	int size(void);

	/* Friends. */
	template <class U>
	friend ostream &operator <<(ostream &, const stack<U> &);

	vector<T> data;
};

template <class T>
stack<T>::stack(void)
{}

template <class T>
stack<T>::~stack(void)
{}

template <class T>
void
stack<T>::push(T elem)
{
	data.push_back(elem);
}

template <class T>
void
stack<T>::pop(void)
{
	if (data.size() == 0)
		return;

	data.pop_back();
}

template <class T>
T
stack<T>::top(void)
{
	assert(data.size() != 0);
	return (data.back());
}

template <class T>
int
stack<T>::size(void)
{
	return (data.size());
}

template <class U>
ostream &
operator <<(ostream &out, const stack<U> &s)
{
	int i;

	for (i = 0; i < s.data.size(); i++)
		out << s.data.at(i) << " ";

	return (out);
}

#endif	/* STACK_H_ */
