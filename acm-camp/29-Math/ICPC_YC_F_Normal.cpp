#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

typedef long long ll;
const ll mod = 998244353;

// 快速幂 计算 a^k % p
ll Pow(ll a, ll k, ll p) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = 1ll * ans * a % p;
        k >>= 1; a = 1ll * a * a % p;
    }
    return ans;
}

ll pre2(ll n) {
    ll a = n, b = n + 1, c = 2 * n + 1;
    if(a % 2 == 0) a /= 2;
    else b /= 2;
    if(a % 3 == 0) a /= 3;
    else if(b % 3 == 0) b /= 3;
    else c /= 3;
    a %= mod; b %= mod; c %= mod;
    return a * b % mod * c % mod;
}

ll pre1(ll n) {
    ll a = n, b = n + 1;
    if(n % 2 == 0) a /= 2;
    else b /= 2;
    a %= mod; b %= mod;
    return a * b % mod;
}

int main() {
    ll n;
    cin >> n;
    ll sq;
    for(sq = 1; sq <= (n / sq); ++sq);
    ll ans = 0;
    ans = (pre2(sq) - pre2(n)) % mod + (pre1(n) - pre1(sq)) % mod * ((n + 1) % mod) % mod;
    for(ll i = sq, k = 2, m = i; i >= 2; --i) {
        for(k = 1, m = i; m <= n / i; m *= i, k += 1);
        ans = (ans + i % mod * (k % mod) * (n + 1) % mod) % mod;
        ans = (ans - (m - 1) / (i - 1) % mod * (i % mod) % mod * (i % mod)) % mod;
    }
    ans = (ans % mod + mod) % mod;
    cout << ans << endl;
}