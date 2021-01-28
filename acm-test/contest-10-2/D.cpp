#include<iostream>
#include<cstdio>
#include<algorithm> 
#include<cstring>
using namespace std;

typedef long long ll;

// 快速幂 计算 a^k % p
ll Pow(ll a, ll k, ll p) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = 1ll * ans * a % p;
        k >>= 1; a = 1ll * a * a % p;
    }
    return ans;
}

const ll mod = 59964251;
const ll phi = 59870352;
const ll pphi = 19768576;

const int maxn = 100000 + 500;

bool isnt[maxn];
int prime[maxn];
int cnt = 0;

// 线性筛法 [1, n] 内素数
void Prime(int n)
{
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
int mu[maxn];
void Phi(int n) {
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

ll f[maxn], g[maxn], D[maxn];




int main() {
    char str[100000 + 500];
    ll n, m, d, k;
    int T;
    cin >> T;
    Phi(100000);
    while(T--) {
        scanf("%s%lld%lld%lld", str, &m, &d, &k);
        int len = strlen(str);
        n = 0;
        for(int i = 0; i < len; ++i) {
            //n % phi
            n = (n + ((str[i] - '0') * Pow(10, len - i - 1, phi)) % phi) % phi;
        }
        n = (n + phi) % phi + phi;

        D[0] = 0;
        for(int i = 1; i <= m; ++i) {
            D[i] = (D[i-1] + Pow(i, k, mod)) % mod;
        }
        for(ll i = 1; i <= m; ++i) {
            g[i] = Pow(Pow(i, k, mod) * D[m / i] % mod, n, mod);
        }
        ll ans = 0;
        for(ll j = 1, i = d; i <= m; i += d, j++) {
            ans = (ans + g[i] * mu[j] % mod) % mod;
        }
        printf("%lld\n", (ans + mod) % mod);

        /*for(int i = 1; i <= m; ++i) {
            printf("g[%d]: %lld\n", i, g[i]);
        */

    }
}
