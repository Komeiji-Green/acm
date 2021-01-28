#include<bits/stdc++.h>
using namespace std;
const double eps = 1e-10;
const int N = 233333;      
int sgn(double x) {
	if(fabs(x) < eps) return 0;
	else return x < 0 ? -1 : 1;
}
inline double sqr(double x) {
	return x * x;
}
struct Point {
	double x, y;
	Point() {
	}
	Point(double _x, double _y) {
		x = _x; y = _y;
	}
	void input() {
		scanf("%lf%lf", &x, &y);
	}
	Point operator-(const Point& b) const {
		return Point(x-b.x, y-b.y);
	}
	Point operator+(const Point& b) const {
		return Point(x+b.x, y+b.y);
	}
	double operator^(const Point& b) const {
		return x * b.y - y * b.x;
	}
	double distance(Point p) {
		return hypot(x - p.x, y - p.y);
	}
};

struct Line {
	Point s, e;
	Line() {
	}
	Line(Point _s, Point _e) {
		s = _s; e = _e;
	}
	Point crosspoint(Line v) {
		double a1 = (v.e - v.s) ^ (s - v.s);
		double a2 = (v.e - v.s) ^ (e - v.s);
		return Point((s.x * a2 - e.x * a1) / (a2 - a1), (s.y * a2 - e.y * a1) / (a2 - a1));
	}
};

Point p[N];
int main() {
	int n;
	cin >> n;
	double h;
	scanf("%lf", &h);
	for(int i = 1; i <= n; ++i) p[i].input();
	Point s = p[n] + Point(0, h), e = p[n];
	Line l1, l2; Point c;
	double ans = 0.0;
	int sg;
	for(int i = n - 1; i >= 1; --i) {
		if((sg = sgn((p[i]-s)^(e-s))) > 0) {
			l1 = Line(s, e);
			l2 = Line(p[i],p[i+1]);
			c = l1.crosspoint(l2);
			e = p[i];
			ans += c.distance(p[i]);
		} else if(sg==0 && sgn((p[i]-s)^(p[i+1]-s))==0) {
			e = p[i];
			ans += p[i].distance(p[i+1]);
		}
	}
	printf("%.10f\n", ans);
}
