#include <iostream>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

int optimal(int left, int right, vector<int> &coins,
	vector< vector<int> > &sums, vector< vector<int> > &best) {

	// if one coin
	if (left == right) {
		best[left][right] = coins[left];
		return coins[left];
	}
	// if two
	else if (right - left == 1) {
		best[left][right] = max(coins[left], coins[right]);	
		return max(coins[left], coins[right]);
	}
	else {
		// chcek if we have best gain on remaining else compute
		if (best[left + 1][right] == 0) {
			best[left + 1][right] = optimal(left + 1, right, coins, sums, best);
		}

		// chcek if we have best gain on remaining else compute
		if (best[left][right - 1] == 0) {
			best[left][right - 1] = optimal(left, right - 1, coins, sums, best);
		}

		int gain_left = coins[left] + sums[left + 1][right] - best[left + 1][right];
		int gain_right = coins[right] + sums[left][right - 1] - best[left][right - 1];
		return max(gain_left, gain_right);
	}
}

void testcase() {
	//read input
	int num_coins; cin >> num_coins;
	vector<int> coins;
	int coin;
	for (int i = 0; i < num_coins; i++) {
		cin >> coin;
		coins.push_back(coin);
	}

	// compute map of sums for each pair of indices
	vector< vector<int> > sums(num_coins, vector<int>(num_coins, 0));
	for (int i = 0; i < num_coins; i++) {
		sums[i][i] = coins[i];
		for (int j = i + 1; j < num_coins; j++) {
			sums[i][j] = sums[i][j - 1] + coins[j];
		}
	}

	// initialize map for best result
	vector< vector<int> > best(num_coins, vector<int>(num_coins, 0));;

	// compute and output
	cout << optimal(0, num_coins - 1, coins, sums, best) << endl;
}

int main(int argc, char const *argv[])
{
	int num_tests; cin >> num_tests;
	while (num_tests--) {
		testcase();
	}
	return 0;
}

