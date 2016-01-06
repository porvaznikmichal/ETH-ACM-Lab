#include <iostream>

using namespace std;

void testcase() {
	int num_terms; cin >> num_terms;

	double sum = 0;
	double number;
	for (int i = 0; i < num_terms; ++i) {
		cin >> number;
		sum  += number;
	}
	cout << sum << endl;
}

int main(int argc, char const *argv[])
{
	int num_tests; cin >> num_tests;
	while (num_tests--) {
		testcase();
	}
	return 0;
}