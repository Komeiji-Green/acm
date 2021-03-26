
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

int main() {
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i) p[i].input();
    ll ans = INF;
    for(int i = 1; i <= n; ++i) {
        for(int j = i + 1; j <= n; ++j) {
            for(int k = j + 1; k <= n; ++k) {
                ans = min(ans, abs( (p[j]-p[i])^(p[k]-p[i]) ));
            }
        }
    }
    if(ans % 2) {
        printf("%lld.500\n", ans/2);
    } else {
        printf("%lld.000\n", ans/2);
    }
}   