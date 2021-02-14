#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>


void
print_array(int *array, int len)
{
	int i;

	for (i = 0; i < len; i++)
		printf("%d ", array[i]);

	printf("\n");
}

void
swap(int *array, int x, int y)
{
	array[x] = (array[x] + array[y]) - (array[y] = array[x]);
}

void
quick_sort(int *array, int left, int right)
{
	int last, i;

	assert(array != NULL);

	if (left >= right)
		return;

	last = left;
	swap(array, left, (left + right) / 2);

	for (i = left + 1; i <= right; i++)
		if (array[i] <= array[left])
			swap(array, ++last, i);

	swap(array, left, last);
	quick_sort(array, left, last - 1);
	quick_sort(array, last + 1, right);	
}

static inline int
left_child(int i)
{
	return (i * 2 + 1);
}

void
sift_down(int *array, int cur, int len)
{
	int child, tmp;

	assert(array != NULL);

	for (tmp = array[cur]; left_child(cur) < len; cur = child) {
		child = left_child(cur);
		if (child != len - 1 && array[child] < array[child + 1])
			child++;

		if (tmp >= array[child])
			break;

		array[cur] = array[child];
	}

	array[cur] = tmp;
}

void
heapify(int *array, int len)
{
	int i;

	assert(array != NULL);

	for (i = len / 2; i >= 0; i--)
		sift_down(array, i, len);
}

void
heap_sort(int *array, int len)
{
	int i;

	assert(array != NULL);

	heapify(array, len + 1);

	for (i = len; i > 0; i--) {
		swap(array, 0, i);
		sift_down(array, 0, i);
	}
}

void
merge(int *array, int *tmp, int l_pos, int r_pos, int r_end)
{
	int i;
	int elems = r_end - l_pos + 1;
	int l_end = r_pos - 1;
	int tmp_pos = l_pos;

	while (l_pos <= l_end  && r_pos <= r_end) {
		if (array[l_pos] <= array[r_pos])
			tmp[tmp_pos++] = array[l_pos++];
		else
			tmp[tmp_pos++] = array[r_pos++];
	}

	while (l_pos <= l_end)
		tmp[tmp_pos++] = array[l_pos++];

	while (r_pos <= r_end)
		tmp[tmp_pos++] = array[r_pos++];

	for (i = 0; i < elems; i++, r_end--)
		array[r_end] = tmp[r_end];
}

void
m_sort(int *array, int *tmp, int left, int right)
{
	int middle;

	if (left >= right)
		return;

	middle = (left + right) / 2;
	m_sort(array, tmp, left, middle);
	m_sort(array, tmp, middle + 1, right);
	merge(array, tmp, left, middle + 1, right);
}

void
merge_sort(int *array, int len)
{
	int *tmp;

	assert(array != NULL);

	tmp = malloc(sizeof (int) * (len + 1));

	assert(tmp != NULL);

	(void) bzero(tmp, sizeof (int) * (len + 1));
	m_sort(array, tmp, 0, len);
}

void
help_check(int *array, int len)
{
	int i;

	for (i = 0; i < len - 1; i++)
		assert(array[i] <= array[i + 1]);
}

int main(int argc, char **argv)
{
	int i;
	int len;
	int *array;

	assert(argc == 2);

	len = atoi(argv[1]);
	array = malloc(sizeof (int) * len);

	assert(array != NULL);

	for (i = 0; i < len; i++)
		array[i] = rand() % (len * 3);

	print_array(array, len);
	//quick_sort(array, 0, len - 1);
	heap_sort(array, len - 1);
	//merge_sort(array, len - 1);

	help_check(array, len);
	return (0);
}
