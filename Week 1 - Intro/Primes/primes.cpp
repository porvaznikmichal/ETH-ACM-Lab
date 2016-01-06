#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<bool> primes(1000000, true);

// Returns an indicator vector for primes at most n
vector<bool> sieve(int n) {
	vector<bool> primes(n, true);

	for (int i = 2; i <= sqrt(n); ++i) {
		// if i is prime, clear all of its multiples
		if (primes[i]) {
			for (int j = i*i; j <= n; j += i) {
				primes[j] = false;
			}
		}
	}

	return primes;
}
int main(int argc, char const *argv[])
{
	int t; cin >> t;
	int m, n;
	primes = sieve(1000001);
	for (int i = 0; i < t; ++i) {
		cin >> m >> n;
		for (int j = m; j <=n; j++) {
			if (primes[j] && j > 1) {
				cout << j << endl;
			}
		}
	}

	return 0;
}