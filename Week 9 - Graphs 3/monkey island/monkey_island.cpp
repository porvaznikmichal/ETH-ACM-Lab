#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <numeric>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAX_COST = 100;

void strongconnect(vector<vector<int> >& graph, stack<int>& S, vector<bool>& on_stack, 
	vector<int>& index, vector<int>& lowlink, vector<int>& components, int v, int &ind, int &comp_id) {
	//set index and lowlink and put on stack
	index[v] = ind;
	lowlink[v] = ind;
	++ind;
	S.push(v);
	on_stack[v] = true;

	//loop through neighbours of v
	vector<int> nbr = graph[v];
	for (vector<int>::iterator vi = nbr.begin(); vi != nbr.end(); ++vi) {
		//if neighbour unvsited then recurse on it
		if (index[*vi] == -1) {
			strongconnect(graph, S, on_stack, index, lowlink, components, *vi, ind, comp_id);
			lowlink[v] = min(lowlink[v], lowlink[*vi]);
		}
		else if (on_stack[*vi]) {
			// Successor w is in stack S and hence in the current SCC
			lowlink[v] = min(lowlink[v], index[*vi]);
		}
	}

	//if v is a root node, create an SCC
	if (lowlink[v] == index[v]) {
		//initialize new component
		int w;
		do {
			w = S.top();
			S.pop();
			on_stack[w] = false;
			components[w] = comp_id;
		} while (w != v);
		// increment component id for the next one
		comp_id++;
	}
}

vector<int> SCC(vector<vector<int> >& graph) {
	int ind = 0;
	int n = graph.size();
	//initialize stack
	stack<int> S;
	//initialize three vectors on_stack, index and lowlink for bookkeeping
	vector<bool> on_stack(n,false);
	vector<int> index(n, -1);
	vector<int> lowlink(n, -1);
	//initialize empty set for the components
	vector<int> components(n, -1);
	int comp_id = 0;

	//run through vertices
	for (int i = 0; i < n; ++i) {
		if (index[i] == -1) {
			strongconnect(graph, S, on_stack, index, lowlink, components, i, ind, comp_id);
		}
	}

	//return components
	return components;
}

void testcase() {
	int n, m;
	cin >> n >> m;

	// read graph
	vector<vector<int> > graph(n, vector<int>());
	int u, v;
	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		graph[u - 1].push_back(v - 1);
	}

	// read the station costs
	vector<int> costs;
	int c;
	for (int i = 0; i < n; i++) {
		cin >> c;
		costs.push_back(c);
	}

	vector<int> components = SCC(graph);

	int num_components = *max_element(components.begin(), components.end()) + 1;

	// initialze component cost vector
	vector<int> component_cost(num_components, MAX_COST);

	// go through stations and find component costs
	for (int i = 0; i < n; i++) {
		if (costs[i] < component_cost[components[i]]) {
			component_cost[components[i]] = costs[i];
		}
	}

	// run over edges and update component costs if an edge connects two SCCs
	for (int u = 0; u < n; u++) {
		for (int i = 0; i < graph[u].size(); i++) {
			v = graph[u][i];
			if (components[u] != components[v]) {
				component_cost[components[v]] = 0;
			}
		}
	}

	// // sum up all the costs and output
	cout << accumulate(component_cost.begin(), component_cost.end(), 0) << endl;
}

int main(int argc, char const *argv[])
{
	int t; cin >> t;
	while (t--) {
		testcase();
	}
	return 0;
}