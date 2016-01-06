#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void testcase() {
	int n; cin >> n;
	int number; cin >> number;

	vector<int> orig1(10,0);
	vector<int> orig2(10,0);

	int digit;
	for (int i = 0; i < n; i++) {
		digit = number % 10;
		orig1[digit]++;
		orig2[digit]++;

		number /= 10;
	}

	int current = 0, maximum = 0;
	for (int i = 1; i < 10; i++) {
		if (orig1[i] == 0 || orig2[10 - i] == 0) {
			current = orig1[0];
		}
		else {
			current = 1;
			orig1[i]--;
			orig2[10 - i]--;
			// count pairs of 9
			for (int j = 0; j < 10; j++) {
				current += min(orig1[j], orig2[9 - j]);
			}
			// increment orig back
			orig1[i]++;
			orig2[10 - i]++;

			// add additional zeros
			current += max(0, orig1[0] - orig1[9]);
		}
		if (current > maximum) {
			maximum = current;
		}
	}

	// check for case with one 5 and only 9s and 0s
	bool case_905 = ((orig1[5] == 1) && (orig1[0] > 0) && (orig1[9] > 0) && (orig1[0] >= orig1[9])) ? true : false;
	for (int i = 1; i < 9; i++) {
		if (i != 5 && orig1[i] > 0) {
			case_905 = false;
		}
	}

	if (case_905) {
		cout << maximum - 1 << endl;
	}
	else {
		cout << maximum << endl;
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
