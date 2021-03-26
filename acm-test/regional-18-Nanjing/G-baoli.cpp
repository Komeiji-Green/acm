#include<bits/stdc++.h>
using namespace std;

const double eps = 1e-6;
int sgn(double x) {
    if(fabs(x) < eps) return 0;
    return x < 0 ? -1 : 1;
}
inline double sqr(double x) {
    return x * x;
}
struct Point {
    double x, y;
    Point() {}
    Point(double _x, double _y) {
        x = _x; y = _y;
    }
    double dis(Point p) {
        return sqr(x-p.x)+sqr(y-p.y);
    }
} p[1005];
int main() {
    int n; cin >> n;
    ++n;
    int m = n;
    double x = 0, y = 0, h = sqrt(3) / 2, a, b, c;
    int tot = 0;
    for(int i = 1; i <= n; ++i, --m, x += 0.5, y += h) {
        for(int j = 0; j < m; ++j) {
            p[++tot] = Point(x + j, y);
        }
    }
    int cnt = 0;
    for(int i = 1; i <= tot; ++i)
        for(int j = i + 1; j <= tot; ++j)
            for(int k = j + 1; k <= tot; ++k) {
                a = p[i].dis(p[j]);
                b = p[j].dis(p[k]);
                c = p[k].dis(p[i]);
                if(sgn(a-b)==0 && sgn(b-c)==0) ++cnt;
            }
    printf("%d\n", cnt);
}