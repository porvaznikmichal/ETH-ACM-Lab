#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void dfs(int source, int &timer ,vector< vector<int> > &graph, vector<int> &parent,
	vector<int> &discovery, vector<int> &low, vector<bool> &visited, vector<pair<int, int> > &bridges) {
	// throw source to discovery and mark it visited
	visited[source] = true;
	discovery[source] = timer;
	low[source] = timer;
	timer++;

	// visit neighbours
	for (vector<int>::iterator vi = graph[source].begin(); vi != graph[source].end(); ++vi) {
		// if not visited
		if (!visited[*vi]) {
			// recurse
			parent[*vi] = source;
			dfs(*vi, timer, graph, parent, discovery, low, visited, bridges);

			// set low link to the minimum of itself and a child node
			low[source] = min(low[source], low[*vi]);

			// now check if the lowest we can reach from *vi is itself
			// and if so, (source, *vi) is a bridge
			if (low[*vi] == discovery[*vi]) {
				bridges.push_back(make_pair(min(source, *vi), max(source, *vi)));
			}
		}
		else if (parent[source] != *vi) {
			low[source] = min(low[source], low[*vi]);			
		}
	}
}

void testcase() {
	int n, m;
	cin >> n >> m;

	if (n == 0 || m == 0) {
		cout << 0 << endl;
		return;
	}

	// read graph
	vector<vector<int> > graph(n, vector<int>());
	int u, v;
	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		graph[u - 1].push_back(v - 1);
		graph[v - 1].push_back(u - 1);		
	}

	
	// initialize containers
	vector<int> discovery(n, -1);
	vector<int> parent(n, -1);
	vector<int> low(n, -1);
	vector<bool> visited(n, false);
	vector<pair<int, int> > bridges;
	int timer = 0;
	
	// run dfs
	dfs(0, timer, graph, parent, discovery, low, visited, bridges);

	// sort the bridges
	sort(bridges.begin(), bridges.end());

	// output
	cout << bridges.size() << endl;
	for (int i = 0; i < bridges.size(); i++) {
		cout << bridges[i].first + 1 << ' ' << bridges[i].second + 1 << endl;
	}

}

int main(int argc, char const *argv[])
{
    std::ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while (t--) {
		testcase();
	}
	return 0;
}