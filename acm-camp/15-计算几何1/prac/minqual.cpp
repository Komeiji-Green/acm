#pragma optimize(2)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = 0x7fffffffffffffff;

const int N = 2005;
int sgn(ll x) {
    if(x == 0) return 0;
    else return x < 0 ? -1 : 1;
}
struct Point {
    ll x, y;
    Point() {}
    Point(ll _x, ll _y) {
        x = _x; y = _y;
    }
    void input() {
        scanf("%lld%lld", &x, &y);
    }
    bool operator<(const Point &b) {
        return x < b.x || x == b.x && y < b.y;
    }
    bool operator==(const Point &b) {
        return x == b.x && y == b.y;
    }
    Point operator -(const Point &b)const{
		return Point(x-b.x,y-b.y);
	}
	ll operator ^(const Point &b)const{
		return x*b.y - y*b.x;
	}
} p[N];

int kth[N], rk[N];
struct Line {
    int i, j;
    bool operator< (const Line& b) {
        return sgn( (p[j]-p[i])^(p[b.j]-p[b.i]) ) > 0;
    }
} l[N*N];

Point s, e;
int main() {
    int n, tot = 0;
    ll maxv = 0, minv = INF;
    while(scanf("%d", &n) != EOF) {
        maxv = 0; minv = INF;
        for(int i = 1; i <= n; ++i) p[i].input();
        if(n < 4) { printf("0 0\n"); continue; }
        sort(p + 1, p + n + 1);
        for(int i = 1; i <= n; ++i) kth[i] = rk[i] = i;
        tot = 0;
        for(int i = 1; i <= n; ++i) 
            for(int j = i + 1; j <= n; ++j) {
                l[++tot].i = i; l[tot].j = j;
            }
        sort(l + 1, l + tot + 1);
        for(int i = 1; i <= tot; ++i) {
            int x = l[i].i, y = l[i].j;
            s = p[x]; e = p[y];

            int le = 0, ri = n;
            int mid = ((le + ri + 1) >> 1);
            while(le < ri) {
                if(sgn( (e-s)^(p[kth[mid]]-s) ) < 0) le = mid;
                else ri = mid - 1;
                mid = ((le + ri + 1) >> 1);
            }

            le = 1, ri = n + 1;
            int mmid = ((le + ri) >> 1);
            while(le < ri) {
                if(sgn( (e-s)^(p[kth[mmid]]-s) ) > 0) ri = mmid;
                else le = mmid + 1;
                mmid = ((le + ri) >> 1);
            }

            if(mid >= 1 && mmid <= n) {
                maxv = max(maxv, abs( (e-s)^(p[kth[n]]-p[kth[1]]) ));
                minv = min(minv, abs( (e-s)^(p[kth[mmid]]-p[kth[mid]]) ));
            }

            swap(kth[rk[x]], kth[rk[y]]);
            swap(rk[x], rk[y]);
        }
        printf("%lld %lld\n", minv, maxv);
    }
    return 0;
}