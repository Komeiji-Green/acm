#include<bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
typedef long long ll;

const int N = 100010, M = 400500;
const ll mod = 1e9 + 7;
const ll inv2 = (mod+1)/2;
struct Edge {
    int to, pre;
    ll w;
} e[M];
int last[N], tot = 0;

void ine(int a, int b, ll w) {
    ++tot;
    e[tot].to = b; e[tot].w = w; e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b, ll w) { ine(a, b, w); ine(b, a, w); }

#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)

ll po[M];

struct pir {
    int u, v;
} pr[M];
int n, m;

int f[N];
int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }

void Kruskal() {
    for(int i = 1, u, v; i <= m; ++i) {
        u = pr[i].u, v = pr[i].v;
        int fu = find(u), fv = find(v);
        if(fu == fv) continue;
        f[fu] = fv;
        ine2(u, v, po[i]);
    }
}

int a[N];
ll su[N][2], siz[N][2], ans, cur;
ll sum[N][2], cnt[N][2];
void dfs(int x, int dad) {
    su[x][0]=su[x][1]=siz[x][0]=siz[x][1]=0;
    int sz = 0;
    reg(i, x) {
        int y = e[i].to; if(y == dad) continue;
        dfs(y, x);
    }
    reg(i, x) {
        int y = e[i].to; if(y == dad) continue;
        ll w = e[i].w; ++sz; 
        cnt[sz][0] = siz[y][0]; cnt[sz][1] = siz[y][1];
        for(int j = 0; j < 2; ++j) sum[sz][j] = (w * siz[y][j] % mod + su[y][j]) % mod;
    }
    for(int i = 1; i <= sz; ++i) 
        for(int j = 0; j < 2; ++j) {
            su[x][j] = (su[x][j] + sum[i][j]) % mod;
            siz[x][j] = (siz[x][j] + cnt[i][j]) % mod;
        }
    // upd siz
    cur = (su[x][0]*siz[x][1]%mod + su[x][1]*siz[x][0]%mod)%mod;
    for(int i = 1; i <= sz; ++i) {
        cur = (cur - sum[i][0]*cnt[i][1]%mod - sum[i][1]*cnt[i][0]%mod) % mod;
    }
    cur = cur*inv2%mod;
    cur = (cur + su[x][a[x]^1]) % mod;
    ans = (ans+cur)%mod;
    siz[x][a[x]]++;
}

int main() {
    const size_t nc = sizeof(su) + sizeof(siz) + sizeof(sum) + sizeof(cnt) + sizeof(a) + sizeof(f) + sizeof(pr) + sizeof(po) + sizeof(last) + sizeof(e);
    int T;
    cin >> T;
    po[0] = 1; for(int i = 1; i < M; ++i) po[i] = 2ll * po[i-1] % mod;
    while(T--) {
        scanf("%d %d", &n, &m);
        tot = 0;
        for(int i = 0; i <= n; ++i) last[i] = 0, f[i] = i;

        for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        for(int i = 1; i <= m; ++i) {
            scanf("%d %d", &pr[i].u, &pr[i].v);
        }
        Kruskal();
        ans = 0;
        dfs(1, 0);
        printf("%lld\n", (ans+mod)%mod);
    }
}