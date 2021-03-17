#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 998244353;
const ll inv2 = (mod+1)/2;
const ll base = 3ll * inv2 % mod;
ll Pow(ll a, ll k, ll p) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = ans * a % p;
        k >>= 1; a = a * a % p;
    }
    return ans;
}
int main() {
    int T;
    ll n;
    cin >> T;
    while(T--) {
        scanf("%lld", &n);
        ll ans = (2ll * Pow(base, n, mod) % mod + Pow(2ll, n, mod) + 1) % mod;
        printf("%lld\n", (ans+mod)%mod);
    }
}