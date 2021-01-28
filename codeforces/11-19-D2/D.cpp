#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
const ll mod=  998244353;

// 快速幂 计算 a^k % p
ll Pow(ll a, ll k, ll p) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = ans * a % p;
        k >>= 1; a = a * a % p;
    }
    return ans;
}

// 求模p的乘法逆元 [1, p - 1]
ll inv[maxn];
void init(ll n) {
    inv[0] = 0, inv[1] = 1;
    for(ll i = 2; i <= n; i++) inv[i] = inv[mod % i] * (mod - mod / i) % mod;
}

ll f[maxn], rf[maxn]; // 阶乘
ll Com(ll n, ll m) {
    if(m > n) return 0;
    return (f[n] * rf[m] % mod) * rf[n-m] % mod;
}



int main() {
    init(200050);
    f[0] = rf[0] = 1;
    for(ll i = 1; i <= 200050; ++i) {
        f[i] = i * f[i-1] % mod;
        rf[i] = inv[i]*rf[i-1]%mod;
    }
    ll n, s;
    cin >> n;
    if(n % 2 == 0) s = 2;
    else s = 1;

    ll ans = 0;
    for(; s <= (n + s) / 2; s += 2) {
        ans = (ans + Com((n+s)/2-1,s-1)) % mod;
    }
    //printf("%lld\n", (ans + mod) % mod);
    ll mu = Pow(Pow(2, n, mod), mod - 2, mod);
    ans = ans * mu % mod;
    printf("%lld\n", (ans + mod) % mod);
}