#include <iostream>
#include <cstdio>
#include <ctime>
using namespace std;
typedef long long ll;

const int maxn = 10000000 + 5;
bool isnt[maxn];
int prime[maxn];
int cnt = 0;

const ll mod = 20101009;

// 线性筛求积性函数
int mu[maxn];
void Sieve(int n) {
    isnt[1] = true;
    //phi[1] = 1;
    mu[1] = 1;
    cnt = 0;
    for(int i = 2; i <= n; i++) {
        if(!isnt[i]) {
            prime[++cnt] = i;
            //phi[i] = i - 1;
            mu[i] = -1;
            // d[i] = 2; q[i] = 1;
            // D[i] = i + 1; q[i] = 1;
        }
        for(int j = 1; j <= cnt; j++) {
            int x = i * prime[j];
            if(x > n) break;
            isnt[x] = 1;
            if(i % prime[j] == 0) {
                //phi[x] = phi[i] * prime[j];
                mu[x] = 0;
                // d[x] = d[i] / (q[i] + 1) * (q[i] + 2), q[x] = q[i] + 1;
                // D[x] = D[i] / (prime[j] ^ (q[i] + 1) - 1) * (prime[j] ^ (q[i] + 2) - 1), q[x] = q[i] + 1;
                break;
            } else {
                //phi[x] = phi[i] * (prime[j] - 1);
                mu[x] = -mu[i];
                // d[x] = 2 * d[i], q[x] = 1;
                // D[x] = (prime[j] + 1) * D[i], q[x] = 1;
            }
        }
    }
}

ll pre1(ll n) {
    return (n * (n + 1) / 2) % mod;
}
ll pre2[maxn];

ll func(ll a, ll b) {
    ll mm = min(a, b);
    ll ans = 0;
    for(ll i = 1, j; i <= mm; i = j + 1) {
        j = min(a / (a / i), b / (b / i));
        ans = (ans + (pre1(a / i) * pre1(b / i) % mod) * (pre2[j] - pre2[i - 1]) % mod) % mod;
    }
    return ans;
}
ll calc(ll n, ll m) {
    ll mm = min(n, m);
    ll ans = 0;
    for(ll i = 1, j; i <= mm; i = j + 1) {
        j = min(n / (n / i), m / (m / i));
        ans = (ans + (func(n / i, m / i) * (pre1(j) - pre1(i - 1)) % mod)) % mod; 
    }
    return ans;
}

int main() {
    Sieve(10000000);
    pre2[0] = 0;
    for(int i = 1; i <= 10000000; ++i) {
        pre2[i] = (pre2[i - 1] + 1ll * i * i * mu[i] % mod) % mod;
    }
    ll n, m;
    cin >> n >> m;
    printf("%lld\n", (calc(n, m) + mod) % mod);
}