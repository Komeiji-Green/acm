#include<bits/stdc++.h>
using namespace std;

const double eps = 1e-10;
const double inf = 1e14;
int sgn(double x) {
    if(fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
}

struct Point {
    double x, y;
    Point() {}
    Point(double _x, double _y) {
        x = _x; y = _y;
    }
    void input() {
        scanf("%lf%lf", &x, &y);
    }
};

double dist(Point a, Point b) {
    return hypot(a.x - b.x, a.y - b.y);
}

bool cmp1(const Point& a, const Point& b) {
    int c = sgn(a.x-b.x);
    return (c < 0) || (c == 0) && (sgn(a.y-b.y) < 0);
}
bool cmp2(const Point& a, const Point& b) {
    int c = sgn(a.y-b.y);
    return (c < 0) || (c == 0) && (sgn(a.x-b.x) < 0);
}

const int N = 233333;
Point A[N], B[N], C[N];
Point p[N];

void merge(int l, int m, int r, Point A[], Point B[]) {
    int t = l;
    int i = l, j = m + 1;
    while(i <= m && j <= r) B[t++] = (cmp2(A[j], A[i]) ? A[j++] : A[i++]);
    while(i <= m) B[t++] = A[i++];
    while(j <= r) B[t++] = A[j++];
}
double gao(int l, int r, Point A[], Point B[]) {
    int m = (l + r) >> 1;
    if(l == r) { B[l] = A[l]; return inf; }
    double h = min(gao(l, m, A, B), gao(m + 1, r, A, B));
    merge(l, m, r, B, A);
    memcpy(B+l, A+l, sizeof(Point)*(r-l+1));
    int t = 0; Point mid = p[m];    // p是按x排好序的
    for(int i = l; i <= r; ++i) if(sgn(h-fabs(mid.x-B[i].x)) > 0) C[++t] = B[i]; // B是按y排好序的
    double res = inf, up;
    for(int i = 1; i <= t; ++i) {
        up = C[i].y + h;
        for(int j = i + 1; j <= t; ++j) {
            if(sgn(C[j].y - up) < 0)
                res = min(res, dist(C[i], C[j]));
            else break;
        }
    }
    return min(res, h);
}

int main() {
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i) p[i].input();
    sort(p + 1, p + n + 1, cmp1);
    memcpy(A, p, sizeof(p));
    double res = gao(1, n, A, B);
    printf("%.4f\n", res);
}