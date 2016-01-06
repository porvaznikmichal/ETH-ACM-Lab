#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>


using namespace std;

void bfs(vector<int> &distances, vector< vector<int> > &graph, int source) {
	// push source to que and set distance
	distances[source] = 1;
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
	int n; cin >> n;

	// read graph
	vector< vector<int> > graph(n, vector<int>());
	int a, b;
	for (int i = 0; i < n - 1; i++) {
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);	
	}

	// run bfs from vertex 0
	vector<int> distances1(n, -1);
	bfs(distances1, graph, 0);

	// find vertex with highest distance from 0
	int max = -1;
	int max_ind = -1;
	for (int i = 0; i < n; i++) {
		if (distances1[i] > max) {
			max = distances1[i];
			max_ind = i;
		}
	}

	// run bfs from max_ind
	vector<int> distances2(n, -1);
	bfs(distances2, graph, max_ind);

	// return the longest path
	cout << *max_element(distances2.begin(), distances2.end()) << endl;
}

int main(int argc, char const *argv[])
{
	int num_tests; cin >> num_tests;
	while (num_tests--) {
		testcase();
	}
	return 0;
}
