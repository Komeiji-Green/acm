#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 19260817;
const ll M = 1000000;
const int maxn = 1000000 + 5;
bool isnt[maxn];
int prime[maxn];
int cnt = 0;

ll Pow(ll a, ll k) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = ans * a % mod;
        k >>= 1; a = a * a % mod;
    }
    return ans;
}

// 线性筛法 [1, n] 内素数
void Prime(int n) {
    isnt[1] = true;
    cnt = 0;
    for (int i = 2; i <= n; i++) {
        if (!isnt[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt; j++) {
            if (1ll * i * prime[j] > n) break;
            isnt[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}
int calc(int x, int p) {
    int res = 0;
    while(x % p == 0) {
        ++res; x /= p;
    }
    return res;
}

ll G[maxn], fac[maxn];
ll Sum[maxn], Cnt[maxn];
void add(int idx, ll v) {
    for(int i = idx; i <= 30; i += i & (-i)) {
        Sum[i] += v; Cnt[i]++;
    }
}
void query(int idx, ll &_sum, ll &_cnt) {
    _sum = _cnt = 0;
    for(int i = idx; i; i -= i & (-i)) {
        _sum += Sum[i]; _cnt += Cnt[i];
    }
}
void add1(int idx, ll v) {
    for(int i = idx; i <= M; i += i & (-i)) {
        G[i] = G[i] * v % mod;
    }
}
ll query1(int idx) {
    ll res = 1;
    for(int i = idx; i; i -= i & (-i)) {
        res = res * G[i] % mod;
    }
    return res;
}
void init() {
    for(int i = 0; i <= 30; ++i) Sum[i] = Cnt[i] = 0;
}

ll f[maxn];
int main() {

    Prime(M);
    f[0] = 1;
    for(ll i = 1; i <= M; ++i) f[i] = i * f[i - 1] % mod;
    for(int i = 1; i <= M; ++i) G[i] = 1;
    for(int i = 1; i <= cnt; ++i) {
        int p = prime[i];
        fac[0] = 0;
        init();
        //printf("%d: ", p);
        for(int x = p, j = 1; x <= M; x += p, ++j) {
            int l = calc(x, p);
            ll S, C; query(l, S, C);
            fac[x] = 2 * ((j - 1 - C) * l + S) + l;
            add1(x, Pow(p, fac[x]));
            //printf("(%d, %lld) ", x, fac[x]);
            //G[x] = G[x] * Pow(p, fac[x]) % mod;
            add(l, l);
        }
        //printf("\n");
    }
    int T, n;
    cin >> T;
    while(T--) {
        scanf("%d", &n);
        ll g = query1(n);
        //printf("f: %lld, G: %lld\n", f[n], g);
        ll res = Pow(f[n], n) * Pow(g, mod - 2) % mod;
        res = res * res % mod;
        printf("%lld\n", (res + mod) % mod);
    }

}