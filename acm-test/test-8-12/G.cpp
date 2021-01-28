#include <cstring>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define mp make_pair

typedef long long ll;

const int M = 600000 + 5;
const int N = 100000 + 500;

struct Edge
{
    int from, to, pre;
    ll w;
} e[M];
int last[M];
int tot = 0;

void ine(int a, int b, ll w)
{
    tot++;
    e[tot].from = a;
    e[tot].to = b;
    e[tot].w = w;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b, ll w)
{
    ine(a, b, w);
    ine(b, a, w);
}

#define reg(i, x) for (int i = last[x]; i; i = e[i].pre)

int n, m, clc, low[N], dfn[N];

// 求桥, ebcc
bool vis[N];
int sta[1000000], top = 0;
int ebcc[N], ebccnum = 0;
void tarjan(int cur, int dad)
{
    sta[++top] = cur;
    vis[cur] = 0;
    low[cur] = dfn[cur] = ++clc;
    bool flag = false;
    reg(i, cur)
    {
        int nex = e[i].to;
        if(nex == dad && !flag) {   // 这是正常的反向边，不要碰它
            flag = true;
            continue;
        }
        if (!dfn[nex])  // 树边
        {
            tarjan(nex, cur);
            low[cur] = min(low[cur], low[nex]);
        }
        else if (!vis[nex]) // 也是提防重边
        {
            low[cur] = min(low[cur], dfn[nex]);
        }
    }
    if(dfn[cur] == low[cur]) {  // 从dad到cur是一个桥
        ebccnum++;
        //printf("%d: ", ebccnum);
        do {
            vis[sta[top]] = 1;
            ebcc[sta[top]] = ebccnum;
            //printf("%d ", sta[top]);
        } while(top && sta[top--] != cur);
        //cout << endl;
    }
}


Edge ee[M];
int la[M];
int es = 0;

void ine3(int a, int b, ll w)
{
    es++;
    ee[es].from = a;
    ee[es].to = b;
    ee[es].w = w;
    ee[es].pre = la[a];
    la[a] = es;
}

void build()
{
    rep(x, 1, n) {
        reg(i, x) {
            int y = e[i].to;
            if(ebcc[x] != ebcc[y]) {
                ine3(ebcc[x], ebcc[y], 0);
            }
        }
    }
}

int size[N]; // 子树大小
int dep[N]; // 深度
int anc[N][30]; // 祖先
int minv[N][30]; // 最小权-->边权
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
    for(lg = 0; lg <= 20; lg++) if((1 << (lg - 1)) > n) break;
    if(dep[a] > dep[b]) swap(a, b);
    int d = dep[b] - dep[a];
    for(int i = lg; i >= 0; i--) {
        //if(dep[a] < (1 << i)) continue;
        if((1 << i) & d) b = anc[b][i];
    }
    //cout << a << " " << b << endl;
    if(a == b) return a;
    for(int i = lg; i >= 0; i--) {
        //if(dep[a] < (1 << i)) continue;
        if(anc[a][i] != anc[b][i]) {
            a = anc[a][i]; b = anc[b][i];
        }
    }
    if(a != b)
        a = anc[a][0], b = anc[b][0];
    return a;
}

void init()
{
    tot = 0;
    es = 0;
    memset(last, 0, sizeof(int) * 3 * (m + 10));
    memset(la, 0, sizeof(int) * 3 * (m + 10));
    clc = 0;
    memset(low, 0, sizeof(int) * (n + 10));
    memset(dfn, 0, sizeof(int) * (n + 10));
    top = 0;
    ebccnum = 0;
    memset(vis, 0, sizeof(bool) * (n + 10));
    memset(dep, 0, sizeof(int) * (n + 10));
    memset(anc, 0, sizeof(anc));

}

int main()
{
    int T;
    cin >> T;
    while(T--) {
        int q;
        cin >> n >> m >> q;

        init();
        int u, v, w;
        rep(i, 1, m) {
            scanf("%d %d", &u, &v);
            ine2(u, v, 0);
        }
        
        rep(i, 1, n) {
            if(!dfn[i])
                tarjan(i, 0);
        }

        build();

        rep(i, 1, ebccnum) {
            if(dep[i] == 0)
                change(i, 0, 1);
        }

        /*rep(i, 1, ebccnum) {
            printf("%d: anc: ", i);
            rep(j, 0, lg)
                printf("%d ", anc[i][j]);
            cout << endl;
        }*/

        int d, x, y;
        rep(i, 1, q) {
            scanf("%d %d %d", &d, &x, &y);

            d = ebcc[d]; x = ebcc[x]; y = ebcc[y];
            bool ok = true;
            int f = lca(x, y);  //printf("f: %d ", f);
            if(f == 0) ok = false;
            else {
                int ff = lca(f, d);// printf("ff: %d ", ff);
                if(ff != f) ok = false;
                else {
                    int f1 = lca(d, x); //printf("f1: %d ", f1);
                    int f2 = lca(d, y); //printf("f2: %d ", f2);
                    if(f1 != d && f2 != d) ok = false;
                }
            }
            printf(ok ? "Yes\n" : "No\n");
        }
    }
}