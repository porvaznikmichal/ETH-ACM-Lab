#include <iostream>
#include <vector>

using namespace std;

void print_list(vector<int> &list)
{
    for (int i = 0; i < list.size() - 1; i++)
    {
        cout << list[i] << ", ";
    }
    cout << list[list.size() - 1] << endl;
}

// swap elements on positions a and b
void swap(vector<int> &list, int a, int b)
{
    // make sure a, b in range
    int n = list.size();
    if (a < 0 || a >= n || b < 0 || b >= n)
    {
        cout << "Index out of range. No swap performed." << endl;
        return;
    }

    int temp = list[a];
    list[a] = list[b];
    list[b] = temp;
}

// prints all permutations of {0,..,n}
void permute(vector<int> &list, int left, int right)
{
    if (left == right)
    {
        print_list(list);
    }

    // swap each starting element
    for (int i = left; i <= right; i++)
    {
        // start with element on position i
        swap(list, left, i);
        // recurse
        permute(list, left + 1, right);
        // swap them back
        swap(list, left, i);
    }
}

int main(int argc, char const *argv[])
{
    vector<int> list;

    for (int i = 1; i <= 20; i++)
    {
        list.push_back(i);
    }
    int count = 0;
    do
    {
        // print_list(list);
        count++;
    } while (next_permutation(list.begin(), list.end()));
    cout << count << "\n";
    // permute(list, 0, 9);
    return 0;
}