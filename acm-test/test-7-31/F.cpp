#include<iostream>
#include<string>
using namespace std;
typedef long long ll;
const int MOD = (1e9 + 9);
const int maxn = 1e5 + 5;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

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


int sign[maxn];
int main()
{
    int n, a, b, k;
    string s;
    cin >> n >> a >> b >> k;
    cin >> s;
    for(int i = 0; i < k; i++) {
        sign[i] = s[i] == '+' ? 1 : -1;
    }

    ll ans = 0;
    ll inva = Inv(a, MOD);
    ll n1 = (n + 1) / k;
    ll q1 = Pow(1ll * inva * b % MOD, k, MOD);

    for(int i = 0; i < k; i++) {
        ll a1 = 1ll * Pow(a, n - i, MOD) * Pow(b, i, MOD) % MOD;
        if((q1 - 1) % MOD == 0) {
            ans += 1ll * sign[i] * n1 * a1 % MOD;
            ans %= MOD;
        } else {
            ans += 1ll * sign[i] * (1ll * a1 * (Pow(q1, n1, MOD) - 1) % MOD) * (Inv(q1 - 1, MOD)) % MOD;
            ans %= MOD;
        }
    }
    cout << (ans < 0 ? MOD + ans : ans) << endl;
}