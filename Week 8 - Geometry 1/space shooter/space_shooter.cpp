#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point
{
	int x, y;
	Point(int x, int y) : x(x), y(y) {}
	
	void print() {
		cout << "Point: x = " << x << ", y = " << y << endl;
	}
};

struct Vec
{
	int x, y;
	Vec(Point p, Point q) {
		x = q.x - p.x;
		y = q.y - p.y;
	}

};

struct Poly
{
	vector<Point> vertices;
	double area;

	void set_area() {
		int result = 0;
		for (int i = 0; i < vertices.size()-1; i++) {
			result += vertices[i].x * vertices[i+1].y - vertices[i+1].x * vertices[i].y;
		}
		area = (double)result/2.0;
	}

	Poly(vector<Point> vertices) : vertices(vertices) {
		set_area();
	}

	bool operator<(Poly other) const {
		return (area < other.area) ? true : false;
	}

	void print() {
		cout << "Polygon: " << endl;
		for (int i = 0; i < vertices.size(); i++) {
			vertices[i].print();
		}
		cout << "Area = " << area << endl;
	}
};

int cross(Vec v, Vec u) {
	return v.x*u.y - u.x*v.y;
}

double dot(Vec v, Vec u) {
	return v.x*u.x + v.y*u.y;
}

double norm(Vec v) {
	return sqrt(dot(v, v));
}

double angle(Vec v, Vec u) {
	return acos(dot(v,u)/(norm(v)*norm(u)));
}

int ccw(Point p, Point q, Point r) {
	// negative: clockwise
	// 0: colinear
	// positive: counter -clockwise
	return cross(Vec(p,q), Vec(p,r));
}

bool contains(Poly P, Point q) { 
	double sum = 0.0;
	for (int i = 0; i < P.vertices.size()-1; i++) {
		if (ccw(q, P.vertices[i], P.vertices[i+1]) >= 0) {
			sum += angle(Vec(q,P.vertices[i]), Vec(q,P.vertices[i+1]));
		} else {
			sum -= angle(Vec(q,P.vertices[i]), Vec(q,P.vertices[i+1]));
		}
	}
	return (sum > 3);
}

void testcase() {
	int n, m;
	cin >> n >> m;

	// read shots
	vector<Point> shots;
	int x, y;
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		shots.push_back(Point(x, y));
	}

	// read spaceships
	vector<Poly> fleet;
	int num_corners;
	for (int i = 0; i < m; i++) {
		cin >> num_corners;
		vector<Point> ship;
		for (int j = 0; j < num_corners; j++) {
			cin >> x >> y;
			ship.push_back(Point(x, y));
		}
		// add first vertex once more
		ship.push_back(ship[0]);
		//add to fleet
		fleet.push_back(Poly(ship));
	}

	// sort the fleet
	sort(fleet.begin(), fleet.end());

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (contains(fleet[i], shots[j])) {
				cout << fleet[i].area << endl;
				return;
			}
		}
	}

	// if we are here, no ship has been shot
	cout << "fail" << endl;
}

int main(int argc, char const *argv[])
{
	// cout << fixed;
	int T; cin >> T;
	while (T--) {
		testcase();
	}
	return 0;
}
