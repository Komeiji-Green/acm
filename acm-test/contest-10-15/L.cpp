#include<bits/stdc++.h>
#include<cmath>
using namespace std;
const double eps = 1e-9;
const double pi = acos(-1.0);
const int maxp = 1010;
int sgn(double x) {
    if(fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
}
inline double sqr(double x) { return x * x; }

struct Point {
    double x, y;
    Point() {}
    Point(double _x, double _y) { x = _x, y = _y; }
    void input() {scanf("%lf%lf", &x, &y);}
    bool operator == (Point b) const {
        return sgn(x - b.x) == 0 && sgn(y - b.y) == 0;
    }
    Point operator-(const Point& b) const {
        return Point(x - b.x, y - b.y);
    }
    Point operator+(const Point& b) const {
        return Point(x + b.x, y + b.y);
    }
    double operator*(const Point& b) const {
        return x * b.x + y * b.y;
    }
    double operator^(const Point& b) const {
        return x * b.y - y * b.x;
    }
    Point rotleft() {
        return Point(-y, x);
    }
    double len() {
        return hypot(x, y);
    }
    Point trunc(double r){
        double l = len();
        if(!sgn(l)) return *this;
        r /= l;
        return Point(x * r, y * r);
    }
};

struct polygon {
    int n;
    Point p[maxp];
    void add(Point q) {
        p[n++] = q;
    }
    void input(int _n) {
        n = _n;
        for(int i = 0; i < n; ++i)
            p[i].input();
    }
    double getarea() {
        double sum = 0;
        for(int i = 0; i < n; ++i) {
            sum += (p[i] ^ p[(i + 1) % n]);
        }
        return fabs(sum) / 2;
    }
    double getcircu() {
        double sum = 0;
        for(int i = 0; i < n; ++i) {
            sum += (p[(i + 1) % n] - p[i]).len();
        }
        return sum;
    }
};

struct Line {
    Point s, e;
    Line() {}
    Line(Point _s, Point _e) {
        s = _s, e = _e;
    }
    double getangle() {
        return atan2(e.y - s.y, e.x - s.x);
    }
};

Point crosspoint(Line u, Line v) {
    double a1 = (v.e - v.s) ^ (u.s - v.s);
    double a2 = (v.e - v.s) ^ (u.e - v.s);
    return Point((u.s.x * a2 - u.e.x * a1) / (a2 - a1), (u.s.y * a2 - u.e.y * a1) / (a2 - a1));
}

bool onRight(Line a, Line b, Line c) {
    Point o = crosspoint(b, c);
    return ((a.e - a.s) ^ (o - a.s)) < 0;
}


Line L[maxp], que[maxp];
Point p[maxp];

void HalfPlaneIntersection(polygon &con, int n) {
    // sort
    int head = 0, tail = 0, cnt = 0;
    for(int i = 0; i < n - 1; ++i) {
        if(sgn(L[i].getangle() - L[i+1].getangle()) != 0) L[cnt++] = L[i];
    }
    L[cnt++] = L[n - 1];

    for(int i = 0; i < cnt; ++i) {
        while(tail - head > 1 && onRight(L[i], que[tail-1], que[tail-2])) --tail;
        while(tail - head > 1 && onRight(L[i], que[head], que[head+1])) ++head;
        que[tail++] = L[i];
    }
    while(tail - head > 1 && onRight(que[head], que[tail - 1], que[tail - 2])) --tail;
    while(tail - head > 1 && onRight(que[tail - 1], que[head], que[head + 1])) ++head;

    con.add(crosspoint(que[head], que[tail - 1]));
    for(int j = head + 1; j < tail; ++j) {
        con.add(crosspoint(que[j], que[j - 1]));
    }
}

int main() {
    int T;
    cin >> T;
    int n, A, B;
    double r;
    polygon con, po;
    while(T--) {
        scanf("%d%lf", &n, &r);
        scanf("%d%d", &A, &B);
        po.input(n);
        for(int i = 0; i < n; ++i) {
            p[i] = po.p[i];
        }
        p[n] = p[0];
        for(int i = 0; i < n; ++i) L[i] = Line(p[i], p[i+1]);

        Point ss, ee;
        for(int i = 0; i < n; ++i) {
            ss = L[i].s + (L[i].e - L[i].s).rotleft().trunc(r);
            ee = ss + L[i].e - L[i].s;
            L[i] = Line(ss, ee);
        }

        if(n <= 2) {
            printf("%.12f\n", 0.0);
            continue;
        }

        con.n = 0;
        HalfPlaneIntersection(con, n);
        if(con.n < 2 || A <= B) {
            printf("%.12f\n", po.getarea() * A);
        } else {
            double area = con.getarea() + con.getcircu() * r + pi * r * r;
            printf("%.12f\n", po.getarea() * A + area * (B - A));
        }
    }
}