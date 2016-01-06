#include <iostream>
#include <vector>

using namespace std;

// solution in quadratic time
void quadratic() {
	//read input
	int n; cin >> n;
	int bit;
	vector<int> sequence;
	for (int i = 0; i < n; ++i) {
		cin >> bit;
		sequence.push_back(bit);
	}

	// take partial sums
	// n+1 not to run out of bounds
	vector<int> S(n+1, 0);
	for (int i = 1; i <= n; ++i) {
		S[i] = S[i - 1] + sequence[i - 1];
	}

	// run through all pairs
	int total_even = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = i; j <= n; ++j) {
			if ((S[j] - S[i - 1]) % 2 == 0) {
				++total_even;
			}
		}
	}

	cout << total_even << endl;
}

// solution in linear time
void linear() {
	//read input
	int n; cin >> n;
	int bit;
	vector<int> sequence;
	for (int i = 0; i < n; ++i) {
		cin >> bit;
		sequence.push_back(bit);
	}

	// take partial sums
	// n+1 not to run out of bounds
	vector<int> S(n+1, 0);
	for (int i = 1; i <= n; ++i) {
		S[i] = S[i - 1] + sequence[i - 1];
	}

	int even = 1;
	int odd = 0;
	int total_even = 0;
	for (int i = 1; i <= n; ++i) {
		if (S[i] % 2 == 0) {
			total_even += even;
			++even;
		}
		else {
			total_even += odd;
			++odd;
		}
	}
	cout << total_even << endl;
}

int main(int argc, char const *argv[])
{
	linear();
	return 0;
}