#ifndef	LINKEDLIST_H_
#define	LINKEDLIST_H_

#include <iostream>
#include <cassert>

using namespace std;

template <class T>
class node {
public:
	node(void);
	node(T);
	~node(void);

	node *prev;
	node *next;
	T val;

	template <class U>
	friend ostream &operator <<(ostream &, const node<U> &);
};

template <class T>
node<T>::node(void)
{
	val = T();
	prev = next = NULL;
}

template <class T>
node<T>::node(T v)
{
	val = v;
	prev = next = NULL;
}

template <class T>
node<T>::~node()
{
	val.~T();
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

	void single_ordered_insert(T);
	void double_ordered_insert(T);

	void append(linkedlist<T> &);

	/* Public accessors. */
	node<T> *get_head(void) const;
	node<T> *get_tail(void) const;
	void set_tail(node<T> *);
	node<T> *get_at(int) const;
	int size(void);
	void set_size(int);

	/* Friends. */
	template <class U>
	friend ostream &operator <<(ostream &, const node<U> &);

private:
	node<T> *head;
	node<T> *tail;
	int elems;
};

template <class T>
linkedlist<T>::linkedlist(void)
{
	head = tail = NULL;
}

template <class T>
linkedlist<T>::~linkedlist(void)
{
	node<T> *pn = head;
	node<T> *tmp;

	if (pn != NULL && pn->next == NULL) {
		delete pn;
		return;
	}

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

	if (head == NULL) {
		head = tail = pn;
	} else {
		head->prev = pn;
	}
	head = pn;
	elems++;
}

template <class T>
void
linkedlist<T>::push_back(T elem)
{
	node<T> *pn = new node<T>(elem);

	assert(pn != NULL);

	pn->prev = tail;

	if (tail == NULL) {
		head = tail = pn;
	} else {
		tail->next = pn;
	}
	tail = pn;
	elems++;
}

template <class T>
void
linkedlist<T>::pop_front(void)
{
	node<T> *tmp = head;

	if (tmp == NULL)
		return;

	head = tmp->next;

	if (head != NULL)
		head->prev = NULL;

	if (head == NULL)
		tail = NULL;

	delete tmp;
	elems--;
}

template <class T>
void
linkedlist<T>::pop_back(void)
{
	node<T> *tmp = tail;

	if (tmp == NULL)
		return;

	tail = tmp->prev;

	if (tail != NULL)
		tail->next = NULL;

	if (tail == NULL)
		head = NULL;

	delete tmp;
	elems--;

}

/*
 * Perform an ordered insert on a singly linked list.  We still use the same
 * kind of node that a doubly linked list would use -- we just don't update
 * the prev pointer.  Why does such a mechanism exist?  Just for bullshit
 * interview problems.  In reality, especially if order matters, it's always
 * wise to use a doubly linked list.
 */
template <class T>
void
linkedlist<T>::single_ordered_insert(T elem)
{
	node<T> *cur;
	node<T> *pn = new node<T>(elem);

	if (head == NULL || head->val >= pn->val) {
		pn->next = head;
		head = pn;

		if (elems == 0)
			tail = pn;

		elems++;
		return;
	}

	for (cur = head; cur->next != NULL && cur->next->val < pn->val;
	    cur = cur->next);

	pn->next = cur->next;
	cur->next = pn;
	elems++;
}

template <class T>
void
double_ordered_insert(T elem)
{

}

template <class T>
void
linkedlist<T>::append(linkedlist<T> &l)
{
	node<T> *pn = l.get_head();

	if (tail == NULL) {
		tail = head = l.get_head();
		return;
	}

	tail->next = pn;

	if (pn != NULL)
		pn->prev = tail;
}

template <class T>
node<T> *
linkedlist<T>::get_head(void) const
{
	return (head);
}

template <class T>
node<T> *
linkedlist<T>::get_tail(void) const
{
	return (tail);
}

template <class T>
void
linkedlist<T>::set_tail(node<T> *t)
{
	tail = t;
}

template <class T>
node<T> *
linkedlist<T>::get_at(int index) const
{
	int i;
	node<T> *tmp;

	if (index < 0 || index >= elems)
		return (NULL);

	for (i = 0, tmp = head; i < index; i++)
		tmp = tmp->next;

	return (tmp);
}

template <class T>
int
linkedlist<T>::size(void)
{
	return (elems);
}

template <class T>
void
linkedlist<T>::set_size(int val)
{
	elems = val;
}

template <class U>
ostream &
operator <<(ostream &out, const linkedlist<U> &l)
{
	node<U> *pn;

	for (pn = l.get_head(); pn != NULL; pn = pn->next)
		out << *pn << " ";

	return (out);
}

#endif	/* LINKEDLIST_H_ */
