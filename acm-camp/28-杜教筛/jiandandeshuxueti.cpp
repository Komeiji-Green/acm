#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll mod;

const int maxn = 10000005;
bool isnt[maxn];
int prime[maxn];
int cnt = 0;

// 线性筛求积性函数
ll phi[maxn], sum_phi[maxn];
map<ll, ll> mp_phi;
void Sieve(int n) {
    isnt[1] = true;
    phi[1] = 1;
    //mu[1] = 1;
    cnt = 0;
    for(int i = 2; i <= n; i++) {
        if(!isnt[i]) {
            prime[++cnt] = i;
            phi[i] = i - 1; //mu[i] = -1;
            // d[i] = 2; q[i] = 1;
            // D[i] = i + 1; q[i] = 1;
        }
        for(int j = 1; j <= cnt; j++) {
            int x = i * prime[j];
            if(x > n) break;
            isnt[x] = 1;
            if(i % prime[j] == 0) {
                phi[x] = phi[i] * prime[j]; // mu[x] = 0;
                // d[x] = d[i] / (q[i] + 1) * (q[i] + 2), q[x] = q[i] + 1;
                // D[x] = D[i] / (prime[j] ^ (q[i] + 1) - 1) * (prime[j] ^ (q[i] + 2) - 1), q[x] = q[i] + 1;
                break;
            } else {
                phi[x] = phi[i] * (prime[j] - 1); // mu[x] = -mu[i]
                // d[x] = 2 * d[i], q[x] = 1;
                // D[x] = (prime[j] + 1) * D[i], q[x] = 1;
            }
        }
    }
}

ll pre(ll x) {
    return (x & 1) ? (((x + 1) / 2) % mod) * (x % mod) % mod : ((x / 2) % mod) * ((x + 1) % mod) % mod;
}

ll pre2(ll x) {
    ll a = x, b = x + 1, c = 2 * x + 1;
    if(x % 2 == 0) a /= 2;
    else b /= 2;
    if(x % 3 == 0) a /= 3;
    else if(b % 3 == 0) b /= 3;
    else c /= 3;
    a %= mod; b %= mod; c %= mod;
    return ((a * b) % mod) * c % mod;
}

inline ll sqr(ll x) { return x * x % mod; }
ll S_phi(ll x) {
    if(x < maxn) return sum_phi[x];
    if(mp_phi.count(x)) return mp_phi[x];
    ll res = sqr(pre(x));
    for(ll i = 2, j; i <= x; i = j + 1) {
        j = x / (x / i);
        res = (res - S_phi(x / i) * (pre2(j) - pre2(i - 1)) % mod) % mod;
    }
    return mp_phi[x] = res;
}
int main() {
    ll n;
    cin >> mod >> n;
    Sieve(maxn - 1);
    sum_phi[0] = 0;
    for(int i = 1; i < maxn; ++i) {
        sum_phi[i] = (sum_phi[i - 1] + 1ll * (1ll * i * i % mod) * phi[i] % mod) % mod;
    }
    ll ans = 0;
    for(ll i = 1, j; i <= n; i = j + 1) {
        j = n / (n / i);
        ans = (ans + ((S_phi(j) - S_phi(i - 1)) % mod) * sqr(pre(n / i)) % mod) % mod;
    }
    printf("%lld\n", (ans + mod) % mod);
}