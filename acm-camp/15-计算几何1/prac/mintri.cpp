
#pragma optimize(2)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = 0x7fffffffffffffff;

const int N = 5005;
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
struct Line {
    short int i, j;
    //Point s, e;
    Line() {}
    bool operator< (const Line &b) {
        return sgn( (p[j]-p[i])^(p[b.j]-p[b.i]) ) > 0;
    }
};

Point s, e;
Line l[N*N/2];
int kth[N], rk[N];
int main() {
    int n, tot;
    ll ans = INF;
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        p[i].input();
    }
    sort(p + 1, p + n + 1);
    tot = unique(p + 1, p + n + 1) - p - 1;
    if(tot < n) {
        printf("0.000\n");
    } else {
        tot = 0;
        for(int i = 1; i <= n; ++i) 
            for(int j = i + 1; j <= n; ++j) {
                l[++tot].i = i;
                l[tot].j = j;
            }
        sort(l + 1, l + tot + 1);
        for(int i = 1; i <= n; ++i) kth[i] = i;
        for(int i = 1; i <= n; ++i) rk[kth[i]] = i;

        for(int i = 1, x, y; i <= tot; ++i) {
            s = p[l[i].i]; e = p[l[i].j];

            int le = 0, ri = n;
            int mid = ((le + ri + 1) >> 1);
            while(le < ri) {
                if(sgn( (e-s)^(p[kth[mid]]-s) ) < 0) {
                    le = mid;
                } else {
                    ri = mid - 1;
                }
                mid = ((le + ri + 1) >> 1);
            }
            le = 1, ri = n + 1;
            int mmid = ((le + ri) >> 1);
            while(le < ri) {
                if(sgn( (e-s)^(p[kth[mmid]]-s) ) > 0) {
                    ri = mmid;
                } else {
                    le = mmid + 1;
                }
                mmid = ((le + ri) >> 1);
            }
            
            if(mmid - mid > 3) ans = min(ans, 0ll);
            if(mid >= 1) ans = min(ans, abs( (e-s)^(p[kth[mid]]-s) ));
            if(mmid <= n) ans = min(ans, abs( (e-s)^(p[kth[mmid]]-s) ));

            x = l[i].i, y = l[i].j;
            swap(kth[rk[x]], kth[rk[y]]);
            swap(rk[x], rk[y]);
        }
        if(ans % 2) {
            printf("%lld.500\n", ans/2);
        } else {
            printf("%lld.000\n", ans/2);
        }
    }
}