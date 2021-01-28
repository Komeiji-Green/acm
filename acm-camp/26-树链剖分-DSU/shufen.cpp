#include <iostream>
#include <queue>
#include <cstring>
#include <cstdio>
using namespace std;
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define mp make_pair

typedef long long ll;

const int M = 566666;
const int N = 233333;

int n;

ll a[N], t[N<<2], lazy[N<<2], mod;
void Pushup(int k) {
    t[k] = (t[k<<1] + t[k<<1|1]) % mod;
}
void marking(int k, int len, ll lz) {
    lazy[k] = (lazy[k] + lz) % mod;
    t[k] = (t[k] + lz * 1ll * len % mod) % mod;
}
void Pushdown(int k, int l, int r) {
    if(lazy[k]) {
        int m = l + ((r - l) >> 1);
        marking(k<<1, m - l + 1, lazy[k]);
        marking(k<<1|1, r - m, lazy[k]);
        lazy[k] = 0;
    }
}
void build(int k, int l, int r) {
    if(l == r) t[k] = a[l];
    else {
        int m = l + ((r - l) >> 1);
        build(k<<1, l, m);
        build(k<<1|1, m + 1, r);
        Pushup(k);
    }
}
// 查询区间，结点下标及结点区间
ll query(int L, int R, int k, int l, int r) {
    if(l >= L && r <= R)
        return t[k];
    else {
        int m = l + ((r - l) >> 1);
        Pushdown(k, l, r);
        ll ans = 0;
        if(L <= m) 
            ans = (ans + query(L, R, k << 1, l, m)) % mod;
        if(R > m) 
            ans = (ans + query(L, R, k << 1 | 1, m + 1, r)) % mod; // [m + 1, r] [L, R]
        return ans;
    }
}
// 区间更新
void update(int L, int R, ll v, int k, int l, int r) {
    if(L <= l && r <= R) {
        marking(k, r - l + 1, v);
    } else {
        int m = l + ((r - l) >> 1);
        Pushdown(k, l, r);
        if(L <= m)
            update(L, R, v, k << 1, l, m);
        if(R > m)
            update(L, R, v, k << 1 | 1, m + 1, r);
        Pushup(k);
    }
}

struct Edge {
    int from, to, pre;
    ll w;
} e[M];
int last[N];
int tot = 0;

void ine(int a, int b, ll w) {
    tot++;
    e[tot].from = a; e[tot].to = b; e[tot].w = w;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b, ll w) { ine(a, b, w); ine(b, a, w); }

#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)


// 树链剖分
int size[N], fa[N], dep[N], son[N], dfn[N], post[N], rk[N], top[N], clc;
void change(int x, int dad, int d) {
    dep[x] = d, size[x] = 1, fa[x] = dad, son[x] = 0;
    int maxv = 0;
    reg(i, x) {
        int y = e[i].to;
        if(y == dad) continue;
        change(y, x, d + 1);
        size[x] += size[y];
        if(size[y] >= maxv) son[x] = y, maxv = size[y];
    }
}

void link(int x, int dad, int ttop) {
    dfn[x] = ++clc;
    rk[clc] = x;
    top[x] = ttop;
    if(son[x]) {
        link(son[x], x, ttop);
    }
    reg(i, x) {
        int y = e[i].to;
        if(y == dad || y == son[x]) continue;
        link(y, x, y);
    }
    post[x] = clc;
}

int lca(int x, int y) {
    int fx = top[x], fy = top[y];
    while(fx != fy) {
        if(dep[fx] < dep[fy]) swap(x, y), swap(fx, fy);
        x = fa[fx]; fx = top[x];
    }
    return dep[x] < dep[y] ? x : y;
}

// 子树加
void add_tree(int x, ll v) {
    update(dfn[x], post[x], v, 1, 1, n);
}
ll sum_tree(int x) {
    return query(dfn[x], post[x], 1, 1, n);
}

void add_road(int x, int y, ll v) {
    int fx = top[x], fy = top[y];
    while(fx != fy) {
        if(dep[fx] < dep[fy]) swap(x, y), swap(fx, fy);
        update(dfn[fx], dfn[x], v, 1, 1, n);
        x = fa[fx], fx = top[x];
    }
    if(dep[x] >= dep[y]) swap(x, y);
    update(dfn[x], dfn[y], v, 1, 1, n);
}
ll sum_road(int x, int y) {
    int fx = top[x], fy = top[y];
    ll sum = 0;
    while(fx != fy) {
        if(dep[fx] < dep[fy]) swap(x, y), swap(fx, fy);
        sum = (sum + query(dfn[fx], dfn[x], 1, 1, n)) % mod;
        x = fa[fx], fx = top[x];
    }
    if(dep[x] >= dep[y]) swap(x, y);
    sum = (sum + query(dfn[x], dfn[y], 1, 1, n));
    return sum;
}

// 洛谷LCA模板
/*
int main() {
    int m, s, u, v;
    cin >> n >> m >> s;
    for(int i = 1; i < n; ++i) {
        scanf("%d %d", &u, &v);
        ine2(u, v, 0);
    }
    change(s, 0, 1);
    link(s, 0, s);
    while(m--) {
        scanf("%d %d", &u, &v);
        printf("%d\n", lca(u, v));
    }
}*/

// 洛谷数分模板
ll val[N];
int main() {
    int m, s;
    cin >> n >> m >> s >> mod;
    for(int i = 1; i <= n; ++i) {
        scanf("%lld", &val[i]);
    }
    int u, v, op; ll lz;
    for(int i = 1; i < n; ++i) {
        scanf("%d %d", &u, &v);
        ine2(u, v, 0);
    }
    change(s, 0, 1);
    link(s, 0, s);
    for(int i = 1; i <= n; ++i) {
        a[i] = val[rk[i]];
    }
    build(1, 1, n);
    while(m--) {
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d %d %lld", &u, &v, &lz);
            add_road(u, v, lz);
        } else if(op == 2) {
            scanf("%d %d", &u, &v);
            printf("%lld\n", (sum_road(u, v) + mod) % mod);
        } else if(op == 3) {
            scanf("%d %lld", &u, &lz);
            add_tree(u, lz);
        } else if(op == 4) {
            scanf("%d", &u);
            printf("%lld\n", (sum_tree(u) + mod) % mod);
        }
        /*for(int i = 1; i <= n; ++i) {
            printf("%lld ", query(dfn[i], dfn[i], 1, 1, n));
        }
        printf("\n");*/
    }
} 