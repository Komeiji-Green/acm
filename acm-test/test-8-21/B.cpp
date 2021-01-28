#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
typedef long long ll;
const int N = 233333;
const ll mod = 1000000007;


// 快速幂 计算 a^k % p
// a <= 1e9, k <= 1e9
ll Pow(ll a, ll k, ll p) 
{
    ll ans = 1;
    while(k) {
        if(k & 1) ans = 1ll * ans * a % p;
        k >>= 1; a = 1ll * a * a % p;
    }
    return ans;
}

// 单乘法逆元 (mod p)
ll Inv(ll a, ll p)
{
    return Pow(a, p - 2, p);
}

ll inv[N];

// 求模p的乘法逆元 [1, p - 1]
void InvList(ll p, int n)
{
    inv[0] = 0;
    inv[1] = 1;
    for(int i = 2; i < n; i++) {
        inv[i] = 1ll * inv[p % i] * (p - p / i) % p;
    }
}

ll pow_2[N];

void PowList(ll p, int n) {
    pow_2[0] = 1;
    for(int i = 1; i < n; i++) {
        pow_2[i] = 2 * pow_2[i - 1] % p;
    }
}

// pre(n, k) = pre(n - 1, k - 1) + pre(n - 1, k)
// pre(n, k) = 2 * pre(n - 1, k - 1) + C(n - 1, k)
// 至少能玩i次的概率 = P[i] + P[i + 1] + ... + P[n]
//                  = pre(i, k), 其中k为使得 t1 + ... + ti + k <= T 成立的最大数 

ll C[N], pre[N];
ll T, t[N];

ll DP(ll n) {
    InvList(mod, n + 1);
    PowList(mod, n + 1);
    
    ll r = T, ans = 0;
    pre[0] = 1;
    C[0] = 1;
    for(ll i = 1; i <= n; i++) {
        r -= t[i];
        if(r >= i) {
            pre[i] = 2 * pre[i - 1] % mod;
            C[i] = 1;
            ans += pre[i] % mod * pow_2[n - i] % mod;
            ans %= mod;
            //printf("%lld: k:%lld, C:%lld, pre:%lld\n", i, i, C[i], pre[i]);
        } else if (r >= 0) {
            ll k = min(r + t[i], i - 1);
            while(k > r) {
                C[k - 1] = C[k] * k % mod * inv[i - k] % mod;
                pre[k - 1] = (pre[k] - C[k]) % mod;
                k--;
            }
            pre[k] = (2 * pre[k] - C[k]) % mod;
            C[k] = C[k] * i % mod * inv[i - k] % mod;
            ans += pre[k] % mod * pow_2[n - i] % mod;
            ans %= mod;

            //printf("%lld: k:%lld, C:%lld, pre:%lld\n", i, k, C[k], pre[k]);
        } else {
            break;
        }
    }
    ans = ans * Inv(pow_2[n], mod) % mod;
    return (ans + mod) % mod;
}

int main()
{
    ll n;
    cin >> n >> T;
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &t[i]);
    }
    cout << DP(n) << endl;
}