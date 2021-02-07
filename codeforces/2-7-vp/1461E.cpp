#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf = 0x3f3f3f3f3f3f3f3f;
bool vis[1000500];
int main() {
    ll k, l, r, t, x, y;
    cin >> k >> l >> r >> t >> x >> y;
    if(x > y) {
        if(k + y <= r) k += y;
        k -= l;
        ll d = x - y;
        ll tt;
        if(k < x) tt = 1;
        else tt = (k - x) / d + 2;
        if(tt <= t) {
            printf("No\n");
        } else {
            printf("Yes\n");
        }
    } else {
        k -= l; r -= l;
        ll s = r - y;
        if(s > x) printf("Yes\n");
        else {
            ll res = k % x, d = k / x;
            ll tt = d;
            while(res <= s) {
                if(tt >= t) break;
                if(vis[res]) {
                    tt = inf; break;
                }
                vis[res] = 1;
                k = res + y; d = k / x; res = k % x;
                tt += d;
            }
            if(tt >= t) printf("Yes\n");
            else printf("No\n");
        }
    }
}