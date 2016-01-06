#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip> 

using namespace std;

void testcase() {
	int t, n; cin >> t >> n;
	// cout << "t = " << t << ", n = " << n << endl;

	// read in the stations
	vector< pair<int, int> > stations;

	int d, c;
	for (int i = 0; i < n; i++) {
		cin >> d >> c;
		stations.push_back(make_pair(d, c));
	}

	// initialize by going to the first station
	int position, current_index, cost, tank;
	if (stations[0].first > 1000) {
		cout << "impossible" << endl;
		return;
	}
	else {
		position = stations[0].first;
		current_index = 0;
		cost = 0;
		tank = 1000 - position;
	}

	// cout << "pos = " << position << ", current_index = " << current_index << ", cost = " << cost << ", tank = " << tank << endl;

	// iterate until end is reached
	int station_index;
	int cheapest_index;
	while (position < t) {
		// cout << "pos = " << position << ", current_index = " << current_index << ", cost = " << cost << ", tank = " << tank << endl;
		if (t - position <= tank) {
			cout << setprecision(1) << float(cost)/10 << endl;
			return;
		}
		// look for next station
		else {
			// if we are at the last station, check if we can reach end
			if (current_index == n - 1) {
				if (t - stations[current_index].first <= 1000) {
					cost += max(t - position - tank, 0)*stations[current_index].second;
					cout << setprecision(1) << float(cost)/10 << endl;
					return;
				}
				else {
					cout << "impossible" << endl;
					return;
				}
			}

			// check if we can reach next station
			station_index = current_index + 1;
			if (position + 1000 < stations[station_index].first) {
				cout << "impossible" << endl;
				return;
			}

			// at least one station reachable
			cheapest_index = station_index;
			while (stations[station_index].first <= position + 1000) {
				// if this is cheaper than the next
				if (stations[station_index].second < stations[current_index].second) {
					// go to this station
					cheapest_index = station_index;
					break;
				}
				else if (stations[station_index].second <= stations[cheapest_index].second) {
					cheapest_index = station_index;
				}
				if (station_index < n - 1) station_index++;
				else break;
			}

			// cout << "cheapest_index = " << cheapest_index << " position[cheapest_index] = " << stations[cheapest_index].first << ", cost[cheapest_index] = " << stations[cheapest_index].second << endl;
			// we found next station
			// if the next station is more expensive
			if (stations[current_index].second <= stations[cheapest_index].second) {
				// if we can reach goal go there
				if (t - stations[current_index].first <= 1000) {
					cost += max(t - position - tank, 0)*stations[current_index].second;
					cout << setprecision(1) << float(cost)/10 << endl;
					return;
				}
				// otherwise tank full in current station
				else {
					cost += (1000 - tank)*stations[current_index].second;
					tank = 1000 - (stations[cheapest_index].first - position);
					current_index = cheapest_index;
					position = stations[cheapest_index].first;
				}
			}
			// else if the next is cheaper
			// if we can reach it on tank go straight there
			else if (stations[cheapest_index].first <= position + tank) {
				tank -= stations[cheapest_index].first - position;
				position = stations[cheapest_index].first;
				current_index = cheapest_index;
			}
			// otherwise tank what only as much as we need
			else {
				// tank on current
				// cout << "distance out of tank = " << (stations[cheapest_index].first - position - tank) << ", cost of liter = " << stations[current_index].second << endl;
				// cout << "cost change = " << (stations[cheapest_index].first - position - tank)*stations[current_index].second << endl;
				cost += max(stations[cheapest_index].first - position - tank, 0)*stations[current_index].second;
				tank = 0;
				position = stations[cheapest_index].first;
				current_index = cheapest_index;
			}
		}
	}
}

int main(int argc, char const *argv[])
{
	int N; cin >> N;
	cout << std::fixed;
	while (N--) {
		// cout << N << endl;
		testcase();
	}
	return 0;
}
