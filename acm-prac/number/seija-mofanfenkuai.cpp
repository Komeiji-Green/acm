#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1000500;
bool isnt[maxn];
int prime[maxn];
int cnt = 0;

const ll mod = 19260817;

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

ll S(ll n) {
    return (n * (n + 1) / 2) % mod;
}
ll G(ll n) {
    ll res = 0, x;
    for(ll d = 1; d <= n; ++d) {
        x = S(n / d);
        x = x * x % mod;
        res = (res + x) % mod;
    }
    return res;
}

int main() {
    int T;
    cin >> T;
    ll n;
    Sieve(1000000);
    while(T--) {
        scanf("%lld", &n);
        ll res = 0, x;
        for(ll i = 1; i <= n; ++i) {
            x = mu[i] * i * i % mod;
            x = x * G(n / i) % mod;
            res = (res + x) % mod;
        }
        printf("%lld\n", (res + mod) % mod);
    }
}