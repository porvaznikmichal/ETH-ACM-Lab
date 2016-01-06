#include <iostream>
#include <vector>
#include <queue>
#include <set>



using namespace std;

int find_length(vector<vector<int> > &graph, vector<int> &parent, int node_a, int node_b)
{
    // backtrack from a
    set<int> path_a;
    int node = node_a;
    
    do
    {
        node = parent[node];
        path_a.insert(node);
    } while (node != 0);

    // backtrack from b and find intersection
    int num_nodes = 1;
    int intersection = node_b;
    while (path_a.count(intersection) == 0)
    {
        intersection = parent[intersection];
        num_nodes++;
    }

    // backtract again from a until intersection
    node = node_a;
    while (node != intersection)
    {
        node = parent[node];
        num_nodes++;
    }

    return num_nodes;
}

int cycle_length(vector<vector<int> > &graph)
{
    int n = graph.size();
    // initialize visited and parent map
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);
    vector<int> dist(n, -1);


    // initialize que
    queue<int> q;
    visited[0] = true;
    dist[0] = 0;
    q.push(0);

    int current;
    while (!q.empty())
    {

        current = q.front();
        q.pop();

        for (vector<int>::iterator vi = graph[current].begin(); vi != graph[current].end(); vi++)
        {
            if (!visited[*vi])
            {
                visited[*vi] = true;
                parent[*vi] = current;
                dist[*vi] = dist[current] + 1;
                q.push(*vi);
            }
            else
            {
                // check if we close the cycle
                if (*vi != parent[current] && current != 0)
                {
                    int length = find_length(graph, parent, current, *vi);
                    return length;
                }
            }
        }
    }

    return -1;
}

void testcase()
{
    int n; cin >> n;
    vector< vector<int> > graph(n, vector<int>());
    int u, v;
    for (int i = 0; i < n; i++)
    {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    cout << cycle_length(graph) << endl;
}

int main(int argc, char const *argv[])
{
    int t; cin >> t;
    while (t--)
    {
        testcase();
    }
    return 0;
}
