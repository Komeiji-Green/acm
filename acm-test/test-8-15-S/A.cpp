#include <cstring>
#include <iostream>
#include <queue>
#include <cstdio>
using namespace std;
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define mp make_pair

typedef long long ll;

const int M = 2333334;
const int N = 10000;
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

int n, m, clock, low[N], dfn[N];


// 强连通分量
bool vis[N];
int sta[N], top = 0;
int scc[N], sccnum = 0;
void tarjan(int cur, int dad)
{
    sta[++top] = cur;
    vis[cur] = 0;
    dfn[cur] = ++clock;
    low[cur] = clock;
    bool flag = false;
    reg(i, cur)
    {
        flag = true;
        int nex = e[i].to;
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
    if((dfn[cur] == low[cur]) /*|| (dad == 0 && !flag)*/) { 
        sccnum++;
        do {
            vis[sta[top]] = 1;
            scc[sta[top]] = sccnum;
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

int ans[N];
int ansnum = 0;

int main()
{
    while(scanf("%d", &n) != EOF && n != 0) {
        scanf("%d", &m);

        tot = 0;
        memset(last, 0, sizeof(last));
        int u, v;
        rep(i, 1, m) {
            scanf("%d %d", &u, &v);
            ine(u, v, 0);
        }

        top = 0;
        sccnum = 0;
        memset(vis, 0, sizeof(vis));
        clock = 0;
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(deg, 0, sizeof(deg));

        // 非连通性需考虑, 孤立点应算SCC
        rep(i, 1, n) {
            if(!dfn[i])
                tarjan(i, 0);
        }

        build();

        ansnum = 0;
        rep(i, 1, n) {
            if(deg[scc[i]] == 0) {
                ans[++ansnum] = i;
            }
        }

        rep(i, 1, ansnum) {
            printf("%d", ans[i]);
            if(i != ansnum)
            printf(" ");
        }
        printf("\n");
    }
}