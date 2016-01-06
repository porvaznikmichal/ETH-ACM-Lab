#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INT_MAX = 10000;

int longest(vector< vector<int> > &graph, int source)
{
    // initialize containers
    int n = graph.size();
    vector<int> distance(n, 0);
    vector<bool> visited(n, false);

    // initialize queue
    queue<int> q;
    q.push(source);
    visited[source] = true;

    // bfs
    int current;
    int max_dist = 0;
    while (!q.empty())
    {
        // get the font of the queue
        current = q.front();
        q.pop();
        visited[current] = true;

        // iterate through the neighbours
        for (vector<int>::iterator vi = graph[current].begin();
         vi != graph[current].end(); vi++)
        {
            if (!visited[*vi])
            {
                // process node
                visited[*vi] = true;
                distance[*vi] = 1 + distance[current];
                q.push(*vi);

                // update max distance
                max_dist = max(max_dist, distance[*vi]);
            }
        }
    }

    return max_dist;
}

int master(vector< vector<int> > &graph)
{

    // iterate through all nodes and try them as the master
    int n = graph.size();
    pair<int, int> smallest = make_pair(INT_MAX, n);
    int distance;
    for (int i = 0; i < n; i++)
    {   
        distance = longest(graph, i);
        if (make_pair(distance, i) < smallest) smallest = make_pair(distance, i);
    }

    return smallest.second;
}

void testcase()
{
    // read the graph
    int n, m;
    cin >> n >> m;

    vector< vector<int> > graph(n, vector<int>());
    int u, v;
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v;
        graph[u - 1].push_back(v - 1);
        graph[v - 1].push_back(u - 1);
    }

    cout << master(graph) + 1 << endl;
}

int main(int argc, char const *argv[])
{
    int t;
    cin >> t;
    while (t--)
    {
        testcase();
    }
    return 0;
}
