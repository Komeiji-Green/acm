#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll mod = 1e9 + 7;
ll Pow(ll a, ll k, ll p) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = ans * a % p;
        k >>= 1; a = a * a % p;
    }
    return ans;
}


const int maxn = 1000050;
ll b[maxn], a[maxn], f[maxn], rf[maxn], F = 1, ans;
int main() {
    ll n, k, m;
    cin >> n >> k;
    m = k + 1;
    b[0] = 0;
    for(ll i = 1; i <= m; ++i) {
        b[i] = Pow(i, k, mod) + b[i - 1] % mod;
    }
    f[0] = 1, rf[0] = 1;
    for(ll i = 1; i <= m; ++i) {
        f[i] = i * f[i - 1] % mod;
        rf[i] = Pow(f[i], mod - 2, mod);
    }
    for(ll i = 0; i <= m; ++i) {
        a[i] = rf[i] * rf[m - i] % mod;
        if((m - i) % 2) a[i] = -a[i];
    }
    bool flag = false;
    for(ll i = 0; i <= m; ++i) {
        if((n - i) % mod == 0) {
            flag = true;
            for(ll j = 0; j <= m; ++j) {
                if(j == i) continue;
                F = F * (n - j) % mod;
            }
            ans = (F * b[i] % mod) * a[i] % mod; 
            break;
        }
    }
    if(!flag) {
        for(ll i = 0; i <= m; ++i) {
            F = F * (n - i) % mod;
        }
        ans = 0;
        for(ll i = 0, Fi; i <= m; ++i) {
            Fi = F * Pow(n - i, mod - 2, mod) % mod;
            ans = (ans + (Fi * b[i] % mod) * a[i] % mod) % mod;
        }
    }
    printf("%lld\n", (ans + mod) % mod);
}  