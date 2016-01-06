#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

const int MAX_INT = 100000000;

void solve(string &s, vector< vector<int> > &table, vector<string> &result, string word, int a, int b) {
	string new_word;
	// if we have 0 or 1 characters
	if (b - a <= 1) {
		new_word = word;
		// if its exactly one character
		if (b - a == 1) {
			new_word.push_back(s[a]);
		}
		reverse(word.begin(), word.end());
		new_word += word;
		result.push_back(new_word);
	}
	else if (s[a] == s[b - 1]) {
		new_word = word;
		new_word += s[a];
		solve(s, table, result, new_word, a + 1, b - 1);
	}
	else {
		if (table[a + 1][b] <= table[a][b - 1]) {
			new_word = word;
			new_word += s[a];
			solve(s, table, result, new_word, a + 1, b);
		}
		if (table[a + 1][b] >= table[a][b - 1]) {
			new_word = word;
			new_word += s[b - 1];
			solve(s, table, result, new_word, a, b - 1);
		}
	}
}


void testcase(string s) {
	// build table
	int n = s.size();
	vector< vector<int> > table(n, vector<int>(n + 1, 0));

	for (int jump=2; jump <= n; ++jump) {
		for (int i=0; i+jump <= n; ++i) {
			int j=i+jump;
			// cout << "i = " << i << ", j = " << j << endl;
			if (s[i] == s[j - 1]) {	
				table[i][j] = table[i+1][j-1];
			}
			else {
				table[i][j] = 1 + min(table[i+1][j], table[i][j-1]);
			}
		}
	}

	// get palindromes
	vector<string> result;
	solve(s, table, result, "", 0, n);

	// sort
	sort(result.begin(), result.end());
	cout << table[0][n];
	for (int i = 0; i < result.size(); i++) {
		cout << " " << result[i];
	}
	cout << endl;
}

int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);
	string s;
	while (getline(cin, s)) {
		testcase(s);
	}
	return 0;
}

