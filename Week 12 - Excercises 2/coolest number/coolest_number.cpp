#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<int, int> coolness;

pair<int, int> process(vector<int> &list)
{
    int left = 0;
    int right = 0;
    for (int i = 0; i < 5; i++)
    {
        left *= 10;
        left += list[i];
    }
    for (int i = 5; i < 10; i++)
    {
        right *= 10;
        right += list[i];
    }

    return make_pair(left, right);
}

/*
Iterates through all permutations of size 10, computing each ratio
*/
map<int, int> precompute()
{
    map<int, int> result;

    // initialize vector
    vector<int> list;
    for (int i = 0; i < 10; i++)
    {
        list.push_back(i);
    }

    // iterate through permutations
    pair<int, int> numbers;
    int ratio;
    do
    {
        numbers = process(list);
        // check divisibility
        if (numbers.first % numbers.second != 0) continue;


        // else get ratio
        ratio = numbers.first / numbers.second;

        // check if its in map
        if (result.count(ratio) == 0)
        {
            result[ratio] = 1;
        }
        else
        {
            result[ratio]++;
        }

    } while (next_permutation(list.begin(), list.end()));

    return result;
}

void testcase()
{
    int k; cin >> k;

    // keep the best
    pair<int, int> best = make_pair(-1, -1);

    int n, score;
    for (int i = 0; i < k; i++)
    {
        cin >> n;
        if (coolness.count(n) == 0)
        {
            score = 0;
        }
        else
        {
            score = coolness[n];
        }

        if (score > best.second)
        {
            best = make_pair(n, score);
        }
        else if (score == best.second && n < best.first)
        {
            best = make_pair(n, score);
        }
    }

    // output
    cout << best.first << " " << best.second << "\n";
}

int main(int argc, char const *argv[])
{
    // precompute coolness map
    coolness = precompute();
    int t; cin >> t;
    while (t--)
    {
        testcase();
    }
    return 0;
}
