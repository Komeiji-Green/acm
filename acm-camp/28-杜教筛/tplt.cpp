#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = (1 << 21); // n ^ (2/3)
ll sum_mu[maxn];
unordered_map<ll, ll> mp_mu;

bool isnt[maxn];
int prime[maxn];
int cnt = 0;

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

// f 的前缀和
ll S_mu(ll x) {
    if(x < maxn) return sum_mu[x];
    if(mp_mu.count(x)) return mp_mu[x];
    ll res = 1; // (f * g) 的 [1, x] 前缀和
    for(ll i = 2, j; i <= x; i = j + 1) {
        j = x / (x / i);
        res -= S_mu(x / i) * (j - i + 1); // sum_g[i, j]
    }
    return mp_mu[x] = res; // 若g(1)非1, 记得除掉
}

ll S_phi(ll x) {
    ll res = 0;
    for(ll i = 1, j; i <= x; i = j + 1) {
        j = x / (x / i);
        res += (S_mu(j) - S_mu(i - 1)) * (x / i) * (x / i);
    }
    return ((res - 1) >> 1) + 1;
}

int main() {
    Sieve(maxn - 1);
    sum_mu[0] = 0;
    for(int i = 1; i < maxn; ++i) {
        sum_mu[i] = sum_mu[i - 1] + mu[i];
    }
    int T;
    cin >> T;
    ll n;
    while(T--) {
        scanf("%lld", &n);
        ll ans1 = S_mu(n), ans2 = S_phi(n);
        printf("%lld %lld\n", ans2, ans1);
    }
}