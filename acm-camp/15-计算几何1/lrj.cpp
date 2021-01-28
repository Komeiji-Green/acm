#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>

const double eps = 1e-10;
int sgn(double x) {
    if(fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
}
int sgn(int x) {
    if(x == 0) return 0;
    else return x < 0 ? -1 : 1;
}

typedef double ll;
struct Point {
    ll x, y;
    Point() {}
    Point(ll _x, ll _y): x(_x), y(_y) {}
    void input() { scanf("%lf%lf",&x,&y); }
	void output() { printf("%.2f %.2f\n",x,y); }
    Point operator+ (Point B) const { return Point(x + B.x, y + B.y); }
    Point operator- (Point B) const { return Point(x - B.x, y - B.y); }
    Point operator* (ll p) const { return Point(x * p, y * p); }
    Point operator/ (ll p) const { return Point(x / p, y / p); }
    bool operator== (const Point& b) {
        return sgn(x-b.x) == 0 && sgn(y-b.y) == 0;
    }
    bool operator< (const Point& b) {
        return sgn(x-b.x) == 0 ? sgn(y-b.y) < 0 : x < b.x;
    }
    ll operator* (Point B) { return x * B.x + y * B.y; }
    ll len() { return sqrt(x * x + y * y); }
    ll len2() { return x * x + y * y; }
    Point rotleft() { return Point(-y, x); }
    Point rotright() { return Point(y, -x); }
    // 绕p逆时针旋转rad
    Point rotate(Point p, double rad) {
        Point v = (*this) - p;
        double c = cos(rad), s = sin(rad);
        return Point(p.x + v.x*c - v.y*s, p.y + v.x*s + v.y*c);
    }
    // 自旋rad
    Point rotate(double rad) {
        double c = cos(rad), s = sin(rad);
        return Point(x*c - y*s, x*s + y*c);
    }

};

ll Area2(Point a, Point b, Point c) { return (b - a) ^ (c - a); }
