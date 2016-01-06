#include <iostream>
#include <vector>


using namespace std;

void testcase() {
	// read input
	int n; cin >> n;
	vector<int> A,B;
	int bit;
	for (int i = 0; i < n; i++) {
		cin >> bit;
		A.push_back(bit - 1);
	}
	for (int i = 0; i < n; i++) {
		cin >> bit;
		B.push_back(bit - 1);
	}

	
	// compute partial sums for all pairs
	vector< vector<int> > sumsA(n, vector<int>(n, 0));
	vector< vector<int> > sumsB(n, vector<int>(n, 0));
	sumsA[0][0] = A[0];
	sumsB[0][0] = B[0];
	// compute the sides
	for (int i = 1; i < n; i++) {
		sumsA[0][i] = sumsA[0][i - 1] + A[i];
		sumsB[0][i] = sumsB[0][i - 1] + B[i];
	}
	// compute the rest
	for (int i = 1; i < n; i++) {
		for (int j = i; j < n; j++) {
			sumsA[i][j] = sumsA[0][j] - sumsA[0][i - 1];
			sumsB[i][j] = sumsB[0][j] - sumsB[0][i - 1];
		}
	}
	

	// initialize dp map
	vector< vector<int> > dp_map(n, vector<int>(n,0));
	// compute side cases
	for (int i = 0; i < n; i++) {
		// if we have only one left and take it
		dp_map[0][i] = A[0]*sumsB[0][i];
		dp_map[i][0] = B[0]*sumsA[0][i];
	}

	// for remainging cases
	int min_cost;
	int move_cost;
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < n; j++) {
			// now we are looking for optimum given only A[0:i], B[0:j]
			int min_cost = sumsA[0][i] * sumsB[0][j];
			// iterate through all other possibilities
			for (int ka = 1; ka <= i; ka++) {
				move_cost = sumsA[i - ka + 1][i] * B[j];
				if (dp_map[i - ka][j - 1] + move_cost < min_cost) {
					min_cost = dp_map[i - ka][j - 1] + move_cost;
				}
			}

			for (int kb = 1; kb <= j; kb++) {
				move_cost = A[i] * sumsB[j - kb + 1][j];
				if (dp_map[i - 1][j - kb] + move_cost < min_cost) {
					min_cost = dp_map[i - 1][j - kb] + move_cost;
				}
			}

			dp_map[i][j] = min_cost;
		}
	}

	cout << dp_map[n - 1][n - 1] << endl;
}

int main(int argc, char const *argv[])
{	
	int t; cin >> t;
	while (t--) {
		testcase();
	}

	return 0;
}
