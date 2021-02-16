#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = 0x3f3f3f3f3f3f3f3f;
const int inf = 0x3f3f3f3f;
const int N = 233333;

int a[N], n;
ll f[N];
int main() {
    int T;
    cin >>  T;
    ll n, k, p;
    for(int cas = 1; cas <= T; ++cas) {
        scanf("%lld %lld %lld", &n, &k, &p);
        f[0] = 1;
        for(ll i = 1; i <= n; ++i) f[i] = i * f[i-1] % p;
        ll ans = 0, le, ri;
        if(k >= n) {
            ans = f[n];
        } else {
            ll r = n - k;
            le = f[k], ri = (r - 1) * (r - 1) + 1;
            ans = (ans + le * ri % p) % p;
            for(ll i = 1; i <= k; ++i) {
                ans = (ans + r * f[k] % p) % p;
            }
            for(ll i = k + 2; i <= n; ++i) {
                ans = (ans + f[k]) % p;
            }
        }
        printf("Case #%d: %lld\n", cas, ans);
    }
}