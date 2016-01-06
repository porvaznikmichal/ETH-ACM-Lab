#include <iostream>
#include <vector>
#include <set>
#include <climits>

using namespace std;

const long long MAX = LLONG_MAX;

void testcase() {
    // read input
    int n, k;
    cin >> n >> k;
    vector<long long> A(n, 0);
    long long a;
    for (int i = 0; i < n; i++) {
        cin >> a;
        A[i] = a;
    }

    // Initialize cost vector. Here C[i] denotes the cost of getting
    // n - 1, starting at position i
    vector<long long> cost(n, MAX);

    // starting from n - 1, its for free
    cost[n - 1] = 0;

    // initilize set of cheapest possible jumps
    set<pair<long long, int> > reachable;
    reachable.insert(make_pair(A[n - 1], n - 1));

    // iterate through all positions
    pair<long long, int> furthest, current;
    for (int i = n - 2; i >= 0; i--) {
        // get the cost of current position
        cost[i] = reachable.begin() -> first;

        // if the set already has k elements, erase the furthest one
        if (reachable.size() == k) {
            furthest = make_pair(A[i + k] + cost[i + k], i + k);
            reachable.erase(furthest);
        }

        // add the current element
        current = make_pair(A[i] + cost[i], i);
        reachable.insert(current);
    }

    // output cost[0]
    cout << cost[0] << endl;

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
