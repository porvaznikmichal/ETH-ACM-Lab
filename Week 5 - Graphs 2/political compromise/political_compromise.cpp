#include <iostream>
#include <vector>
#include <algorithm>
#include <set>


using namespace std;

class Union_Find {
public:
	vector<int> id, size;
	// class constructor
	Union_Find(int n) {
		for (int i = 0; i < n; i++) {
			id.push_back(i);
			size.push_back(1);
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

	void unite(int p, int q) {
		int i = root(p);
		int j = root(q);

		if(size[i] < size[j])
		{
			id[i] = j;
			size[j] += size[i];
		}
		else
		{
			id[j] = i;
			size[i] += size[j];
		}
	}
};

struct edge {
	int u, v, weight;

	friend bool operator<(const edge &x, const edge &y) {
		return x.weight <= y.weight;
	}
};

set< pair<int, int> > kruskal(vector<edge> &graph, int num_vertices) {
	// initialize result
	set< pair<int, int> > result;

	// initialize union find class
	Union_Find UF(num_vertices);

	// sort edges by weight
	sort(graph.begin(), graph.end());

	// run through edges
	int u, v;
	for (vector<edge>:: iterator ei = graph.begin(); ei != graph.end(); ei++) {
		u = min(ei->u, ei->v);
		v = max(ei->u, ei->v);
		// check if edge doesnt close a cycle
		if (!UF.find(u, v)) {
			UF.unite(u, v);
			result.insert(make_pair(u, v));
		}
	}

	return result;
}

void testcase() {
	int v, e; cin >> v >> e;

	vector<edge> duration, cost;
	edge e1, e2;
	int a, b, c, d;
	for (int i = 0; i < e; i++) {
		cin >> a >> b >> c >> d;
		// push time edge
		e1.u = a;
		e1.v = b;
		e1.weight = c;
		duration.push_back(e1);

		e2.u = a;
		e2.v = b;
		e2.weight = d;
		cost.push_back(e2);
	}

	set< pair<int, int> > fastest = kruskal(duration, v);
	set< pair<int, int> > cheapest = kruskal(cost, v);


	if (fastest == cheapest) {
		cout << "yes" << endl;
	}
	else cout << "no" << endl;

}

int main(int argc, char const *argv[])
{
	int n; cin >> n;
	while (n--) {
		testcase();
	}
	return 0;
}