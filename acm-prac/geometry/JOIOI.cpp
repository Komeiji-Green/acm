#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const double eps = 1e-9;
const double pi = acos(-1.0);
const int maxp = 10005;
int sgn(double x) {
    if(fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
}
inline double sqr(double x) { return x * x; }

struct Point {
    double x, y, rad;
    int tag;
    Point() {}
    Point(double _x, double _y) { x = _x, y = _y; }
    void input() {
        scanf("%lf%lf", &x, &y);
    }
    Point operator-(const Point &b) const {
        return Point(x - b.x, y - b.y);
    }
    double operator^(const Point& b) const {
        return x * b.y - y * b.x;
    }
    double operator*(const Point& b) const {
        return x * b.x + y * b.y;
    }
    Point operator+(const Point& b) const {
        return Point(x + b.x, y + b.y);
    }
    bool operator<(const Point& b) const {
        return rad < b.rad;
    }
    void getrad() {
        rad = atan2(y, x);
    }
};
Point inp[maxp], p[maxp];
ll cnt1[3], cnt2[3];
int main() {
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i) {
        inp[i].input();
        scanf("%d", &inp[i].tag);
    }
    Point cen, tmp;
    ll ans = 0;
    for(int x = 0; x < n; ++x) {
        memcpy(p, inp, sizeof(inp));
        memset(cnt1, 0, sizeof(cnt1));
        memset(cnt2, 0, sizeof(cnt2));
        if(x) swap(p[0], p[x]);
        cen = p[0];
        for(int i = 1, tg; i < n; ++i) {
            tg = p[i].tag;
            ++cnt2[tg];
            p[i] = p[i] - cen;
            p[i].tag = tg;
            p[i].getrad();
        }
        sort(p + 1, p + n);
        for(int i = 1; i < n; ++i) {
            p[i - 1 + n] = p[i];
            p[i - 1 + n].rad += 2 * pi;
        }
        int m = 2 * n - 1;
        cnt1[p[1].tag]++;
        cnt2[p[1].tag]--;
        for(int i = 1, j = 1, s = cen.tag, e; i < n; ++i) {
            while((j + 1 < m) && p[j + 1].rad < p[i].rad + pi) {
                ++j;
                cnt1[p[j].tag]++;
                cnt2[p[j].tag]--;
            }
            cnt1[p[i].tag]--;
            e = p[i].tag;
            ans += cnt2[(s + 1) % 3] * cnt2[(s + 2) % 3] * cnt1[(e + 1) % 3] * cnt1[(e + 2) % 3];
            cnt2[p[i].tag]++;
        }
    
        /*
        int stg = cen.tag, etg;
        for(int i = 1; i < n; ++i) {
            etg = p[i].tag;
            cnt1[etg]--;
            ans += cnt2[(stg + 1) % 3] * cnt2[(stg + 2) % 3] * cnt1[(etg + 1) % 3] * cnt1[(etg + 2) % 3];
            cnt2[etg]++;
        }*/
    }
    cout << ans / 2 << endl;
}