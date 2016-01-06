#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void testcase() {
    int m; cin >> m;

    // initialize a priority que
    priority_queue<int,vector<int>,greater<int> > que;
    int l;
    for (int i = 0; i < m; i++) {
        cin >> l;
        que.push(l);
    }

    int steps = 0;
    int first, second;
    while (que.size() > 1) {
        // get first element and remove it
        first = que.top();
        que.pop();

        // get second element and remove it
        second = que.top();
        que.pop();

        // update complexity and push the sum
        steps += first + second - 1;
        que.push(first + second);
    }

    // output
    cout << steps << endl;
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
