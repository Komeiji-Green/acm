#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 998244353, phi = mod - 1, G = 3;
const int maxn = 833333;

inline ll Pow(ll x, ll k, ll p) {
    ll ans=1;
    for(;k;k>>=1,x=x*x%p)if(k&1)ans=ans*x%p;
    return ans;
}

ll inv[maxn];
void init() {
    int mm = 1<<20;
    inv[0] = 0, inv[1] = 1;
    for(int i = 2; i <= mm && i < maxn; i++) inv[i] = inv[mod % i] * (mod - mod / i) % mod;
}

inline void NTT(ll *a, ll k, ll f) {  
    for (int i=0,j=0;i<k;i++){
        if (i>j)swap(a[i],a[j]);
        for (int l=k>>1;(j^=l)<l;l>>=1);
    }
    for (int i=1;i<k;i<<=1){
		ll w=Pow(G,(f*(mod-1)/(i<<1)+mod-1)%(mod-1),mod);
        for (int j=0;j<k;j+=(i<<1)){
			ll e=1;
            for (register int k=0;k<i;++k,e=e*w%mod){
				ll x,y;
                x=a[j+k];y=a[j+k+i]*e%mod;
                a[j+k]=(x+y)%mod;a[j+k+i]=(x-y+mod)%mod;        
            }
        }
    }
    if(f==-1){
		ll _inv=Pow(k,mod-2,mod);
		for (int i=0;i<k;++i)a[i]=a[i]*_inv%mod;
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

// b = ln(a), c = inv(a), tmp = d(a), yuchuli: inv
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

ll base[maxn], dd[maxn];

int main() {
    init();
    int T, n, L, cas = 0;
    cin >> T;
    ll m;
    while(T--) {
        ++cas;
        scanf("%d %d %lld", &n, &L, &m);
        int len;for(len = 1; len < n; len <<= 1);

        memset(a, 0, sizeof(ll) * len);
        memset(base, 0, sizeof(ll) * len);

        for(int i = n - 1; i >= 0; --i) scanf("%lld", &a[i]);
        for(int i = 0; i < L; ++i) base[i] = 1;

        ksm(base, dd, b, c, d, m, len);

        int sz = (len<<1);
        NTT(dd, sz, 1); NTT(a, sz, 1);
        for(int i = 0; i < sz; ++i) tmp[i] = dd[i] * a[i] % mod;
        NTT(tmp, sz, -1);

        printf("Case %d: ", cas);
        for(int i = n - 1; i >= 0; --i) {
            printf("%lld ", (tmp[i] + mod) % mod);
        }
        printf("\n");
    }
}