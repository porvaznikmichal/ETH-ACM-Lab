#include <iostream>
#include <vector>
#include <set>
#include <algorithm>


using namespace std;

void backtrack(vector<int> path, bool &found, vector< vector<int> > &graph) {
	// if we already found a path kill the process
	if (found) return;

	// iterate through neighbours
	int current = path[path.size() - 1];
	int s = graph.size();
	vector<int> extended_path;
	for (vector<int>::iterator vi = graph[current].begin(); vi != graph[current].end(); vi++) {
		// if we get back to 0 we found cycle
		if ((path.size() == s) && (*vi == 0)) {
			found = true;
			return;
		}

		// if the neighbour is not already in the path then skip
		if (find(path.begin(), path.end(), *vi) == path.end()) {
			extended_path = path;
			extended_path.push_back(*vi);
			backtrack(extended_path, found, graph);
		}
	}
}

void testcase() {
	// read input and chceck if we have seen all values
	int n, s; cin >> n >> s;
	// initialize graph
	vector< vector<int> > graph(s + 1, vector<int>());
	set<int> nodes;
	int u, v;
	for (int i = 0; i < n; i++) {
		cin >> u >> v;
		nodes.insert(u);
		nodes.insert(v);
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	// chcek if we have enough nodes and edges
	if ((nodes.size() < s + 1) || (n < s + 1)) {
		cout << "no" << endl;
		return;
	}

	// create an indicator if we found hamiltonain cycle
	bool found = false;
	vector<int> path;
	path.push_back(0);
	backtrack(path, found, graph);

	//output
	if (found) {
		cout << "yes" << endl;
	}
	else {
		cout << "no" << endl;
	}

}

int main(int argc, char const *argv[])
{
	int num_tests; cin >> num_tests;
	while (num_tests--) {
		testcase();
	}
	return 0;
}
