#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void dfs(int source, int &timer ,vector< vector<int> > &graph, 
	vector<int> &discovery, vector<int> &finished) {
	// throw source to discovery and mark it visited
	discovery[source] = timer;
	timer++;

	// visit neighbours
	for (vector<int>::iterator vi = graph[source].begin(); vi != graph[source].end(); ++vi) {
		// if not visited
		if (discovery[*vi] < 0) {
			dfs(*vi, timer, graph, discovery, finished);
		}
	}

	// close vertex
	finished[source] = timer;
	timer++;
}

void testcase() {
	// read number of nodes and edges
	int n, m; cin >> n >> m;

	// read the adjacency list
	vector< vector<int> > graph(n, vector<int>());
	int a, b;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	// sort the adjacency list
	for (int i = 0; i < n; ++i) {
		sort(graph[i].begin(), graph[i].end());
	}

	// initialize continers and run dfs from each vertex
	vector<int> discovery(n, -1);
	vector<int> fin(n, -1);
	int timer = 0;
	for (int i = 0; i < n; ++i) {
		if (discovery[i] < 0) {
			dfs(i, timer, graph, discovery, fin);
		}
	}

	// output result
	for (int i = 0; i < n; i++) {
		cout << discovery[i];
		if (i < n - 1) cout << " ";
		else cout << endl;
	}
	for (int i = 0; i < n; i++) {
		cout << fin[i];
		if (i < n - 1) cout << " ";
		else cout << endl;
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
