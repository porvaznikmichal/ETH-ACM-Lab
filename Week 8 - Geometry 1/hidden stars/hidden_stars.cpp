#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

const double PI = 3.14159265358979323846;

struct Point {
	int x, y;
	double distance, angle;

	void set_distance() {
		distance = x*x + y*y;
	}

	void set_angle() {
		// deal with boarder cases
		if (y == 0) {
			angle = (x >= 0) ? PI/2 : 3*PI/2;
		}
		else if (x == 0) {
			angle = (y >= 0) ? 0 : PI;
		}
		else if (x > 0 && y > 0) {
			angle = atan(((double) x )/ y);
		}
		else if (x > 0 && y < 0) {
			angle = atan(((double) abs(y))/ x) + PI/2;
		}
		else if (x < 0 && y < 0) {
			angle = atan(((double) abs(x)) / abs(y)) + PI;
		}
		else {
			angle = atan(((double) x )/ y) + 2*PI;
		}
	}

	Point(int x, int y) : x(x), y(y) {
		set_distance();
		set_angle();
	} 

	void print_point() {
		cout << "Point: " << "x = " << x << ", y = " << y << ", distance = " << distance << ", angle = " << angle*180/PI << endl;
	}

	bool operator<(Point other) const {
		if (angle < other.angle) {
			return true;
		}
		else if (angle == other.angle) {
			return distance < other.distance;
		}
		else {
			return false;
		}
	}
};

void testcase() {
	int n, x, y, p, q;
	cin >> n >> x >> y;

	// read stars
	vector<Point> stars;
	for (int i = 0; i < n; i++) {
		cin >> p >> q;
		Point star(p - x, q - y);
		stars.push_back(star);
	}

	// sort stars
	sort(stars.begin(), stars.end());

	// count hidden
	int hidden = 0;
	for (int i = 1; i < n; i++) {
		if (stars[i].angle == stars[i - 1].angle) {
			hidden += 1;
		}
	}

	cout << hidden << endl;
}

int main(int argc, char const *argv[])
{
	int T; cin >> T;
	while (T--) {
		testcase();
	}
	return 0;
}
