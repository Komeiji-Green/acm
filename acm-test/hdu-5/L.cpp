#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 998244353;
const int maxn = 5000007;
ll inv[maxn], ip[maxn], f[maxn], ifr[maxn];
void init() {
    inv[0] = 0, inv[1] = 1;
    for(int i = 2; i < maxn; ++i) inv[i] = inv[mod % i] * (mod - mod / i) % mod;
    ip[0] = 1;
    for(int i = 1; i < maxn; ++i) ip[i] = ip[i-1] * inv[2] % mod;
    f[0] = 1;
    for(int i = 1; i < maxn; ++i) f[i] = i * f[i-1] % mod;
    ifr[0] = 1;
    for(int i = 1; i < maxn; ++i) ifr[i] = ifr[i-1] * inv[i] % mod;
}

ll ans[maxn];
int main() {
    init();
    int T, n;
    ll isum;
    cin >> T;
    while(T--) {
        scanf("%d", &n);
        isum = 1;
        for(ll i = n - 1; i > 0; i -= 2) isum = isum * inv[i] % mod;
        int m = (1 + n) / 2;
        for(int i = 1; i < m; ++i) ans[i] = 0;
        for(int i = m; i <= n; ++i) {
            ans[i] = f[i-1]*ifr[i-m]%mod*ip[i-m]%mod*isum%mod;
        }
        for(int i = 1; i < n; ++i) printf("%lld ", (ans[i]+mod)%mod);
        printf("%lld\n", (ans[n]+mod)%mod);
    }
}