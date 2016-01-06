#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>


using namespace std;

bool reachable(int source, int target, vector< vector<int> > &graph, vector<int> &path) {
	// set all nodes in path as visited
	vector<bool> visited(graph.size(), false);
	int path_length = path.size();
	for (int i = 0; i < path_length; i++) {
		visited[path[i]] = true;
	}

	queue<int> q;
	q.push(source);
	visited[source] = true;
	
	// run bfs
	int current;
	while (!q.empty()) {
		current = q.front();
		q.pop();

		for (vector<int>::iterator vi = graph[current].begin(); vi != graph[current].end(); vi++) {
			if (*vi == target) {
				return true;
			}
			else if (!visited[*vi]) {
				q.push(*vi);
				visited[*vi] = true;
			}
		}
	}

	return false;
}

void backtrack(vector<int> path, vector< vector<int> > &graph,
	vector< vector<int> > &allpaths, int &target) {

	// chcek next node
	vector<int> extended_path;
	int current = path[path.size() - 1];
	for (vector<int>::iterator vi = graph[current].begin(); vi != graph[current].end(); vi++) {
		// if we reached target add to all paths
		if (*vi == target) {
			extended_path = path;
			extended_path.push_back(*vi);
			allpaths.push_back(extended_path);
		}

		// chcek if target reachable from neighbour
		else if (reachable(*vi, target, graph, path)) {

			// if not in current path backtrack
			if (find(path.begin(), path.end(), *vi) == path.end()) {
				extended_path = path;
				extended_path.push_back(*vi);
				backtrack(extended_path, graph, allpaths, target);
			}
		}
	}
}

void testcase() {
	// read graph
	int n, m, s, t; cin >> n >> m >> s >> t;
	vector< vector<int> > graph(n, vector<int>());
	int u, v;
	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	// create a vector of all paths
	vector< vector<int> > allpaths;

	// create initial path
	vector<int> path;
	path.push_back(s);

	// run complete search
	backtrack(path, graph, allpaths, t);

	// sort all paths lexicographically
	sort(allpaths.begin(), allpaths.end());

	// output all paths
	int path_length;
	for (int i = 0; i < allpaths.size(); i++) {
		path_length = allpaths[i].size();
		for (int j = 0; j < path_length; j++) {
			if (j < path_length - 1) {
				cout << allpaths[i][j] << " ";
			}
			else {
				cout << allpaths[i][j] << endl;
			}
		}
	}
	cout << allpaths.size() << endl;

}

int main(int argc, char const *argv[])
{
	int num_tests; cin >> num_tests;
	while (num_tests--) {
		testcase();
	}
	return 0;
}

