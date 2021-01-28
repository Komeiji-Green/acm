#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 998244353, G = 3;
const int maxn = 8333333;

ll Pow(ll a, ll k, ll p) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = 1ll * ans * a % p;
        k >>= 1; a = 1ll * a * a % p;
    }
    return ans;
}

ll invx[maxn];
void init() {
    int mm = 1<<22;
    invx[0] = 0, invx[1] = 1;
    for(int i = 2; i <= mm; i++) invx[i] = invx[mod % i] * (mod - mod / i) % mod;
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

// inverse
ll df[maxn];
void INV(ll f[], ll g[], int len) {
    g[0] = Pow(f[0], mod - 2, mod);
    for(int t = 1, cur; t < len; t <<= 1) {
        cur = (t<<2);
        memcpy(df, f, (t<<1)*sizeof(ll));
        NTT(df, cur, 1); NTT(g, cur, 1);
        for(int i = 0; i < cur; ++i)
            g[i] = (-(g[i] * g[i] % mod) * df[i] % mod + 2ll * g[i] % mod) % mod;
        NTT(g, cur, -1);
        for(int i = (t<<1); i < cur; ++i) g[i] = 0;
    }
}

ll ff[maxn], invf[maxn], gg[maxn];
void LN(ll lnf[], ll f[], int len) {
    for(int i = 1; i < len; ++i) ff[i-1] = i * f[i] % mod;
    INV(f, invf, len);
    NTT(ff, len<<1, 1); NTT(invf, len<<1, 1);
    for(int i = 0; i < (len<<1); ++i)
        gg[i] = ff[i] * invf[i] % mod;
    NTT(gg, len<<1, -1);
    for(int i = 0; i < len; ++i) lnf[i+1] = invx[i+1] * gg[i] % mod;
}

ll f[maxn], g[maxn];
int main() {
    init();
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i) scanf("%lld", &f[i]);
    int len = 1;
    while(len < n) len <<= 1;
    LN(g, f, len);
    for(int i = 0; i < n; ++i) printf("%lld ", (g[i] + mod) % mod); cout << endl;
}