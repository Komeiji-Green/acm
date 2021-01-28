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


// 强连通分量
bool vis[N];
int sta[N], top = 0;
int scc[N], sccnum = 0;
int nums[N];    // 强连通分量中结点数
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
            nums[sccnum]++;
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
    cin >> n >> m;
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

    int cnt = 0;
    int ans = 0;
    rep(i, 1, sccnum) {
        if(deg[i] == 0) {
            cnt++;
            ans += nums[i];
        }
    }

    if(cnt == 0 || cnt >= 2) {
        cout << 0 << endl;
    } else {
        cout << ans << endl;
    }
}