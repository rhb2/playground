#include <iostream>
#include <map>
#include <vector>
#include <set>


using namespace std;

/*
 * List of dependencies.  Note: if a project has no dependencies, it will not
 * be listed here at all.
 */
static char dependencies[][2] = {
	{'a', 'd'},
	{'f', 'b'},
	{'b', 'd'},
	{'f', 'a'},
	{'d', 'c'},
};
#define DEP_LEN	(sizeof (dependencies) / sizeof (dependencies[0]))

void
print_dependencies(map<char, vector<char>> &deps)
{
	int i;
	map<char, vector<char>>::iterator it;

	cout << "DEPENDENCIES: " << endl;

	for (it = deps.begin(); it != deps.end(); it++) {
		cout << it->first << ": ";
		for (i = 0; i < it->second.size(); i++)
			cout << it->second[i] << " ";

		cout << endl;
	}
}

bool
build(char project, map<char, vector<char>> &deps, set<char> &built,
    set<char> &visited, vector<char> &order)
{
	int i;
	char p, d;

	/* This one has already been built.  Return. */
	if (built.find(project) != built.end())
		return (true);

	/*
	 * Add the current project to our list of visited projects so that
	 * if one of our dependencies (God forbid) depends on us, we will
	 * be able to catch the circular pattern.
	 */
	visited.insert(project);

	for (i = 0; i < deps[project].size(); i++) {
		char dependency = deps[project].at(i);
		/*
		 * This is a dependency that we have already visited.  This
		 * means that there is a circular dependency in our build
		 * graph and we will never finish.  Flag failure and return.
		 */
		if (visited.find(dependency) != visited.end())
			return (false);

		/*
		 * We have an unsatisfied build dependency here.  We need to
		 * to build it before we can move forward.
		 */
		if (!build(dependency, deps, built, visited, order))
			return (false);
	}

	/* This project has been successfully built. */
	built.insert(project);
	order.push_back(project);
	return (true);
}

bool
build_all(vector<char> &projects, map<char, vector<char>> &deps,
    vector<char> &order)
{
	int i;
	char p;
	set<char> built;

	/*
	 * Of the remaining projects, resolve their dependencies and build them.
	 * We will likely end up with all the projects built before we even
	 * finish the loop.
	 */
	for (i = 0; i < projects.size(); i++) {
		set<char> visited;
		if (!build(projects[i], deps, built, visited, order))
			return (false);
	}

	return (true);
}

int main(int argc, char **argv)
{
	int i;
	char projects[] = "abcdef";
	vector<char> p, order;
	map<char, vector<char>> deps;

	cout << "PROJECTS: ";
	for (i = 0; i < strlen(projects); i++) {
		cout << projects[i] << " ";
		p.push_back(projects[i]);
	}
	cout << endl;

	/*
	 * First, convert the list of pairs (above) to an adjacency list.
	 * After that, we can treat this like a graph traversal problem.
	 */
	for (i = 0; i < DEP_LEN; i++) {
		char project = dependencies[i][0];
		vector<char> v;

		if (deps.find(project) == deps.end())
			deps[project] = v;

		deps[project].push_back(dependencies[i][1]);
	}

	print_dependencies(deps);

	if (build_all(p, deps, order)) {
		cout << "All projects successfully built." << endl;
		cout << "BUILD ORDER: ";

		for (i = 0; i < order.size(); i++)
			cout << order[i] << " ";
		cout << endl;
	} else {
		cout << "Unable to successfully build all projects." << endl;
	}

	return (0);
}
