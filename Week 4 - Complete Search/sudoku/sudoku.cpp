#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <stack>

using namespace std;

typedef struct {
	vector< vector<int> > field;
	vector< vector<bool> > rows;
	vector< vector<bool> > columns;
	vector< vector<bool> > blocks;
	int num_filled;
	stack<pair<int, int> > empty;
} sudoku;

vector<int> parse(string s, int &num_filled) {
	vector<int> result;
	int bit;
	for (int i = 0; i < 17; i += 2) {
		if (s[i] == '?') {
			bit = 0;
		} 
		else {
			bit = s[i] - '0';
			num_filled++;
		}		
		result.push_back(bit);
	}
	return result;
}

// void print_field(vector<vector<int> > &field) {
// 	// output solved sudoku
// 	for (int i = 0; i < 9; i++) {
// 		for (int j = 0; j < 9; j++) {
// 			if (j == 3 || j == 6) {
// 				cout << " | " << field[i][j];
// 			}
// 			else cout << " " << field[i][j];
// 		}
// 		if (i == 2 || i == 5) {
// 			cout << endl << " - - -   - - -   - - - " << endl;
// 		} else cout << endl;
// 	}
// }

bool backtrack(sudoku &partial) {
	// c++; if (c % 1000000 == 0) cout << c << endl;
	// print_field(partial.field);
	// cout << endl;

	pair<int, int> top = partial.empty .top();
	int x = top.first;
	int y = top.second;

	// run through values
	for (int val = 1; val <= 9; val++) {
		if (!(partial.rows[x][val - 1] || partial.columns[y][val - 1] || partial.blocks[3*(x/3) + (y/3)][val - 1])) {
			// if valid, remove from stack
			partial.empty.pop();
			// found a valid candidate
			if (partial.num_filled == 80) {
				partial.field[x][y] = val;
				// print_field(partial.field);
				return true;
			}
			else {
				partial.field[x][y] = val;
				partial.num_filled++;
				partial.rows[x][val - 1] = true;
				partial.columns[y][val - 1] = true;
				partial.blocks[3*(x/3) + (y/3)][val - 1] = true;

				// recurse
				if (backtrack(partial)) {
					// found_valid = true;
					return true;
				}
				// delete the change we made
				else {
					partial.field[x][y] = 0;
					partial.num_filled--;
					partial.rows[x][val - 1] = false;
					partial.columns[y][val - 1] = false;
					partial.blocks[3*(x/3) + (y/3)][val - 1] = false;
					partial.empty.push(make_pair(x, y));
				}
			}
		}
	}
	return false;			
}

pair<sudoku, bool> initial_validity(vector<vector<int> > &field) {
	vector<bool> row, column, block;
	sudoku initial;
	initial.rows = vector< vector<bool> >(9, vector<bool> (9, false));
	initial.columns = vector< vector<bool> >(9, vector<bool> (9, false));
	initial.blocks = vector< vector<bool> >(9, vector<bool> (9, false));
	initial.field = field;
	initial.empty = stack<pair<int, int> >();

	int bit;
	bool valid = true;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			bit = field[i][j];
			if (bit > 0) {
				// check if we already have this for validity
				if (initial.rows[i][bit - 1]) valid = false;
				else initial.rows[i][bit - 1] = true;
				
				if (initial.columns[j][bit - 1]) valid = false;
				else initial.columns[j][bit - 1] = true;

				if (initial.blocks[3*(i/3) + (j/3)][bit - 1]) valid = false;
				else initial.blocks[3*(i/3) + (j/3)][bit - 1] = true;
			}
			else {
				initial.empty.push(make_pair(i, j));
			}
		}
	}
	return make_pair(initial, valid);
}

void testcase() {
	// read given field
	vector< vector<int> > field(9, vector<int>());
	string s;
	int num_filled = 0;
	
	for (int i = 0; i < 9; i++) {
		getline(cin, s);
		field[i] = parse(s, num_filled);
	}

	// initialize partial solution and chcek for validity
	pair<sudoku, bool> initial = initial_validity(field);
	sudoku partial = initial.first;
	partial.num_filled = num_filled;

	bool found = false;
	if (initial.second) found = backtrack(partial);

	// output
	cout << found << endl;

	// output solved sudoku
	// print_field(partial.field);

}

int main(int argc, char const *argv[])
{
	int num_tests; cin >> num_tests;
	string s;
	getline(cin, s);
	while (num_tests--) {
		testcase();
	}
	return 0;
}