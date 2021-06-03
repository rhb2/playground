#include <iostream>
#include <vector>
#include <cassert>

using namespace std;


ostream &
operator<<(ostream &out, const vector<int> &v)
{
	int i;

	for (i = 0; i < v.size(); i++)
		out << v[i] << " ";

	return (out);
}

void
verify(vector<int> &v)
{
	int i;

	for (i = 0; i < v.size() - 1; i++)
		assert(v[i] <= v[i + 1]);
}

/*
 * Because we want a min-heap, we must supply a custom comparator that is
 * used for all heap operations (make_heap(), heap_pop(), heap_push()).
 * Without this, we are at the mercy of the STL default implementation which
 * is a max-heap.
 */
bool
compare(pair<int, int> &l, pair<int, int> &r)
{
	return (r.first < l.first);
}

vector<int>
n_way_merge(vector<vector<int>> &vv)
{
	int i;
	vector<int> result;
	vector<pair<int, int>> heap;

	for (i = 0; i < vv.size(); i++) {
		pair<int, int> p;
		p.first = vv[i][0];
		p.second = i;
		heap.push_back(p);
		vv[i].erase(vv[i].begin());
	}

	std::make_heap(heap.begin(), heap.end(), compare);

	while (!heap.empty()) {
		pair<int, int> p = heap[0];
		pair<int, int> tmp;
		std::pop_heap(heap.begin(), heap.end(), compare);
		heap.pop_back();
		
		result.push_back(p.first);
		
		if (!vv[p.second].empty()) {
			p.first = vv[p.second][0];
			vv[p.second].erase(vv[p.second].begin());
			heap.push_back(p);
			std::push_heap(heap.begin(), heap.end(), compare);
		}

	}

	return (result);
}

int main(int argc, char **argv)
{
	int i, j;
	int num_vecs;
	int vec_len;
	vector<vector<int>> vv;
	vector<int> result;

	assert(argc == 3);

	num_vecs = atoi(argv[1]);
	vec_len = atoi(argv[2]);

	for (i = 0; i < num_vecs; i++) {
		vector<int> v;
		for (j = 0; j < vec_len; j++)
			v.push_back(rand() % 100);

		std::sort(v.begin(), v.end());
		vv.push_back(v);
	}

	for (i = 0; i < vv.size(); i++)
		cout << "array" << i << ": " << vv[i] << endl;

	result = n_way_merge(vv);
	verify(result);

	cout << "result: " << result << endl;

	return (0);
}
