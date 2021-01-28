#include <cstring>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define mp make_pair

typedef long long ll;

const int M = 1000000 + 5;
const int N = 333333;

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

int n, m, clock, low[N], dfn[N], iscut[N];
// 求桥, ebcc
bool vis[N];
int sta[1000000], top = 0;
int ebcc[N], ebccnum = 0;
void tarjan(int cur, int dad)
{
    sta[++top] = cur;
    vis[cur] = 0;
    low[cur] = dfn[cur] = ++clock;
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


int nums[N];    // ebcc中桥的个数
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
            if(ebcc[x] == ebcc[y]) {
                nums[ebcc[x]] += e[i].w;
            } else {
                ine3(ebcc[x], ebcc[y], e[i].w);
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
    size[x] = 1;
    dep[x] = dept;
    for(lg = 1; lg <= 20; lg++) if(n < (1 << (lg - 1))) break;
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

int main()
{
    cin >> n >> m;
    int u, v, w;
    rep(i, 1, m) {
        scanf("%d %d %d", &u, &v, &w);
        ine2(u, v, w);
    }

    tarjan(1, 0);
    build();

    int a, b;
    cin >> a >> b;
    change(1, 0, 1);
    /*rep(i, 1, ebccnum) {
        printf("%d: minv: %d nums: %d anc: ", i, minv[i][0], nums[i]);
        rep(j, 0, lg)
            printf("%d ", anc[i][j]);
        cout << endl;
    }*/
    int f = lca(ebcc[a], ebcc[b]);
    //printf("lca: %d\n", f);

    bool ok = false;
    for(int u = ebcc[a]; u && u != f; u = anc[u][0]) {
        if(minv[u][0] > 0) ok = true;
        if(nums[u] > 0) ok = true;
        if(ok) break;
    }
    for(int u = ebcc[b]; u && u != f; u = anc[u][0]) {
        if(minv[u][0] > 0) ok = true;
        if(nums[u] > 0) ok = true;
        if(ok) break;
    }
    if(f && nums[f] > 0) ok = true;
    cout << (ok ? "YES" : "NO") << endl;
}
