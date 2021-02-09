#include<bits/stdc++.h>
#include<random>
using namespace std;
typedef unsigned long long ll;

const int maxn = (1<<25) + 7;
const int N = 300007;

// 可持久化线段树
struct node {
    int l, r; ll val;
} tr[maxn];
int rt[N], tot;
int clone(int k) {
    ++tot;
    tr[tot] = tr[k];
    return tot;
}
void pushup(int k) {
    tr[k].val = tr[tr[k].l].val^tr[tr[k].r].val;
}
void update(int &k, int x, ll val, int l, int r) {
    k = clone(k);
    if(l == r) {
        tr[k].val ^= val;
    } else {
        int m = ((l + r) >> 1);
        if(x <= m) update(tr[k].l, x, val, l, m);
        else update(tr[k].r, x, val, m + 1, r);
        pushup(k);
    }
}

ll hsh[N];
int a[N], n;

int pos;
// 存在性二分搜索: 寻找pos使得异或值非0
void bsearch(int b, int c, int d, int e, int L, int R, int l, int r) {
    if(L <= l && r <= R) {
        ll sum = tr[b].val^tr[c].val^tr[d].val^tr[e].val;
        if(!sum) return;
        if(l == r) pos = l;
    }
    int m = ((l + r) >> 1);
    if(L <= m) bsearch(tr[b].l,tr[c].l,tr[d].l,tr[e].l, L, R, l, m); 
    if(pos != -1) return;
    if(R > m) bsearch(tr[b].r,tr[c].r,tr[d].r,tr[e].r, L, R, m + 1, r);
}

void dfs(int x, int dad) {
    rt[x] = rt[dad];
    update(rt[x], a[x], hsh[a[x]], 1, n);
    for(auto y : ch[x]) {
        if(y == dad) continue;
        dfs(y, x);
    }
}

vector<int> ch[N];
int dep[N]; // 深度
int anc[N][30]; // 祖先
int lg;

void change(int x, int dad, int dept) {
    dep[x] = dept;
    for(int i = 1; i <= lg; ++i) {
        if(dep[x] < (1 << i)) break;
        anc[x][i] = anc[anc[x][i - 1]][i - 1];
    }
    for(auto y : ch[x]) {
        if(y == dad) continue;
        anc[y][0] = x;
        change(y, x, dept + 1);
    }
}

// 倍增
int lca(int a, int b) {
    if(dep[a] > dep[b]) swap(a, b);
    int d = dep[b] - dep[a];
    for(int i = lg; i >= 0; i--) {
        if(dep[b] < (1 << i)) continue;
        if((1 << i) & d) b = anc[b][i];
    }
    for(int i = lg; i >= 0; i--) {
        if(dep[a] < (1 << i)) continue;
        if(anc[a][i] != anc[b][i]) {
            a = anc[a][i]; b = anc[b][i];
        }
    }
    if(a != b)
        a = anc[a][0], b = anc[b][0];
    return a;
}

int main() {
    mt19937 eng(time(0));
    uniform_int_distribution<ll> dis(1ull, 0xffffffffffffffffull);
    int q; cin >> n >> q;
    for(int i = 1; i <= n; ++i) hsh[i] = dis(eng);
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for(int i = 1, u, v; i < n; ++i) {
        scanf("%d %d", &u, &v);
        ch[u].push_back(v); ch[v].push_back(u);
    }
    // lca
    for(lg = 1; lg <= 21; lg++) if(n < (1 << (lg - 1))) break;
    change(1, 0, 1);
    // kcjh
    dfs(1, 0);

    while(q--) {
        int u, v, l, r;
        scanf("%d %d %d %d", &u, &v, &l, &r);
        int f = lca(u, v);
        int ff = anc[f][0];
        int m = ((l + r) >> 1);
        pos = -1;
        bsearch(rt[u], rt[v], rt[f], rt[ff], l, r, 1, n);
        printf("%d\n", pos);
    }
}