#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll sqr(ll x) {
    return x * x;
}
struct Point {
    ll x, y;
    Point() {}
    Point(ll _x, ll _y) {
        x = _x; y = _y;
    }
    void input() {
        scanf("%lld %lld", &x, &y);
    }
    ll distance(Point p) {
        return sqr(x - p.x) + sqr(y - p.y);
    }
} p[5050];
bool vis[5050];
int ans[5050];
int main() {
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i) p[i].input();
    ans[1] = 1; vis[1] = 1;
    Point q = p[1];
    for(int i = 2; i <= n; ++i) {
        ll maxv = 0, dis;
        int j;
        for(int i = 1; i <= n; ++i) {
            if(!vis[i] && (dis = q.distance(p[i])) >= maxv) {
                maxv = dis;
                j = i;
            }
        }
        ans[i] = j; vis[j] = 1; q = p[j];
    }
    for(int i = 1; i <= n; ++i) printf("%d ", ans[i]);
    printf("\n");
}