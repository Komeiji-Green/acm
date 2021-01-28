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

const int M = 233333;
const int N = 233333;

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

int n;

// 倍增LCA
//int size[N]; // 子树大小
int dep[N]; // 深度
int anc[N][30]; // 祖先
//int minv[N][30]; // 最小权
int lg;

// dad是用来防止重复遍历的
void change(int x, int dad, int dept) {
    //size[x] = 1;
    dep[x] = dept;
    for(lg = 0; lg <= 20; lg++) if(n < (1 << (lg - 1))) break;
    rep(i, 1, lg) {
        if(dep[x] < (1 << i)) break;
        anc[x][i] = anc[anc[x][i - 1]][i - 1];
        //minv[x][i] = min(minv[x][i - 1], minv[anc[x][i - 1]][i - 1]);
    }
    for(int i = la[x]; i; i = ee[i].pre) {
        int y = ee[i].to;
        if(y == dad) continue;
        anc[y][0] = x;
        //minv[y][0] = ee[i].w;
        change(y, x, dept + 1);
        //size[x] += size[y];
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

int gao(int a, int b, int c, int ab, int bc, int ca) {
    if(ab == ca) {
        return dep[a] - dep[ab] + 1 + dep[bc] - dep[ab];
    } else {
        return min(dep[a] - dep[ab], dep[a] - dep[ca]) + 1;
    }
}

int main()
{
    int q;
    cin >> n >> q;
    int u;
    for(int i = 2; i <= n; i++) {
        scanf("%d", &u);
        ine4(i, u, 0);
    }
    change(1, 0, 1);
    int a, b, c;
    for(int i = 1; i <= q; i++) {
        scanf("%d %d %d", &a, &b, &c);
        int ab = lca(a, b);
        int bc = lca(b, c);
        int ca = lca(c, a);
        int ans = gao(a, b, c, ab, bc, ca);
        ans = max(ans, gao(b, c, a, bc, ca, ab));
        ans = max(ans, gao(c, a, b, ca, ab, bc));
        printf("%d\n", ans);
    }
}
