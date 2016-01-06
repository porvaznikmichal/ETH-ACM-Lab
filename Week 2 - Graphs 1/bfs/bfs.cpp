#include <iostream>
#include <vector>
#include <queue>


using namespace std;

void bfs(vector<int> &distances, vector< vector<int> > &graph, int source) {
	// push source to que and set distance
	distances[source] = 0;
	queue<int> q;
	q.push(source);
	
	int current;
	while (!q.empty()) {
		// dequeue the current
		current = q.front();
		q.pop();

		// traverse neighbours that were not visited
		for (vector<int>::iterator vi = graph[current].begin(); vi != graph[current].end(); vi++) {
			if (distances[*vi] < 0) {
				distances[*vi] = distances[current] + 1;
				q.push(*vi);
			}
		}
	}
}

void testcase() {
	// read num vertices, edges and source
	int n, m, s; cin >> n >> m >> s;

	// read graph
	vector< vector<int> > graph(n, vector<int>());
	int a, b;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);	
	}

	// run bfs
	vector<int> distances(n, -1);
	bfs(distances, graph, s);

	// output distances
	for (int i = 0; i < n; i++) {
		cout << distances[i];
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
