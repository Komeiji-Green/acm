#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1005;
const ll mod = 1e9 + 7;
int a[maxn];
bool vis[maxn];
void bs(int pos, int n) {
    memset(vis, 0, sizeof(vis));
    int le = 0, ri = n;
    int mid;
    while(le < ri) {
        mid = (le + ri) / 2;
        vis[mid] = true;
        if(mid <= pos)
            le = mid + 1;
        else 
            ri = mid;
    }
}

ll f[maxn];
int main() {
    int n, x, pos;
    cin >> n >> x >> pos;
    for(int i = 0; i < n; ++i) {
        a[i] = i + 1;
    }
    bs(pos, n);
    f[0] = 1;
    for(int i = 1; i <= n; ++i) {
        f[i] = 1ll * i * f[i - 1] % mod;
    }
    int c1 = 0, c2 = 0, c3;
    for(int i = 0; i < n; ++i) {
        if(vis[i] && i < pos) ++c1;
        if(vis[i] && i > pos) ++c2;
    }
    c3 = n - 1 - c1 - c2;
    ll ans = c3 >= 0 ? f[c3] : 0;
    for(ll i = 1; i <= c1; ++i) {
        ans = ans * (x - i) % mod;
    }
    for(ll i = 0; i < c2; ++i) {
        ans = ans * (n - x - i) % mod;
    }
    printf("%lld\n", (ans + mod) % mod);
}