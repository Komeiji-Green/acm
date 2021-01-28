#include <cstring>
#include <iostream>
#include <queue>
#include <cstdio>
using namespace std;
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define mp make_pair

typedef long long ll;

const int M = 2333334;
const int N = 2333333;
const int mod = 1000000007;

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

int n, m, clock, low[N], dfn[N], iscut[N], cost[N];


// 强连通分量
bool vis[N];
int sta[N], top = 0;
int scc[N], sccnum = 0;
int nums[N];    // 强连通分量中结点数
int minv[N];    // 单个强连通分量中最小消耗值
void tarjan(int cur, int dad)
{
    sta[++top] = cur;
    vis[cur] = 0;
    dfn[cur] = ++clock;
    low[cur] = clock;
    //bool flag = false;
    reg(i, cur)
    {
        //flag = true;
        int nex = e[i].to;
        if (!dfn[nex]) { // 树边
            tarjan(nex, cur);
            low[cur] = min(low[cur], low[nex]);
        }
        else if (!vis[nex]) { // 防重边
            low[cur] = min(low[cur], dfn[nex]);
        }
    }
    if((dfn[cur] == low[cur]) /*|| (dad == 0 && !flag)*/) { 
        sccnum++;
        minv[sccnum] = mod;
        nums[sccnum] = 1;
        do {
            vis[sta[top]] = 1;
            scc[sta[top]] = sccnum;
            int &mm = minv[sccnum];
            int &cc = cost[sta[top]];
            if(mm == cc) nums[sccnum]++;
            else if(cc < mm) { 
                mm = cc;
                nums[sccnum] = 1;
            }
        } while(top && sta[top--] != cur);
    }
}

int deg[N]; // 出度
void build()
{
    rep(i, 1, n) {
        if(scc[i] == 0) {
            sccnum++;
            scc[i] = sccnum;
            nums[sccnum]++;
        }
    }
    rep(x, 1, n) {
        reg(i, x) {
            if(scc[e[i].to] != scc[x]) {
                deg[scc[x]]++;
            }
        }
    }
}

int main()
{
    cin >> n;
    rep(i, 1, n) scanf("%d", &cost[i]);
    cin >> m;
    int u, v;
    rep(i, 1, m) {
        scanf("%d %d", &u, &v);
        ine(u, v, 0);
    }

    // 非连通性需考虑, 孤立点应算SCC
    rep(i, 1, n) {
        if(!dfn[i])
            tarjan(i, 0);
    }

    build();

    int cnt = 1;
    ll ans = 0;
    rep(i, 1, sccnum) {
        ans += minv[i];
        cnt = 1ll * cnt * nums[i] % mod;
    }

    printf("%lld %d\n", ans, cnt);
}