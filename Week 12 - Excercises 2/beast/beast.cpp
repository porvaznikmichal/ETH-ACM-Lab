#include <iostream>
#include <vector>
#include <cmath>
#include <set>




using namespace std;

bool valid(vector<int> &partial, int r)
{
    // iterate through set and see if vertical offset
    // equals horisontal offset
    int n = partial.size();
    int vertical, horisontal;
    for (int i = 0; i < n; i++)
    {
        horisontal = abs(n - i);
        vertical = abs(r - partial[i]);
        if (horisontal == vertical)
        {
            return false;
        }
    }
    return true;
}

bool backtrack(vector<int> &partial, vector<bool> &remaining)
{
    // if the partial is of full length, we are done
    if (partial.size() == remaining.size())
    {
        return true;
    }

    // else iterate over remaining and see if they are valid
    for (int i = 1; i <= remaining.size(); i++)
    {
        // check if this is avaliable
        if (!remaining[i - 1]) continue;

        if (valid(partial, i))
        {
            // add i to solution and remove from remaining
            partial.push_back(i);
            remaining[i - 1] = false;
            
            // recurse
            if (backtrack(partial, remaining))
            {
                return true;
            }
            else
            {
                // undo this step
                partial.pop_back();
                remaining[i - 1] = true;
            }
        }
    }
    // if we are here, no try has been successfull
    return false;
}

vector<int> solve(int n)
{
    // initialize containers
    vector<int> result;
    vector<bool> remaining(n, true);

    // run backtrack
    bool success = backtrack(result, remaining);

    // if cant be done, return empty
    if (!success)
    {
        result.clear();
    }

    return result;
}


void testcase()
{
    int n;
    cin >> n;

    // solve
    vector<int> result = solve(n);

    // see if solved
    if (result.size() == 0)
    {
        cout << "Impossible" << endl;
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (i == n - 1)
            {
                cout << result[i] << endl;
            }
            else
            {
                cout << result[i] << " ";
            }
        }
    }

}

int main(int argc, char const *argv[])
{
    int t; cin >> t;
    while (t--)
    {
        testcase();
    }
    return 0;
}