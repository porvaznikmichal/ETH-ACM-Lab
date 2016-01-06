#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

const int MAX_INT = 1000001;

int pos_mod(int i, int n) {
	return ((i % n) + n) % n;
}

vector< vector<int> > build_table(vector<int> &bandwidths) {
	int n = bandwidths.size();
	int R = floor(log2(n)) + 1;

	// initialize dp table
	vector< vector<int> > table(n, vector<int>(R, MAX_INT));

	// initialize base case, i.e. for r = 1
	for (int i = 0; i < n; i++) {
		table[i][0] = min(bandwidths[i], bandwidths[(i + 1) % n]);
	}

	// build it up
	for (int r = 1; r < R; r++) {
		for (int i = 0; i < n; i++) {
			table[i][r] = min(table[i][r - 1], table[(i + (int)pow(2, r - 1)) % n][r - 1]);
		}
	}

	return table;
}

pair<int, int> max_bottleneck(vector<int> &bandwidths, vector< vector<int> > &table, int k) {
	int n = table.size();

	int best = 0;
	pair<int, int> best_pair;

	// iterate through all pairs with distance k
	int j, ia, ib, ja, jb, diff, bottleneck_a, bottleneck_b, r, better_path;
	for (int i = 0; i < n; i++) {
		j = pos_mod(i + k, n);
		// compute bottleneck of path a
		ia = i;
		ja = pos_mod((j - 1), n);
		diff = k - 1;
		if (diff == 0) {
			bottleneck_a = bandwidths[ia];
		}
		else {
			r = floor(log2(diff));
			bottleneck_a = min(table[ia][r], table[pos_mod((ja - (int)pow(2, r)), n)][r]);

		}

		// compute bottleneck of path b
		ib = j;
		jb = pos_mod((i - 1), n);
		diff = n - k - 1;

		if (diff == 0) {
			bottleneck_b = bandwidths[ib];
		}
		else {
			r = floor(log2(diff));
			bottleneck_b = min(table[ib][r], table[pos_mod((jb - (int)pow(2, r)), n)][r]);
		}

		// get the maximum over bottlenecks
		better_path = max(bottleneck_a, bottleneck_b);

		// check if this is better
		if (better_path > best) {
			best = better_path;
			best_pair = make_pair(i, j);
		}
		else if (better_path == best && (i < best_pair.first)) {
			best = better_path;
			best_pair = make_pair(i, j);
		}
	}

	return best_pair;
}

void testcase() {
	int n, q;
	cin >> n >> q;

	// read bandwidths
	vector<int> bandwidths;
	int b;
	for (int i = 0; i < n; i++) {
		cin >> b;
		bandwidths.push_back(b);
	}

	// read the distances
	vector<int> distances;
	int k;
	for (int i = 0; i < q; i++) {
		cin >> k;
		distances.push_back(k);
	}

	vector< vector<int> > table = build_table(bandwidths);

	pair<int, int> best;
	// iterate through distances
	for (int i = 0; i < q; i++) {
		best = max_bottleneck(bandwidths, table, distances[i]);
		cout << best.first << " " << best.second << endl;
	}
}

int main(int argc, char const *argv[])
{
	int t; cin >> t;
	while (t--) {
		testcase();
	}
	return 0;
}
