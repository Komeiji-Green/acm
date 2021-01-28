#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int mod = 998244353, G = 3;

ll Pow(ll a, int k, int p) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = 1ll * ans * a % p;
        k >>= 1; a = 1ll * a * a % p;
    }
    return ans;
}
// 
void change(ll a[], int len) {
    for(int i = 1, j = len >> 1; i < len - 1; i++){
        if(i < j) swap(a[i], a[j]);
        int k = len >> 1;
        for(; j >= k; k >>= 1) j -= k;
        if(j < k) j += k;
    }
}
// rev == 1 : NTT rev == -1 : INTT
void NTT(ll a[], int len, int rev) {
    change(a, len);
    for(int h = 2; h <= len; h <<= 1){
        int hh = h >> 1, wn = Pow(G, rev == -1 ? mod - 1 - (mod - 1) / h : (mod - 1) / h, mod);
        for(int i = 0; i < len; i += h){
            ll w = 1;
            for(int j = i; j < i + hh; j++){
                int x = a[j], y = w * a[j + hh] % mod;
                a[j] = (x + y) % mod;
                a[j + hh] = (x - y) % mod;
                w = w * wn % mod;
            }
        }
    }
    if(rev == -1) {
        int inv = Pow(len, mod - 2, mod);
        for(int i = 0; i < len; i++) a[i] = a[i] * inv % mod;
    }
}

const int maxn = 433333;
ll f[maxn], g[maxn], h[maxn];
ll frac[maxn], invfrac[maxn];
int main() {
    int n;
    cin >> n;
    int len = 1;
    while(len <= n * 2) len <<= 1;
    frac[0] = invfrac[0] = 1;
    for(int i = 1; i <= n; i++) {
        frac[i] = frac[i - 1] * i % mod;
        invfrac[i] = Pow(frac[i], mod - 2, mod);
    }
    f[0] = invfrac[0];
    ll temp = 1;
    for(int i = 1; i <= n; i++) {
        temp *= -1;
        f[i] = temp * invfrac[i] % mod;
    }
    g[0] = invfrac[0] * 1;
    g[1] = invfrac[1] * (n + 1) % mod;
    for(int i = 2; i <= n; i++) {
        g[i] = invfrac[i] * (Pow(i, n + 1, mod) - 1) % mod * (Pow(i - 1, mod - 2, mod)) % mod;
    }
    for(int i = n + 1; i < len; i++)
        f[i] = g[i] = 0;
    NTT(f, len, 1); NTT(g, len, 1);
    for(int i = 0; i < len; i++) {
        h[i] = f[i] * g[i] % mod;
    }
    NTT(h, len, -1);
    ll pow2 = 1;
    ll sum = 0;
    for(int i = 0; i < len; i++) {
        sum = (sum + pow2 * frac[i] % mod * h[i] % mod) % mod; 
        pow2 = pow2 * 2 % mod;
    }
    sum = (sum + mod) % mod;
    printf("%lld\n", sum);

    /*printf("%d\n", len);
    for(int i = 0; i < len; i++) {
        printf("%lld ", h[i]);
    }*/
}