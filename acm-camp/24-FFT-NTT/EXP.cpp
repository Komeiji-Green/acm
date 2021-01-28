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
// g-清空 f-
void INV(ll g[], ll f[], int len) {
    memset(g, 0, sizeof(ll) * len); memset(df, 0, sizeof(ll)*(len<<1));
    g[0] = Pow(f[0], mod - 2, mod);
    for(int t = 1, cur; t < len; t <<= 1) {
        cur = (t<<2);
        //memset(df, 0, sizeof(ll)*cur);
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
    int sz = (len<<1);
    memset(ff, 0, sizeof(ll) * sz); memset(invf, 0, sizeof(ll) * sz); memset(gg, 0, sizeof(ll) * sz);
    for(int i = 1; i <= len; ++i) ff[i-1] = i * f[i] % mod;
    INV(invf, f, len);
    NTT(ff, len<<1, 1); NTT(invf, len<<1, 1);
    for(int i = 0; i < (len<<1); ++i)
        gg[i] = ff[i] * invf[i] % mod;
    NTT(gg, len<<1, -1);
    for(int i = 0; i < len - 1; ++i) lnf[i+1] = invx[i+1] * gg[i] % mod;
    lnf[0] = 0;
}

ll lng[maxn], dff[maxn];
void EXP(ll g[], ll f[], int len) {
    memset(g, 0, sizeof(ll) * (len<<1)); memset(dff, 0, sizeof(ll) * (len<<1));
    g[0] = 1;
    for(int t = 1, cur, m; t < len; t <<= 1) {
        cur = (t<<2); m = (t<<1);
        memcpy(dff, f, sizeof(ll) * m); //for(int i = m; i < cur; ++i) dff[i] = 0;
        LN(lng, g, m); for(int i = m; i < cur; ++i) lng[i] = 0;
        NTT(lng, cur, 1); NTT(g, cur, 1); NTT(dff, cur, 1);
        for(int i = 0; i < cur; ++i) g[i] = (g[i] * (1ll + dff[i] - lng[i]) % mod) % mod;
        NTT(g, cur, -1);
        for(int i = m; i < cur; ++i) g[i] = 0;
    }
}
// 以上的len必须是2的整数次幂！


ll a[maxn], b[maxn];

int main() {
    init();
    int T;
    cin >> T;
    while(T--) {
        memset(a, 0, sizeof(a)); memset(b, 0, sizeof(b));
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) scanf("%lld", &a[i]);
        int len = 1;
        while(len < n) len <<= 1;
        EXP(b, a, len);
        for(int i = 0; i < n; ++i) printf("%lld ", (b[i] + mod) % mod);
        cout << endl;
        LN(a, b, len);
        for(int i = 0; i < n; ++i) printf("%lld ", (a[i] + mod) % mod);
        cout << endl;
    }
}