#include <iostream>
#include <vector>
#include <limits>

using namespace std;
const int INF = 100000000;

void testcase() {
	int num_baverages; cin >> num_baverages;
	int num_people; cin >> num_people;

	// read baverages
	vector<int> costs, volumes;
	int cost, volume;
	for (int i = 0; i < num_baverages; i++) {
		cin >> cost >> volume;
		costs.push_back(cost);
		volumes.push_back(volume);
	}

	// initialize dynamic programming table
	vector< pair<int, int > > dp_table(num_people + 1, make_pair(INF, 0));
	vector< vector<bool> > items(num_people + 1, vector<bool>(num_baverages, false));
	dp_table[0].first = 0;
	// run through all volumes
	pair<int, int> best;
	pair<int, int> current;
	int remaining, drink_used;
	for (int k = 1; k <= num_people; k++) {
		best = make_pair(INF, 0);
		for (int i = 0; i < num_baverages; i++) {
			remaining = k - volumes[i];

			// if negative or zero remaining volume
			if (remaining < 0) {
				current.first = costs[i];
				current.second = 1;
			}
			else {
				// get from dp_table
				current = dp_table[remaining];
				// check if we need to update number of distinct drinks
				current.first += costs[i];
				if (!items[remaining][i]) current.second++;
			}
			
			if ((current.first < best.first) || ((current.first == best.first) && (current.second > best.second))) {
				best = current;
				drink_used = i;
			}
		}
		dp_table[k] = best;
		if (k < volumes[drink_used]) {
			items[k][drink_used] = true;
		}
		else {
			items[k] = items[k - volumes[drink_used]];
			items[k][drink_used] = true;	
		}
	}

	cout << dp_table[num_people].first << " " << dp_table[num_people].second << endl;
}

int main(int argc, char const *argv[])
{
	int num_tests; cin >> num_tests;
	while (num_tests--) {
		testcase();
	}
	return 0;
}