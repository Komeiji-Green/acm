#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int bit[31];
const int maxn = 4333333;
const ll mod = 1e9 + 7;
struct Point {
    ll x, y;
    Point() {}
    Point(ll _x, ll _y) {
        x = _x; y = _y;
    }
    void input() {
        scanf("%lld%lld", &x, &y);
    }
};
struct Line {
    Point s, e;
    Line() {}
    Line(Point _s, Point _e) {
        s = _s; e = _e;
        Point tmp;
        if(s.y > e.y) {
            tmp = s;
            s = e;
            e = tmp;
        }
    }
    int inter(ll y) {
        if(s.y == e.y) return 0;
        return s.y <= y && y <= e.y;
    }
    ll crosspoint(ll y) {
        ll u = (y - s.y) * (e.x - s.x);
        ll x = s.x + u / (e.y - s.y);
        if(u % (e.y - s.y) == 0 || u < 0) x -= 1;
        return x;
    }
    void reverse() {
        s.x = -s.x; e.x = -e.x;
    }
};
Line l[3];
ll inv[maxn], p[maxn];
int cnt[maxn];
ll gao(ll n) {
    ll res = 0;
    ll sum, ri, j;
    ll x = 0, y = 0;
    for(int i = 0;  i < 3; ++i) {
        if(l[i].inter(0)) {
            x = min(x, l[i].crosspoint(0));
        }
    }
    if(x >= 0) {
        sum = 1; ri = 1; j = 0;
    } else {
        sum = 0; ri = 0; j = -1;
    }
    //id[0][op] = j; cur[0][op] = sum;
    res = (res + sum) % mod;
    if(j == y) cnt[y]++;
    for(y = 1; y <= n; ++y) {
        x = y;
        for(int i = 0; i < 3; ++i) {
            if(l[i].inter(y)) {
                x = min(x, l[i].crosspoint(y));
            }
        }
        if(abs(x)%2!=y%2) --x;
        if(x < -y) {
            sum = 0; ri = 0; j = -1;
        } else {
            x = (x + y) / 2;
            sum = (2 * sum - ri) % mod;
            ri = (ri * y % mod) * inv[y-j] % mod;
            if(j < x) {
                for(++j; j <= x; ++j) {
                    if(j == 0) {
                        ri = 1;
                    } else {
                        ri = (ri * (y - j + 1) % mod) * inv[j] % mod;
                    }
                    sum = (sum + ri) % mod;
                }
                --j;
            } else {
                for(; j > x; --j) {
                    sum = (sum - ri) % mod;
                    ri = (ri * j % mod) * inv[y - j + 1] % mod;
                }
            }
        }
        res = (res + sum) % mod;
        if(j == y) cnt[y]++;
    }
    return res;
}
void init() {
    inv[0] = 0, inv[1] = 1;
    for(ll i = 2; i < maxn; i++) inv[i] = inv[mod % i] * (mod - mod / i) % mod;
    p[0] = 1;
    for(int i = 1; i < maxn; ++i) p[i] = 2ll * p[i-1] % mod;
}
int main() {
    int T;
    cin >> T;
    init();
    while(T--) {
        Point A, B, C;
        A.input(); B.input(); C.input();
        l[0] = Line(B, C); l[1] = Line(A, C); l[2] = Line(A, B);
        ll n = max(max(A.y, 0ll), max(B.y, C.y));
        for(int i = 0; i <= n; ++i) cnt[i] = 0;

        ll ans = gao(n);
        for(int i = 0; i < 3; ++i) l[i].reverse();
        ans = (ans + gao(n)) % mod;
        ans = (p[n+1]-1-ans) % mod;
        for(int i = 0; i <= n; ++i) {
            if(cnt[i] > 1) {
                ans = (ans + p[i]) % mod;
            }
        }
        printf("%lld\n", (ans + mod) % mod);
    }
}