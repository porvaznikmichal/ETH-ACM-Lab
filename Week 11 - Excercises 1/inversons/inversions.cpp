#include <iostream>
#include <vector>

using namespace std;

void print(vector<int> &list, int left, int right)
{
    cout << "[";
    for (int i = left; i < right - 1; i++)
    {
        cout << list[i] << ", ";
    }
    cout << list[right - 1] << "]";
}

void merge(vector<int> &list, int left, int mid, int right, int &inversions)
{
    // cout << "Current number of inversions = " << inversions << endl;
    // cout << "Merging: ";
    // print(list, left, mid);
    // cout << " and ";
    // print(list, mid, right);
    // cout << endl;

    vector<int> result;

    int i = left;
    int j = mid;

    // while both lists not empty
    while (i < mid && j < right)
    {
        // we have an inversion
        if (list[i] > list[j])
        {
            result.push_back(list[j]);
            inversions += mid - i;
            j++;
        }
        else
        {
            result.push_back(list[i]);
            i++;
        }
    }

    // empty the rest
    while (i < mid)
    {
        result.push_back(list[i]);
        i++;
    }
    while (j < right)
    {
        result.push_back(list[j]);
        j++;
    }

    // put result into list
    for (int i = left; i < right; i++)
    {
        list[i] = result[i - left];
    }

    // cout << "Merged: ";
    // print(list, left, right);
    // cout << "\nCurrent number of inversions = " << inversions << endl;
}


void merge_sort(vector<int> &list, int left, int right, int &inversions)
{
    if (right - left < 2) {
        // already sorted
        return;
    }

    // else split
    int mid = (left + right) / 2;
    merge_sort(list, left, mid, inversions);
    merge_sort(list, mid, right, inversions);
    merge(list, left, mid, right, inversions);
}

void testcase() 
{
    // read input
    int n; cin >> n;
    vector<int> perm(n,0);
    int digit;
    for (int i = 0; i < n; i++) 
    {
        cin >> digit;
        perm[i] = digit;
    }

    int inversions = 0;
    merge_sort(perm, 0, n, inversions);

    // output
    cout << inversions % 10000 << endl;
}

int main(int argc, char const *argv[])
{
    int t; cin >> t;
    while (t--) {
        testcase();
    }
    return 0;
}
