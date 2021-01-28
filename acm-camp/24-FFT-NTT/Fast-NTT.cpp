#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 998244353, phi = mod - 1, G = 3;
const int maxn = 833333;

ll Pow(ll a, ll k, ll p) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = 1ll * ans * a % p;
        k >>= 1; a = 1ll * a * a % p;
    }
    return ans;
}

ll inv[maxn];
void init() {
    int mm = 1<<20;
    inv[0] = 0, inv[1] = 1;
    for(int i = 2; i <= mm && i < maxn; i++) inv[i] = inv[mod % i] * (mod - mod / i) % mod;
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

ll a[maxn], b[maxn], c[maxn], d[maxn], tmp[maxn];


// -n : 2的整数次幂
void getinv(ll *a, ll *b, int n) {
    if(n == 1) {
        b[0] = Pow(a[0], mod - 2, mod), b[1] = 0; return;
    }
    getinv(a, b, n >> 1);
    int k = (n<<1);
    for(int i = 0; i < n; ++i) tmp[i] = a[i], tmp[i + n] = 0, b[i + n] = 0;
    NTT(tmp, k, 1); NTT(b, k, 1);
    for(int i = 0; i < k; ++i) tmp[i] = b[i] * (2 - b[i] * tmp[i] % mod) % mod;
    NTT(tmp, k, -1);
    for(int i = 0; i < n; ++i) b[i] = tmp[i], b[i + n] = 0;
}

// b = ln(a), c = inv(a), tmp = d(a), 要预处理inv
void getln(ll *a, ll *b, ll *c, int n) {
    int k = (n << 1); getinv(a, c, n);
    for(int i = 0; i < n; ++i) tmp[i] = (i + 1) * a[i + 1] % mod, tmp[i + n] = 0;
    NTT(tmp, k, 1); NTT(c, k, 1);
    for(int i = 0; i < k; ++i) tmp[i] = tmp[i] * c[i] % mod;
    NTT(tmp, k, -1);
    for(int i = 1; i < n; ++i) b[i] = inv[i] * tmp[i-1] % mod, b[i + n] = 0; b[0] = 0; b[n] = 0;
}

//c = ln(b)
void getexp(ll *a, ll *b, ll *c, ll *d, int n) {
    if(n == 1) {
        b[0] = 1, b[1] = 0; return;
    }
    getexp(a, b, c, d, n >> 1);
    getln(b, c, d, n);
    for(int i = 0; i < n; ++i) tmp[i] = (a[i] - c[i]) % mod, tmp[i + n] = 0, b[i + n] = 0; ++tmp[0];
    int k = (n << 1); 
    NTT(tmp, k, 1); NTT(b, k, 1);
    for(int i = 0; i < k; ++i) tmp[i] = tmp[i] * b[i] % mod;
    NTT(tmp, k, -1);
    for(int i = 0; i < n; ++i) b[i] = tmp[i], b[i + n] = 0;
}

// -ln : ln(a)
void ksm(ll *a, ll *b, ll *c, ll *d, ll *ln, ll k, int n) {
    getln(a, ln, c, n);
    for(int i = 0; i < n; ++i) ln[i] = k * ln[i] % mod;
    getexp(ln, b, c, d, n);
}

// 以上函数，a为输出，且只需保证a在前n项正确，n为2的整数次幂即可。
// 需要init

char s[maxn];
ll ln[maxn];
int main() {
    init();
    int n, len; ll k = 0;
    cin >> n;
    scanf("%s", s);
    int wei = strlen(s);
    for(int i = 0; s[i]; ++i) {
        --wei;
        k = (k + (s[i] - '0') * Pow(10, wei % phi, mod) % mod) % mod;
    }
    for(int i = 0; i < n; ++i) scanf("%lld", &a[i]);
    for(len = 1; len < n; len <<= 1);
    ksm(a, b, c, d, ln, k, len);
    for(int i = 0; i < n; ++i) printf("%lld ", (b[i] + mod) % mod);
    cout << endl;
}