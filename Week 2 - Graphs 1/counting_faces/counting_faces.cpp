#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void get_component(int i, vector< vector<int> > &graph,
	vector<int> &comp, vector<bool> &visited) {
	// just a bfs throwing component including i into comp
	queue<int> q;
	q.push(i);
	visited[i] = true;
	int current;
	while (!q.empty()) {
		current = q.front();
		q.pop();
		comp.push_back(current);
		for (vector<int>::iterator vi = graph[current].begin(); vi != graph[current].end(); vi++) {
			if (!visited[*vi]) {
				q.push(*vi);
				visited[*vi] = true;
			}
		}
	}
}

vector< vector<int> > components(vector< vector<int> > &graph) {
	int n = graph.size();
	vector<bool> visited(n, false);
	vector< vector<int> > comps;

	vector<int> new_comp;
	for (int i = 0; i < n; i++) {
		if (visited[i]) continue;
		else {
			new_comp.clear();
			get_component(i, graph, new_comp, visited);
			comps.push_back(new_comp);
		}
	}

	return comps;
}

void testcase() {
	// read graph
	int n, m; cin >> n >> m;
	vector< vector<int> > graph(n, vector<int>());
	int u, v;
	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	// get components
	vector< vector<int> > comps = components(graph);

	// run through components
	// num_faces in planar connected graph = 2 - |V| + |E|
	// in disconnected graph we just do this componentwise
	int num_faces = 1;
	int comp_vertices, comp_edges;
	for (int i = 0; i < comps.size(); i++) {
		// run over component counting edges and vertices
		comp_vertices = comps[i].size();
		comp_edges = 0;
		for (int j = 0; j < comps[i].size(); j++) {
			comp_edges += graph[comps[i][j]].size();
		}
		num_faces += (1 - comp_vertices + comp_edges/2);
 	}

 	cout << num_faces << endl;
}

int main(int argc, char const *argv[])
{
	int num_tests; cin >> num_tests;
	while (num_tests--) {
		testcase();
	}
	return 0;
}
