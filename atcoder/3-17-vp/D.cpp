#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 233333;
const ll mod = 998244353;

ll Pow(ll a, ll k, ll p) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = ans * a % p;
        k >>= 1; a = a * a % p;
    }
    return ans;
}

int cnt[26];
char s[N];

ll sum[N];
int main() {
    ll n, m, k, ans = 0;;
    cin >> n >> m >> k;
    for(ll i = 1; i <= k; ++i)
        sum[i] = Pow(i, m, mod);
    for(ll i = 2; i <= k; ++i)
        sum[i] = (sum[i] + (sum[i-1])) % mod;
    if(n == 1 && m == 1) {
        ans = k;
    } else if(n == 1) {
        ans = Pow(k, m, mod);
    } else if(m == 1) {
        ans = Pow(k, n, mod);
    } else { 
        for(ll i = 1; i <= k; ++i) {
            ans = (ans + (Pow(i, n, mod) - Pow(i-1, n, mod)) * Pow(k-i+1, m, mod) % mod) % mod; 
        }
    }
    cout << (ans+mod)%mod << endl;
}