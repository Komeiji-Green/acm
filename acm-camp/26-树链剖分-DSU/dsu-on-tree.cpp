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

const int M = 1000500;
const int N = 500500;
const int inf = -1e9;

int n;

struct Edge {
    int from, to, pre;
    char w;
} e[M];
int last[N];
int tot = 0;

void ine(int a, int b, char w) {
    tot++;
    e[tot].from = a; e[tot].to = b; e[tot].w = w;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b, char w) { ine(a, b, w); ine(b, a, w); }

#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)


// 树链剖分
int size[N], fa[N], dep[N], son[N], dfn[N], rk[N], post[N], clc;
void change(int x, int dad, int d) {
    dep[x] = d, size[x] = 1, fa[x] = dad, son[x] = 0;
    dfn[x] = ++clc; rk[clc] = x;
    int maxv = 0;
    reg(i, x) {
        int y = e[i].to;
        if(y == dad) continue;
        change(y, x, d + 1);
        size[x] += size[y];
        if(size[y] >= maxv) son[x] = y, maxv = size[y];
    }
    post[x] = clc;
}


int v[N], ans[N], bag[1<<22];

void pre(int x, int dad, int tag) {
    v[x] = tag;
    reg(i, x) {
        int y = e[i].to;
        if(y == dad) continue;
        char c = e[i].w;
        pre(y, x, tag ^ (1 << (c - 'a')));
    }
}

void getchk(int x) {
    for(int j = dfn[x], u; j <= post[x]; ++j) {
        u = rk[j];
        bag[v[u]] = max(bag[v[u]], dep[u]);
    }
}

int find_max(int tag) {
    int maxv = inf, t;
    maxv = max(maxv, bag[tag]);
    rep(i, 0, 21) {
        t = (tag ^ (1<<i));
        maxv = max(maxv, bag[t]);
    }
    return maxv;
}

int getans(int x) {
    int maxv = inf;
    for(int j = dfn[x], u; j <= post[x]; ++j) {
        u = rk[j];
        maxv = max(maxv, dep[u] + find_max(v[u]));
    }
    return maxv;
}

int dfs(int x, int dad) {
    int maxv = 0;
    reg(i, x) {
        int y = e[i].to;
        if(y == dad || y == son[x]) continue;
        maxv = max(dfs(y, x), maxv);
        for(int j = dfn[y]; j <= post[y]; ++j) {
            bag[v[rk[j]]] = inf;
        }
    }
    if(son[x]) maxv = max(dfs(son[x], x), maxv);
    bag[v[x]] = max(bag[v[x]], dep[x]);
    maxv = max(maxv, find_max(v[x]) - dep[x]);

    reg(i, x) {
        int y = e[i].to;
        if(y == dad || y == son[x]) continue;
        maxv = max(maxv, getans(y) - 2 * dep[x]);
        getchk(y);
    }
    return ans[x] = maxv;
} 

int main() {
    int n;
    cin >> n;
    char op[4];
    for(int i = 1, uu; i < n; ++i) {
        scanf("%d %s", &uu, op);
        ine2(uu, i + 1, op[0]);
    }
    change(1, 0, 1);
    //printf("1\n");
    pre(1, 0, 0);
    /*
    memcpy(tmp, v, sizeof(v));
    sort(tmp + 1, tmp + n + 1);
    int cnt = unique(tmp + 1, tmp + n + 1) - tmp;
    for(int i = 1; i < cnt; ++i) {
        id[tmp[i]] = i;
    }*/
    //printf("2\n");
    for(int i = 0; i < (1<<22); ++i) {
        bag[i] = inf;
    }
    dfs(1, 0);
    for(int i = 1; i <= n; ++i) {
        printf("%d ", ans[i]);
    }
    printf("\n");
}