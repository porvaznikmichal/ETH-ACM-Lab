#include <iostream>
#include <vector>
#include <algorithm>
#include <set>


using namespace std;

class Union_Find {
public:
	vector<int> id, size, weight;
	// class constructor
	Union_Find(int n) {
		for (int i = 0; i < n; i++) {
			id.push_back(i);
			size.push_back(1);
			weight.push_back(0);
		}
	}

	// representative
	int root(int i) {
		while(i != id[i]) {
			id[i] = id[id[i]];
			i = id[i];
		}
		return i;
	}

	int find(int p, int q) {
		return root(p)==root(q);
	}

	int smaller(int p, int q) {
		if (size[p] < size[q]) return p;
		else return q;
	}

	int larger(int p, int q) {
		if (size[p] >= size[q]) return p;
		else return q;
	}

	void unite(int p, int q, int cost) {
		int i = root(p);
		int j = root(q);

		if(size[i] <= size[j])
		{
			id[i] = j;
			size[j] += size[i];
			weight[j] += weight[i] + cost;
			weight[i] = 0;
		}
		else
		{
			id[j] = i;
			size[i] += size[j];
			weight[i] += weight[j] + cost;
			weight[j] = 0;
		}
	}
};

struct edge {
	int u, v, weight;

	friend bool operator<(const edge &x, const edge &y) {
		return x.weight < y.weight;
	}
};

vector<int> kruskal(vector<edge> &graph, int num_vertices) {
	// // initialize union find class
	Union_Find UF(num_vertices);

	// // sort edges by weight
	sort(graph.begin(), graph.end());

	// run through edges
	int u, v, root_smaller, root_larger;
	for (vector<edge>:: iterator ei = graph.begin(); ei != graph.end(); ei++) {
		u = min(ei->u, ei->v);
		v = max(ei->u, ei->v);
		// check if edge doesnt close a cycle
		if (!UF.find(u, v)) {
			UF.unite(u, v, ei->weight);
		}
	}

	return UF.weight;
}

void testcase() {
	int n, m; cin >> n >> m;

	vector<edge> graph;
	edge e1;
	int a, b, c;
	set<int> seen;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		// push time edge
		e1.u = a;
		e1.v = b;
		e1.weight = c;
		graph.push_back(e1);
		seen.insert(a);
		seen.insert(b);
	}

	vector<int> network = kruskal(graph, n);

	int num_islands = 0;
	int min_cost = *max_element(network.begin(), network.end());
	for (int i = 0; i < n; i++) {
		if ((network[i] > 0) && (network[i] <= 1000000)) {
			num_islands++;
			if (network[i] < min_cost) min_cost = network[i];
		}
	}

	cout << num_islands << " " << min_cost << endl;

}

int main(int argc, char const *argv[])
{

	ios_base::sync_with_stdio(false);

	int t; cin >> t;
	while (t--) {
		testcase();
	}
	return 0;
}