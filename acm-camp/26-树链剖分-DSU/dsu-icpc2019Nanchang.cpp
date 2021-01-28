#include <iostream>
#include <queue>
#include <cstring>
#include <cstdio>
#include <unordered_map>
#include <algorithm>
using namespace std;
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define mp make_pair

typedef long long ll;

const int M = 200500;
const int N = 100500;

const ll inf = 0x3f3f3f3f;
int n, k;

const int maxn = N * 18;
int t[maxn], head[N], ch[maxn][2], tot = 0;
void Pushup(int k) {
    t[k] = (ch[k][0] ? t[ch[k][0]] : 0) + (ch[k][1] ? t[ch[k][1]] : 0); 
}
void add(int x, int v, int &k, int l, int r) {
    if(!k) k = ++tot, t[k] = 0;
    if(l == r) t[k] += v;
    else {
        int m = l + ((r - l) >> 1);
        if(x <= m)
            add(x, v, ch[k][0], l, m); 
        else
            add(x, v, ch[k][1], m + 1, r);
        Pushup(k);
    }
}
int query(int L, int R, int k, int l, int r) {
    if(!k) return 0;
    if(L <= l && r <= R)
        return t[k];
    else {
        int m = l + ((r - l) >> 1);
        int res = 0;
        if(L <= m) res += query(L, R, ch[k][0], l, m);
        if(R > m) res += query(L, R, ch[k][1], m + 1, r); // [m + 1, r] [L, R]
        return res;
    }
}

struct Edge {
    int from, to, pre;
} e[M];
int last[N];
int es = 0;

void ine(int a, int b) {
    es++;
    e[es].from = a; e[es].to = b;
    e[es].pre = last[a];
    last[a] = es;
}
inline void ine2(int a, int b) { ine(a, b); ine(b, a); }

#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)


// 树链剖分
int size[N], fa[N], dep[N], son[N], dfn[N], rk[N], post[N], clc;
int v[N];
void change(int x, int dad, int d) {
    dep[x] = d, size[x] = 1, fa[x] = dad, son[x] = 0;
    dfn[x] = ++clc; rk[clc] = x;
    int maxv = 0;
    reg(i, x) {
        int y = e[i].to;
        change(y, x, d + 1);
        size[x] += size[y];
        if(size[y] >= maxv) son[x] = y, maxv = size[y];
    }
    post[x] = clc;
}


ll ans = 0;
void dfs(int x, bool cl) {
    reg(i, x) {
        int y = e[i].to;
        if(y == son[x]) continue;
        dfs(y, 1);
    }
    if(son[x]) dfs(son[x], 0);
    reg(i, x) {
        int y = e[i].to;
        if(y == son[x]) continue;
        for(int j = dfn[y], u, h, val; j <= post[y]; ++j) {
            u = rk[j];
            h = 2 * dep[x] - dep[u] + k;
            val = 2 * v[x] - v[u];
            if(val < 0 || val > n || h <= 0) continue;
            if(h > n) h = n;
            ans += query(1, h, head[val], 1, n);
        }
        for(int j = dfn[y], u; j <= post[y]; ++j) {
            u = rk[j];
            add(dep[u], 1, head[v[u]], 1, n);
        }
    }
    add(dep[x], 1, head[v[x]], 1, n);
    if(cl) {
        for(int i = dfn[x], j; i <= post[x]; ++i) {
            j = rk[i];
            add(dep[j], -1, head[v[j]], 1, n);
        }
    }
}

int main() {
    cin >> n >> k;
    rep(i, 1, n) {
        scanf("%d", &v[i]);
    }
    int u;
    rep(i, 1, n - 1) {
        scanf("%d", &u);
        ine(u, i + 1);
    }
    change(1, 0, 1);
    dfs(1, 0);
    printf("%lld\n", 2 * ans);
}