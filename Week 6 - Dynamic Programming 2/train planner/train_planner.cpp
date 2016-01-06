#include <iostream>
#include <vector>

using namespace std;

int MAX_INT = 1000001;

struct edge
{
	int to, cost;
};

vector< vector<int> > bellman_ford(vector< vector < edge > > &graph, int K, int source) {
	int n = graph.size();
	// initialize
	vector< vector<int> > d(n, vector<int>(K + 1, MAX_INT));
	d[source][0] = 0;

	int min;
	// iterate through all path lengths
	for (int k = 1; k <= K; k++) {
		// iterate through all vertices
		for (int i = 0; i < n; i++) {
			// iterate through the neighbourhood of this vertex
			min = d[i][k - 1];
			for (vector<edge>::iterator ei = graph[i].begin(); ei != graph[i].end(); ei++) {
				if (d[ei->to][k - 1] + ei->cost <= min) {
					min = d[ei->to][k - 1] + ei->cost;
				}
			}
			d[i][k] = min;
		}
	}

	return d;
}

void testcase() {
	int n, m, s, t, k;
	cin >> n >> m >> s >> t >> k;

	// read graph
	vector< vector < edge > > graph(n, vector<edge>());
	edge e;
	int u, v, d;
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> d;
		// edge there
		e.to = v;
		e.cost = d;
		graph[u].push_back(e);

		// edge back
		e.to = u;
		graph[v].push_back(e);
	}

	vector< vector<int> > dist = bellman_ford(graph, k + 1, s);

	int min_cost = MAX_INT;
	int min_edges;
	for (int i = 0; i <= k + 1; i++) {
		if (dist[t][i] < min_cost) {
			min_cost = dist[t][i];
			min_edges = i;
		}
	}

	// output
	if (min_cost == MAX_INT) {
		cout << "impossible" << endl;
	}
	else {
		cout << min_cost << " " << min_edges - 1 << endl;
	}
}

int main(int argc, char const *argv[])
{
	int t; cin >> t;
	while (t--) {
		testcase();
	}
	return 0;
}
