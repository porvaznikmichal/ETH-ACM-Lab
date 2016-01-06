#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <limits>

using namespace std;

void testcase() {
	// read input
	int num_coins, num_amounts;
	cin >> num_coins >> num_amounts;

	vector<int> coins;
	int coin;
	for (int i = 0; i < num_coins; i++) {
		cin >> coin;
		coins.push_back(coin);
	}

	vector<int> amounts;
	int amount;
	for (int i = 0; i < num_amounts; i++) {
		cin >> amount;
		amounts.push_back(amount);
	}
	// get max amount
	int max_amount = *max_element(amounts.begin(), amounts.end());

	// initialize map of optimal change
	vector<int> change(max_amount + 1, numeric_limits<int>::max());
	change[0] = 0;

	// fill in the map
	int min_change = numeric_limits<int>::max();
	int residual;
	for (int amount = 1; amount <= max_amount; amount++) {
		min_change = numeric_limits<int>::max();

		// iterate through coin values
		for (vector<int>::iterator val = coins.begin(); val != coins.end(); val++) {
			residual = amount - *val;
			if (residual < 0 || change[residual] == numeric_limits<int>::max()) continue;
			if (change[residual] < min_change - 1) {
				min_change = change[residual] + 1;
			}

		}

		// remember min_change for this amount
		change[amount] = min_change;
	}

	// output
	for (vector<int>::iterator am = amounts.begin(); am != amounts.end(); am++) {
		if (change[*am] < numeric_limits<int>::max()) {
			cout << change[*am] << endl;
		}
		else {
			cout << "not possible" << endl;
		}
	}
}

int main(int argc, char const *argv[])
{
	int num_tests; cin >> num_tests;
	while (num_tests--) {
		testcase();
	}
	return 0;
}

