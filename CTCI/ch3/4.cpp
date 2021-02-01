#include <iostream>
#include <stack>

using namespace std;

typedef struct queue {
	stack<int> in;
	stack<int> out;
} queue_t;


void
queue_insert(queue_t *pq, int elem)
{
	if (pq->out.size() > 0) {
		while (pq->out.size() > 0) {
			pq->in.push(pq->out.top());
			pq->out.pop();
		}
	}

	pq->in.push(elem);
}

bool
queue_remove(queue_t *pq, int *elem)
{
	assert(elem != NULL);

	if (pq->in.size() == 0 && pq->out.size() == 0)
		return (false);

	if (pq->in.size() > 0) {
		while (pq->in.size() > 0) {
			pq->out.push(pq->in.top());
			pq->in.pop();
		}
	}

	*elem = pq->out.top();
	pq->out.pop();
	return (true);
}

int main(int argc, char **argv)
{
	queue_t q;
	int i;
	int val;
	int total = atoi(argv[1]);

	for (i = 0; i < total; i++) {
		cout << i << " ";
		queue_insert(&q, i);
	}

	cout << endl;

	while (queue_remove(&q, &val))
		cout << val << " ";

	cout << endl;
	return (0);
}
