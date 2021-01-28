#include<iostream>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7;

int Pow(int a, int k, int p) {
    int ans = 1;
    while(k) {
        if(k & 1) ans = 1ll * ans * a % p;
        k >>= 1; a = 1ll * a * a % p;
    }
    return ans;
}

// jie cheng
int fact[30];
int invfact[30];
void Fact(int n, int p) {
    fact[0] = 1;
    for(int i = 1; i <= n; i++) {
        fact[i] = 1ll * fact[i - 1] * i % p;
    }
    for(int i = 0; i <= n; i++) {
        invfact[i] = Pow(fact[i], p - 2, p);
    }
}

// zu he shu
int C(ll m, ll n, int p) {
    if(m < 0 || n < 0) return 0;
    int ans = 1;
    for(ll i = m; i > m - n; i--) {
        ans = 1ll * (i % p) * ans % p;
    }
    return 1ll * ans * invfact[n] % p;
}

ll l[30];
int main()
{
    Fact(20, mod);
    int n;
    ll s;
    cin >> n >> s;

    for(int i = 0; i < n; i++) {
        cin >> l[i];
    }

    ll ans = 0;
    // rong chi
    for(int i = 0; i < (1 << n); i++) {
        int cnt = 0;
        ll ss = s;
        for(int j = 0; j < n; j++) {
            if((1 << j) & i) {
                cnt++;
                ss -= l[j] + 1;
            }
        }
        if(ss < 0) continue;
        int sign = cnt % 2 ? -1 : 1;
        ans += 1ll * sign * C(ss + n - 1, n - 1, mod) % mod;
        ans %= mod;
    }
    cout << (ans < 0 ? ans + mod : ans) << endl;
}