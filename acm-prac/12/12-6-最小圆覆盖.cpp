#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const double eps = 1e-9;
const double inf = 1e20;
const double pi = acos(-1.0);
int sgn(double x) {
    if(fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
}
inline double sqr(double x) {
    return x * x;
}

struct Point {
    double x, y;
    Point() {}
    Point(double _x, double _y) {
        x = _x, y = _y;
    }
    void input() {
        scanf("%lf%lf", &x, &y);
    }
    void output() {
        printf("%.10f %.10f\n", x, y);
    }
    bool operator== (const Point& b) const {
        return sgn(x - b.x) == 0 && sgn(y - b.y) == 0;
    }
    Point operator-(const Point &b) const {
        return Point(x - b.x, y - b.y);
    }
    Point operator+(const Point &b) const {
        return Point(x + b.x, y + b.y);
    }
    double operator*(const Point &b) const {
        return x * b.x + y * b.y;
    }
    double operator^(const Point &b) const {
        return x * b.y - y * b.x;
    }
    Point operator/(double k) const {
        return Point(x / k, y / k);
    }
    double len() { return hypot(x, y); }
    double distance(Point p) {
        return hypot(x - p.x, y - p.y);
    }
    double cos(Point a, Point b) {
        double d1 = distance(a), d2 = distance(b);
        if(sgn(d1) == 0 || sgn(d2) == 0) return -(1.0);
        return ((a - (*this)) * (b - (*this))) / (d1 * d2);
    }
    Point rotleft() {
        return Point(-y, x);
    }
};

struct Line {
    Point s, e;
    Line() {}
    Line(Point _s, Point _e) {
        s = _s; e = _e;
    }
    bool operator ==(Line v) {
        return (s == v.s) && (e == v.e);
    }
    // 保证两直线不平行或重合
    Point crosspoint(Line v) {
        double a1 = (v.e - v.s) ^ (s - v.s);
        double a2 = (v.e - v.s) ^ (e - v.s);
        return Point((s.x*a2-e.x*a1)/(a2-a1),(s.y*a2-e.y*a1)/(a2-a1));
    }
};

struct circle {
    Point p;
    double r;
    circle() {}
    circle(Point _p, double _r) {
        p = _p; r = _r;
    }
    circle(Point a, Point b, Point c) {
        Line u = Line(((a+b)/2), ((a+b)/2) + ((b-a).rotleft()));
        Line v = Line(((a+c)/2), ((a+c)/2) + ((c-a).rotleft()));
        p = u.crosspoint(v);
        r = p.distance(a);
    }
    // 0 外 1 上或内
    int relation(Point b) {
        double dst = b.distance(p);
        return (sgn(dst - r) <= 0 ? 1 : 0);
    }
};

const int maxn = 100050;
int n;
Point p[maxn];

int main() {
    srand(time(NULL));
    cin >> n;
    for(int i = 1; i <= n; ++i) p[i].input();
    Point a, b;
    random_shuffle(p + 1, p + n + 1);
    circle c(p[1], 0);
    double maxcos, cur;
    for(int i = 2; i <= n; ++i) {
        if(c.relation(p[i])) continue;
        c = circle(p[i], 0);
        for(int j = 1; j < i; ++j) {
            if(c.relation(p[j])) continue;
            a = p[j]; b = p[i];
            c = circle((a+b)/2, a.distance(b)/2);
            maxcos = -1.0; Point t;
            for(int k = 1; k < j; ++k) {
                cur = p[k].cos(a, b);
                if(sgn(cur - maxcos) > 0) { maxcos = cur; t = p[k]; }
            }
            if(sgn(maxcos) <= 0) continue;
            c = circle(a, b, t);
        }
    }
    printf("%.10f\n", c.r);
    c.p.output();
}
