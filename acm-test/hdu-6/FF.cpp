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
ll cnt[N][2], sum[2], ans, c0, c1, cur;
void dfs(int x, int dad) {
    cnt[x][0] = cnt[x][1] = 0;
    cnt[x][a[x]] = 1;
    for(int i = last[x], y; i; i = e[i].pre) {
        y = e[i].to; if(y == dad) continue;
        dfs(y, x);
        for(int j = 0; j < 2; ++j)
            cnt[x][j] = (cnt[x][j] + cnt[y][j]) % mod;
    }
    for(int i = last[x], y; i; i = e[i].pre) {
        y = e[i].to; if(y == dad) continue;
        ll w = e[i].w;
        c0 = (sum[0] - cnt[y][0]) % mod;
        c1 = (sum[1] - cnt[y][1]) % mod;
        cur = c0*cnt[y][1]%mod + c1*cnt[y][0]%mod;
        ans = (ans + cur*w%mod) % mod;
        //ans = (ans + c0*cnt[y][1]%mod + c1*cnt[y][0]%mod) % mod;
    }
}

int main() {
    //const size_t nc = sizeof(su) + sizeof(siz) + sizeof(sum) + sizeof(cnt) + sizeof(a) + sizeof(f) + sizeof(pr) + sizeof(po) + sizeof(last) + sizeof(e);
    int T;
    cin >> T;
    po[0] = 1; for(int i = 1; i < M; ++i) po[i] = 2ll * po[i-1] % mod;
    while(T--) {
        scanf("%d %d", &n, &m);
        tot = 0;
        for(int i = 0; i <= n; ++i) last[i] = 0, f[i] = i;
        sum[0]=sum[1] = 0;
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            sum[a[i]]++;
        }
        for(int i = 1; i <= m; ++i) {
            scanf("%d %d", &pr[i].u, &pr[i].v);
        }
        Kruskal();
        ans = 0;
        dfs(1, 0);
        printf("%lld\n", (ans+mod)%mod);
    }
}