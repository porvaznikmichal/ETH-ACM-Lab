#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>


using namespace std;

const long MAX_INT = LONG_MAX;

bool comp_x(pair<int, int> const &a, pair<int, int> const &b) {
    if (a.first == b.first) {
        return a.second < b.second;
    }
    else return a.first < b.first;
}

bool comp_y(pair<int, int> const &a, pair<int, int> const &b) {
    return a.second < b.second;
}

void print(vector<pair<int, int> > &points, int a, int b) {
    for (int i = a; i <= b; i++) {
        cout << "(" << points[i].first << "," << points[i].second << "), ";
    }
    cout << endl;
}

long distance(pair<int, int> &a, pair<int, int> &b) {
    long dx = a.first - b.first;
    long dy = a.second - b.second;
    return dx*dx + dy*dy;
}

long closest(vector<pair<int, int> > &points, int left, int rigth) {
    int num_elements = rigth - left + 1;
    // if there is only one point
    if (num_elements == 1) {
        return MAX_INT;
    }
    // if there are two points
    else if (num_elements == 2) {
        return distance(points[left], points[rigth]);
    }

    // otherwise partially sort around median
    int mid = left + num_elements/2;
    nth_element(points.begin() + left, points.begin() + mid, points.begin() + rigth + 1, comp_x);
    int median = points[mid].first;


    // divide
    long closest_left = closest(points, left, mid - 1);
    long closest_rigth = closest(points, mid, rigth);
    long r = min(closest_left, closest_rigth);

    // iterate through left half
    int left_index = mid;
    for (int i = left; i < mid; i++) {
        // check if this point is close enough to the median
        if (median - points[i].first > r) continue;

        // else find first index of left half within r of current
        while (points[i].second - points[left_index].second > r) {
            left_index++;
            // if we moved to the end of field, we are done
            if (left_index > rigth) {
                return r;
            }
        }

        // if left_index is far from ith point
        if (points[left_index].second - points[i].second > r) continue;

        // else iterate through six points
        for (int k = left_index; k <= min(left_index + 5, rigth); k++) {
            if (points[k].first - median > r) continue;
            if (abs(points[k].second - points[i].second) <= r) {
                r = min(r, distance(points[i], points[k]));
            }
        }
    }
    return r;

}

void testcase() {
    int N;
    cin >> N;

    // read 
    int x, y;
    vector<pair<int, int> > points;
    for (int i = 0; i < N; i++) {
        cin >> x >> y;
        points.push_back(make_pair(x, y));
    }

    // sort by y
    sort(points.begin(), points.end(), comp_y);

    cout << closest(points, 0, N - 1) << endl;
}

int main(int argc, char const *argv[])
{
    int t; cin >> t;
    while (t--) {
        testcase();
    }
    return 0;
}