#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mod = 998244353, G = 3;
const int maxn = 433333;

ll Pow(ll a, ll k, ll p) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = 1ll * ans * a % p;
        k >>= 1; a = 1ll * a * a % p;
    }
    return ans;
}

int rev[maxn];
void NTT(ll F[], int len, int inv) {
    int bit = 0;
    while((1<<bit) < len) ++bit;
    len = (1<<bit);
    for(int i = 1; i < len; ++i) 
        rev[i] = (rev[i>>1]>>1)|((i&1)<<(bit-1));
    for(int i = 0; i < len; ++i)
        if(i < rev[i]) swap(F[i], F[rev[i]]);
    ll w, wn, x, y;
    for(int h = 2, hh; h <= len; h <<= 1) {
        hh = h >> 1, wn = Pow(G, inv == 1 ? (mod - 1) / h : mod - 1 - (mod - 1) / h, mod);
        for(int i = 0; i < len; i += h) {
            w = 1;
            for(int j = i; j < i + hh; ++j) {
                x = F[j], y = F[j + hh] * w % mod;
                F[j] = (x + y) % mod, F[j + hh] = (x - y) % mod;
                w = w * wn % mod;
            }
        }
    }
    if(inv == -1) {
        ll invN = Pow(len, mod - 2, mod);
        for(int i = 0; i < len; ++i) F[i] = F[i] * invN % mod;
    } 
}