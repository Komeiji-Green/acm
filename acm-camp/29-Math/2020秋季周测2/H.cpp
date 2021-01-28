#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
const int maxn = 1000050;

ll Pow(ll a, ll k, ll p) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = ans * a % p;
        k >>= 1; a = a * a % p;
    }
    return ans;
}

ll f[maxn];
// C(n, m)
ll C(ll n, ll m) {
    return (f[n] * Pow(f[m], mod - 2, mod) % mod) * Pow(f[n - m], mod - 2, mod) % mod;
}
int main() {
    f[0] = 1;
    for(ll i = 1; i < maxn; ++i) {
        f[i] = f[i-1] * i % mod;
    }
    int T, n, m;
    cin >> T;
    ll ans = 0;
    while(T--) {
        scanf("%d %d", &n, &m);
        if(n == 1 && m == 1) ans = 1;
        else if(n == 1 || m == 1) {
            ans = 2ll * C(n + m - 2, n - 1) % mod;
        } else {
            ans = 4ll * C(n + m - 2, n - 1) % mod;
        }
        printf("%lld\n", (ans + mod) % mod);
    }
}