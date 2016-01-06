#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <map>
#include <queue>


using namespace std;

const int MAX_INT = numeric_limits<int>::max();

struct edge
{
    int to, length;
};

int dijkstra(vector< vector<edge> > &graph, int source, int target) {
    int n = graph.size();

    // initialize distance structure and 'priority que'
    vector<int> distance(n, MAX_INT);
    set< pair<int, int> > priority;

    // add source
    distance[source] = 0;
    priority.insert(make_pair(0, source));

    int current;
    int alt;
    while (!priority.empty()) {
        current = priority.begin()->second;
        // if we reached target, we have the shortest distance
        if (current == target) return distance[current];

        // erase current
        priority.erase( priority.begin() );

        // check neighbourhood
        for (vector<edge>::iterator vi = graph[current].begin(); vi != graph[current].end(); vi++) {
            alt = max(distance[current], vi->length);
            if (alt < distance[vi->to]) {
                // decrease key
                priority.erase(make_pair(distance[vi->to], vi->to));
                priority.insert(make_pair(alt, vi->to));
                distance[vi->to] = alt;
            }
        }
    }
    // if not found, return max
    return MAX_INT;
}

void testcase() {
    int n, m, s, t; cin >> n >> m >> s >> t;
    vector< vector<edge> > graph(n, vector<edge>());
    // read graph and weights
    int u, v, c;
    edge e;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> c;

        // push edge there
        e.to = v;
        e.length = c;
        graph[u].push_back(e);

        //push edge back
        e.to = u;
        graph[v].push_back(e);
    }

    int shortest = dijkstra(graph, s, t);
        
    cout << shortest << endl;


}

int main(int argc, char const *argv[])
{
    std::ios_base::sync_with_stdio(false);
    int c; cin >> c;
    while (c--) {
        testcase();
    }
    return 0;
}