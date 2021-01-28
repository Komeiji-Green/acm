#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 4000551 + 5;
bool isnt[maxn];
int prime[maxn];
int cnt = 0;

// 线性筛法 [1, n] 内素数
void Prime(int n) {
    isnt[1] = true;
    cnt = 0;
    for (int i = 2; i <= n; i++) {
        if (!isnt[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > n) break;
            isnt[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

// 线性筛求积性函数
int phi[maxn];
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
                phi[x] = phi[i] * (prime[j] - 1); // mu[x] = -mu[i];
                // d[x] = 2 * d[i], q[x] = 1;
                // D[x] = (prime[j] + 1) * D[i], q[x] = 1;
            }
        }
    }
}
ll gcd(ll a, ll b) { return a == 0 ? b : gcd(b % a, a); }
/*
ll calc(ll n) {
    ll i = 1, res = 0;
    for(i = 1; i * i < n; ++i) {
        if(n % i) continue;
        res += i * phi[n / i];
        res += (n / i) * phi[i];
    }
    if(i * i == n) res += i * phi[i];
    return res;
}
*/

ll g[maxn], sum[maxn];
int main() {
    Sieve(4000051);
    const ll N = 4000000;
    //ll n;
    //cin >> n;
    ll ans = 0;
    /*for(ll i = 1; i <= n; ++i) {
        ans += calc(i);
    }*/
    
    // youhua Dirichlet juanji
    for(ll i = 1; i <= N; ++i) {
        for(ll j = 1, x; (x = j * i) <= N; ++j) {
            g[x] += i * phi[j];
        }
    }
    for(ll i = 1; i <= N; ++i) g[i] -= i;
    sum[0] = 0;
    for(int i = 1; i <= N; ++i) sum[i] = sum[i-1] + g[i];
    ll xx;
    while(scanf("%lld", &xx) != EOF && xx) {
        printf("%lld\n", sum[xx]);
    }
}