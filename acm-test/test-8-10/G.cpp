#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define mp make_pair

typedef long long ll;
const int INF = 0x3f3f3f3f;

inline void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

const int M = 2333333;
const int N = 2333333;

struct Edge {
    int from, to, pre;
    ll w;
} e[M];
int last[M];
int tot = 0;

void ine(int a, int b, ll w) {
    tot++;
    e[tot].from = a; e[tot].to = b; e[tot].w = w;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b, ll w) {
    ine(a, b, w); ine(b, a, w);
}


#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)


int n, m, mm;

vector<int> G[N];

struct cmp {
    bool operator() (const Edge&lhs, const Edge& rhs) {
        return lhs.w > rhs.w;
    }
};

int f[N];
int find(int x) { return f[x] == x ? x : (f[x] = find(f[x])); }
void merge(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    f[fx] = fy;
}

Edge ee[M];
int la[M];
int es = 0;

void ine3(int a, int b, ll w) {
    es++;
    ee[es].from = a; ee[es].to = b; ee[es].w = w;
    ee[es].pre = la[a];
    la[a] = es;
}

inline void ine4(int a, int b, ll w) { ine3(a, b, w); ine3(b, a, w); } 

void Kruskal()
{
    rep(i, 1, n) f[i] = i;
    sort(e + 1, e + tot + 1, cmp());
    int u, v;
    rep(i, 1, tot) {
        u = e[i].from, v = e[i].to;
        int fu = find(u), fv = find(v);
        if(fu == fv) continue;
        f[fu] = fv;
        ine4(u, v, e[i].w);
    }
}

int size[N]; // 子树大小
int dep[N]; // 深度
int anc[N][30]; // 祖先
int minv[N][30]; // 最小权
int lg;

// dad是用来防止重复遍历的
void change(int x, int dad, int dept) {
    size[x] = 1;
    dep[x] = dept;
    for(lg = 0; lg <= 20; lg++) if(n < (1 << (lg - 1))) break;
    rep(i, 1, lg) {
        if(dep[x] < (1 << i)) break;
        anc[x][i] = anc[anc[x][i - 1]][i - 1];
        minv[x][i] = min(minv[x][i - 1], minv[anc[x][i - 1]][i - 1]);
    }
    for(int i = la[x]; i; i = ee[i].pre) {
        int y = ee[i].to;
        if(y == dad) continue;
        anc[y][0] = x;
        minv[y][0] = ee[i].w;
        change(y, x, dept + 1);
        size[x] += size[y];
    }
}

// 倍增
int lca(int a, int b) {
    for(lg = 1; lg <= 20; lg++) if((1 << (lg - 1)) > n) break;
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

int query_min(int a, int b) {
    for(lg = 1; lg <= 20; lg++) if((1 << (lg - 1)) > n) break;
    if(dep[a] < dep[b]) swap(a, b);
    int d = dep[a] - dep[b], ret = INF;
    for(int i = lg; i >= 0; i--) {
        if(dep[a] < (1 << i)) continue;
        if((1 << i) & d) { 
            ret = min(ret, minv[a][i]);
            a = anc[a][i];
        }
    }
    if(a == b) return ret;
    for(int i = lg; i >= 0; i--) {
        if(dep[a] < (1 << i)) continue;
        if(anc[a][i] != anc[b][i]) {
            ret = min(ret, min(minv[a][i], minv[b][i]));
            a = anc[a][i]; b = anc[b][i];
        }
    }
    if(a != b) {
        ret = min(ret, min(minv[a][0], minv[b][0]));
        a = anc[a][0]; b = anc[b][0];
    }
    return ret;
}

int main()
{
    cin >> n >> m;
    int u, v, w;
    rep(i, 1, m) {
        scanf("%d %d %d", &u, &v, &w);
        ine2(u, v, w);
    }

    Kruskal();
    rep(i, 1, n) rep(j, 0, 29) {
        minv[i][j] = INF;
    }
    rep(i, 1, n) {
        if(dep[i] == 0)
            change(i, 0, 1);
    }

    /*rep(i, 1, n) {
        printf("%d: minv: ", i);
        rep(j, 0, lg)
            printf("%d ", minv[i][j]);
        printf("anc: ");
        rep(j, 0, lg)
            printf("%d ", anc[i][j]);
        cout << endl;
    }*/
 
    int q;
    cin >> q;
    int a, b;
    rep(i, 1, q) {
        scanf("%d %d", &a, &b);
        if(find(a) != find(b)) printf("-1\n");
        else {
            printf("%d\n", query_min(a, b));
        }
    }
}