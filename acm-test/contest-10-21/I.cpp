#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
const int maxn = 100050;
int a[maxn];

ll Pow(ll a, ll k, ll p) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = ans * a % p;
        k >>= 1; a = a * a % p;
    }
    return ans;
}

ll f[maxn];

ll C(ll n, ll m) {
    if(n < m) return 0;
    return f[n] * Pow(f[m], mod - 2, mod) % mod * Pow(f[n - m], mod - 2, mod) % mod;
}

struct state {
    int w[51];
} st;

struct cmp {
    bool operator()(const state& a, const state& b) const {
        for(int i = 1; i <= 50; ++i) {
            if(a.w[i] != b.w[i]) return false;
        }
        return true;
    }
};

struct _hash {
    size_t operator()(const state& st) const {
        size_t res = st.w[1];
        for(int i = 2; i <= 50; ++i) {
            res *= 19260817;
            res += st.w[i];
        }
        return res;
    }
};

unordered_map <state, ll, _hash, cmp> mp_st; 


ll dfs(int cur, int r) {
    if(cur >= 50) return f[r];
    if(r == 0) return 1;
    if(mp_st.count(st)) return mp_st[st];
    ll res = 0, kd;
    for(int i = 1; i <= cur; ++i) {
        if(st.w[i] == 0) continue;
        kd = st.w[i];
        --st.w[i];
        res = (res + 1ll * kd * dfs(cur + i, r - 1) % mod) % mod;
        ++st.w[i];
    }
    return mp_st[st] = res;
}
int main() {
    
    int n;
    cin >> n;
    f[0] = 1;
    for(ll i = 1; i <= n; ++i) {
        f[i] = f[i - 1] * i % mod;
    }
    for(int i = 0; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    for(int i = 1; i <= n; ++i) {
        ++st.w[a[i]];
    }
    if(a[0] == 0 && st.w[0] == n) {
        printf("%lld\n", (f[n] + mod) % mod);
    } else if(a[0] == 0 && st.w[0] < n) {
        printf("0\n");
    } else {
        ll ans = dfs(a[0], n - st.w[0]);
        ans = ans * C(n, st.w[0]) % mod * f[st.w[0]] % mod;
        printf("%lld\n", (ans + mod) % mod);
    }
}