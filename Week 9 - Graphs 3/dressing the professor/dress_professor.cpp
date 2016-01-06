#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;


vector<int> toposort(vector<vector<int> >& graph, vector<int> &in_degree) {
	//vector for result
	vector<int> sort;
	int n = graph.size();

	//initialize que and push zero in degree vertices
	priority_queue<int> que;
	for (int i = n - 1; i >= 0; --i) {
		if (in_degree[i] == 0) {
			que.push(i);
		}
	}

	//run through all vertices
	while (!que.empty()) {
		int current = que.top();
		que.pop();
		sort.push_back(current);
		//decerase in degrees of neighbours
		for (vector<int>::iterator vi = graph[current].begin(); vi != graph[current].end(); ++vi) {
			--in_degree[*vi];
			if (in_degree[*vi] == 0) {
				que.push(*vi);
			}
		}
	}

	return sort;
}

void solution1() {
	// read number of nodes and edges
	int n, m; cin >> n >> m;

	// read the adjacency list
	vector< vector<int> > graph(n, vector<int>());
	vector<int> in_degree(n, 0);
	int a, b;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		graph[b - 1].push_back(a - 1);
		in_degree[a - 1]++;
	}
	vector<int> sort = toposort(graph, in_degree);

	for (int i = 0; i < n; i++) {
		cout << sort[i] + 1 << endl;
	}
}

void dfs(int source, vector< vector<int> > &graph, vector<int> &visited, vector<int> &sort) {
	// visit neighbours
	for (vector<int>::iterator vi = graph[source].begin(); vi != graph[source].end(); ++vi) {
		// if not visited
		if (!visited[*vi]) {
			// cout << "dfs discovery " << *vi << endl;
			visited[*vi] = true;
			dfs(*vi, graph, visited, sort);
		}
	}
	// cout << "dfs closing " << source << endl;
	// add to source
	sort.push_back(source);
}

void solution2() {
	// read number of nodes and edges
	int n, m; cin >> n >> m;

	// read the adjacency list
	vector< vector<int> > graph(n, vector<int>());
	vector<int> in_degree(n, 0);
	int a, b;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		graph[b - 1].push_back(a - 1);
		in_degree[a - 1]++;
	}

	// sort the adjacency list
	vector<int> roots;
	for (int i = n - 1; i >= 0; i--) {
		sort(graph[i].begin(), graph[i].end());
		if (!in_degree[i]) {
			roots.push_back(i);
		}
	}

	// initialize continers and run dfs from each vertex
	vector<int> visited(n, false);
	vector<int> result;
	for (int i = 0; i < roots.size(); ++i) {
		// cout << "root " << roots[i] << endl;
		
		visited[roots[i]] = true;
		dfs(roots[i], graph, visited, result);

		for (int i = result.size() - 1; i >= 0; i--) {
			cout << result[i] + 1 << endl;
		}
		result.clear();
	}

	// output result
}

int main(int argc, char const *argv[])
{
    std::ios_base::sync_with_stdio(false);
	int num_tests; cin >> num_tests;
	while (num_tests--) {
		solution2();
	}
	return 0;
}
