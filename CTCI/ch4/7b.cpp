#include <iostream>
#include <vector>
#include <set>

using namespace std;


bool
build_project(char project, vector<pair<char, char>> &deps, set<char> &built,
    set<char> &visited, vector<char> &build_order)
{
	int i;

	if (built.find(project) != built.end())
		return (true);

	/*
	 * If the project has not yet been built, but we have been here before
	 * then there must be a circular dependency.
	 */
	if (visited.find(project) != visited.end())
		return (false);

	visited.insert(project);

	for (i = 0; i < deps.size(); i++) {
		if (deps[i].second == project && !build_project(deps[i].first,
		    deps, built, visited, build_order))
			return (false);
	}

	built.insert(project);
	build_order.push_back(project);

	return (true);
}

bool
build_all(vector<char> &projects, vector<pair<char, char>> &deps,
    vector<char> &build_order)
{
	int i;
	set<char> built;
	set<char> visited;

	for (i = 0; i < projects.size(); i++) {
		if (!build_project(projects[i], deps, built, visited,
		    build_order))
			return (false);
	}

	return (true);
}

int main(void)
{
	int i;
	vector<char> build_order;
	vector<char> projects = {'a', 'b', 'c', 'd', 'e', 'f'};
	vector<pair<char, char>> deps = {
		{'a', 'd'},
		{'f', 'b'},
		{'b', 'd'},
		{'f', 'a'},
		{'d', 'c'}
	};

	if (build_all(projects, deps, build_order))
		cout << "Build successful" << endl;
	else
		cout << "Build unsucessful" << endl;

	for (i = 0; i < build_order.size(); i++)
		cout << build_order[i] << " ";
	cout << endl;
	return (0);
}
