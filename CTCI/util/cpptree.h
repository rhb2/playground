#ifndef TREE_H_
#define	TREE_H_

#include <queue>
#include <string>
#include <cassert>

using namespace std;


template <class T>
class node {
public:
	node(void);
	node(T);
	~node(void);

	T val;
	node *parent;
	node *left;
	node *right;	
};

template <class T>
node<T>::node(void)
{
	left = right = parent = NULL;
}

template <class T>
node<T>::node(T elem)
{
	val = elem;
	left = right = parent = NULL;
}

template <class T>
node<T>::~node(void)
{
	left = right = parent = NULL;
}

template <class T>
ostream &
operator <<(ostream &out, const node<T> &pn)
{
	out << pn.val;
	return (out);
}

template <class T>
static int get_height(node<T> *);

template <class T>
static int get_balance(node<T> *);

template <class T>
static void rotate_left(node<T> **);

template <class T>
static void rotate_right(node<T> **);

template <class T>
static void perform_balance(node<T> **);

template <class T>
void
rotate_left(node<T> **ppn)
{
	node<T> *root = *ppn;
	node<T> *right;

	if (root == NULL)
		return;

	right = root->right;
	root->right = right->left;
	right->left = root;
	*ppn = right;
}

template <class T>
void
rotate_right(node<T> **ppn)
{
	node<T> *root = *ppn;
	node<T> *left;

	if (root == NULL)
		return;

	left = root->left;
	root->left = left->right;
	left->right = root;
	*ppn = left;
}

template <class T>
static int
get_height(node<T> *pn)
{
	int left, right;

	if (pn == NULL)
		return (0);

	left = get_height(pn->left);
	right = get_height(pn->right);
	return (1 + max(left, right));
}

template <class T>
static int
get_balance(node<T> *pn)
{
	int left, right;

	if (pn == 0)
		return (0);

	return (get_height(pn->left) - get_height(pn->right));
}

template <class T>
static void
perform_balance(node<T> **ppn)
{
	node<T> *root;
	int balance;

	assert(ppn != NULL);

	if ((root = *ppn) == NULL)
		return;

	balance = get_balance(root);

	if (balance == 2) {
		if (get_balance(root->right) == -1)
			rotate_left(&root->right);
		rotate_right(ppn);
	} else if (balance == -2) {
		if (get_balance(root->left) == 1)
			rotate_right(&root->left);
		rotate_left(ppn);
	}
}

template <class T>
class tree {
public:
	tree(void);
	~tree(void);

	void insert(T);
	node<T> *root;
	int elems;
};

template <class T>
tree<T>::tree(void)
{
	root = NULL;
}

template <class T>
tree<T>::~tree(void)
{
	node<T> *pn;
	queue<node<T> *> q;

	if (root == NULL)
		return;

	q.push(root);

	while (!q.empty()) {
		pn = q.front();
		q.pop();

		if (pn->left)
			q.push(pn->left);
		if (pn->right)
			q.push(pn->right);
		delete (pn);
	}

	root = NULL;
}

template <class T>
void
insert_impl(node<T> **ppn, node<T> *pn)
{
	node<T> *root;
	node<T> **child;

	assert(ppn != NULL && pn != NULL);

	if ((root = *ppn) == NULL) {
		*ppn = pn;
		return;
	}

	child = (pn->val >= root->val) ? &root->right : &root->left;
	insert_impl(child, pn);
	perform_balance(ppn);
}

template <class T>
void
tree<T>::insert(T elem)
{
	node<T> *pn;

	pn = new node<T>(elem);

	assert(pn != NULL);

	insert_impl(&root, pn);
}

template <class T>
void
print_helper(ostream &out, node<T> *pn, int level)
{
	int i;
	string delim = "   ";

	if (pn == NULL)
		return;

	print_helper(out, pn->left, level + 1);

	for (i = 0; i < level; i++)
		out << delim;
	out << pn->val << endl;

	print_helper(out, pn->right, level + 1);
}

template <class T>
ostream &
operator <<(ostream &out, const tree<T> &t)
{
	print_helper(out, t.root, 0);
	return (out);
}

#endif	/* TREE_H_ */
