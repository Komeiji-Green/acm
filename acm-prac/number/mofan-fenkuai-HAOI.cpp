#include<bits/stdc++.h>
#include<iostream>
using namespace std;
typedef long long ll;

const int maxn = 100000 + 5;
bool isnt[maxn];
int prime[maxn];
int cnt = 0;

// 线性筛求积性函数
int mu[maxn];
void Sieve(int n) {
    isnt[1] = true;
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

ll pre[maxn];
ll func(ll m, ll n, ll k) {
    m = m / k, n = n / k;
    ll mm = min(m, n), ans = 0;
    for(ll i = 1, j; i <= mm; i = j + 1) {
        j = min(m / (m / i), n / (n / i));
        ans += (m / i) * (n / i) * (pre[j] - pre[i - 1]);
    }
    //printf("%lld %lld %lld: %lld\n", m, n, k, ans);
    return ans;
}

int main() {
    Sieve(100000);
    pre[0] = 0;
    for(int i = 1; i <= 100000; ++i) {
        pre[i] = pre[i - 1] + mu[i];
    }
    //for(int i = 1; i <= 10; ++i) printf("%d\n", mu[i]);
    int T;
    cin >> T;
    ll a, b, c, d, k;
    while(T--) {
        scanf("%lld %lld %lld %lld %lld", &a, &b, &c ,&d ,&k);
        ll ans = func(b, d, k) - func(a - 1, d, k) - func(b, c - 1, k) + func(a - 1, c - 1, k);
        printf("%lld\n", ans);
    }
}

const ll mod = 2147493647ll*2147493647ll;
int main() {

    ll mm = min(m, n);
    for(ll i = 1, j; i <= mm; i = j + 1) {
        j = min(m / (m / i), n / (n / i));
        ans += (m / i) * (n / i) * (pre[j] - pre[i - 1]);
    }

}