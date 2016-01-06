#include <iostream>
#include <vector>

using namespace std;

int solve(vector< vector<int> > &field, vector< vector<bool> > &jokers)
{
    int m = field.size();
    int n = field[0].size();

    // check special cases
    if (m == 1)
    {
        int sum = 0;
        for (int i = 0; i < n; i++)
        {
            sum += field[0][i];
        }
        return sum;
    }
    if (n == 1)
    {
        int sum = 0;
        for (int i = 0; i < m; i++)
        {
            sum += field[i][0];
        }
        return sum;
    }

    // else
    // initialize dynamic prgramming tables that hold the
    // highest and lowest score achievable from position (i, j)
    // respectively
    vector< vector<int> > most(m, vector<int>(n, 0));
    vector< vector<int> > least(m, vector<int>(n, 0));

    // fill in the edges
    most[m - 1][n - 1] = field[m - 1][n - 1];
    least[m - 1][n - 1] = field[m - 1][n - 1];
    for (int i = m - 2; i >= 0; i--)
    {
        most[i][n - 1] = most[i + 1][n - 1] + field[i][n - 1];
        least[i][n - 1] = least[i + 1][n - 1] + field[i][n - 1];
    }

    for (int i = n - 2; i >= 0; i--)
    {
        most[m - 1][i] = most[m - 1][i + 1] + field[m - 1][i];
        least[m - 1][i] = least[m - 1][i + 1] + field[m - 1][i];
    }

    // fill in the rest
    for (int i = m - 2; i >= 0; i--)
    {
        for (int j = n - 2; j >= 0; j--)
        {
            // go through the cases
            if (jokers[i + 1][j] && jokers[i][j + 1])
            {
                most[i][j] = field[i][j] + max(most[i][j + 1], most[i + 1][j]);
                least[i][j] = field[i][j] + min(least[i][j + 1], least[i + 1][j]);
            }
            else if (jokers[i + 1][j] && !jokers[i][j + 1])
            {
                most[i][j] = field[i][j] + max(least[i][j + 1], most[i + 1][j]);
                least[i][j] = field[i][j] + min(most[i][j + 1], least[i + 1][j]);
            }
            else if (!jokers[i + 1][j] && jokers[i][j + 1])
            {
                most[i][j] = field[i][j] + max(most[i][j + 1], least[i + 1][j]);
                least[i][j] = field[i][j] + min(least[i][j + 1], most[i + 1][j]);
            }
            else
            {
                most[i][j] = field[i][j] + max(least[i][j + 1], least[i + 1][j]);
                least[i][j] = field[i][j] + min(most[i][j + 1], most[i + 1][j]);
            }
        }
    }

    return most[0][0];
}

void testcase()
{
    // read the playfield
    int n, m;
    cin >> m >> n;

    vector< vector<int> > field(m, vector<int>(n, 0));
    int val;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> val;
            field[i][j] = val;
        }
    }

    // read the jokers
    int num_jokers;
    cin >> num_jokers;

    vector< vector<bool> > jokers(m, vector<bool>(n, false));
    int x, y;
    for (int i = 0; i < num_jokers; i++)
    {
        cin >> x >> y;
        jokers[x - 1][y - 1] = true;
    }

    cout << solve(field, jokers) << endl;
}

int main(int argc, char const *argv[])
{
    int t;
    cin >> t;
    while (t--)
    {
        testcase();
    }
    return 0;
}
