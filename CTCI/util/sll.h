#ifndef	SINGLY_LINKED_LIST_H
#define	SINGLY_LINKED_LIST_H


#include <iostream>
#include <assert.h>

using namespace std;

template <class T>
class node {
public:
	node(void);
	node(T);
	~node(void);

	node *next;
	T val;

	template <class U>
	friend ostream &operator <<(ostream &, const node<U> &);
};

template <class T>
node<T>::node(void)
{
	next = NULL;
}

template <class T>
node<T>::node(T v)
{
	val = v;
	next = NULL;
}

template <class T>
node<T>::~node()
{
	val.~T();
	next = NULL;
}

template <class U>
ostream &
operator <<(ostream &out, const node<U> &n)
{
	out << n.val;
	return (out);
}

template <class T>
class linkedlist {
public:
	linkedlist(void);
	~linkedlist(void);

	/* Public modifiers. */
	void push_front(T);
	void push_back(T);
	void pop_front(void);
	void pop_back(void);
	void ordered_insert(T);
	void reverse(void);
	void append(linkedlist<T> &);

	/* Public accessors. */
	node<T> *get_head(void) const;
	node<T> *get_tail(void) const;
	node<T> *get_at(int) const;
	int size(void) const;

	/* Friends. */
	template <class U>
	friend ostream &operator <<(ostream &, const node<U> &);

	node<T> *head;
};

template <class T>
linkedlist<T>::linkedlist(void)
{
	head = NULL;
}

template <class T>
linkedlist<T>::~linkedlist(void)
{
	node<T> *pn = head;
	node<T> *tmp;

	while (pn != NULL) {
		tmp = pn;
		pn = pn->next;
		delete tmp;
	}
}

template <class T>
void
linkedlist<T>::push_front(T elem)
{
	node<T> *pn = new node<T>(elem);

	assert(pn != NULL);
	pn->next = head;
	head = pn;
}

template <class T>
void
linkedlist<T>::push_back(T elem)
{
	node<T> *pn = new node<T>(elem);
	node<T> *tail;

	assert(pn != NULL);

	if ((tail = get_tail()) == NULL) {
		head = pn;
		return;
	}

	tail->next = pn;
}

template <class T>
void
linkedlist<T>::pop_front(void)
{
	node<T> *tmp = head;

	if (head == NULL)
		return;

	head = head->next;
	delete tmp;	
}

template <class T>
void
linkedlist<T>::pop_back(void)
{
	node<T> *tail;
	node<T> *tmp;

	if (head == NULL)
		return;

	tail = get_tail();

	if (tail == head) {
		delete head;
		head = NULL;
		return;
	}

	for (tmp = head; tmp->next != tail; tmp = tmp->next);

	tmp->next = NULL;
	delete tail;
}

template <class T>
void
linkedlist<T>::ordered_insert(T elem)
{
	node<T> *cur;
	node<T> *pn = new node<T>(elem);

	if ((cur = head) == NULL || pn->val <= head->val) {
		pn->next = head;
		head = pn;
		return;
	}

	for (; cur->next != NULL && cur->next->val < pn->val; cur = cur->next);

	pn->next = cur->next;
	cur->next = pn;
}

template <class T>
void
linkedlist<T>::reverse(void)
{
	linkedlist<T> tmp;
	T elem;

	while (head != NULL) {
		elem = head->val;
		pop_front();
		tmp.push_front(elem);
	}

	head = tmp.head;
	tmp.head = NULL;
}

template <class T>
node<T> *
linkedlist<T>::get_tail(void) const
{
	node<T> *pn;

	if (head == NULL)
		return (NULL);

	for (pn = head; pn->next != NULL; pn = pn->next);
	return (pn);
}

template <class T>
node<T> *
linkedlist<T>::get_at(int idx) const
{
	int i;
	node<T> *pn;

	for (i = 0, pn = head; i < idx; pn = pn->next, i++)
		assert(pn != NULL);

	return (pn);
}

template <class T>
int
linkedlist<T>::size(void) const
{
	int i;
	node<T> *pn;

	for (i = 0, pn = head; pn != NULL; pn = pn->next, i++);
	return (i);
}

template <class U>
ostream &
operator <<(ostream &out, const linkedlist<U> &l)
{
	node<U> *pn;

	for (pn = l.head; pn != NULL; pn = pn->next)
		out << *pn << " ";

	return (out);
}

#endif	/* SINGLY_LINKED_LIST_H_ */
