#include <iostream>
#include <queue>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <cstdio>
using namespace std;
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define mp make_pair

typedef long long ll;
const int INF = 0x3f3f3f3f;
const int M = 50000;
const int N = 150;
// 最小费用流

struct Edge {
    int from, to, w, c, pre;
} e[M];
int last[N];

int tot = 1;
inline void ine(int from, int to, int w, int c)
{
    e[++tot].to = to;
    e[tot].w = w;
    e[tot].c = c;
    e[tot].from = from;
    e[tot].pre = last[from];
    last[from] = tot;
}

inline void add(int a, int b, int w, int c) {
    ine(a, b, w, c);
    ine(b, a, 0, -c);
}


int s, t;
int fa[N], flow[N], inq[N], dis[N];
queue<int> Q;
bool SPFA(int n)
{
    while (!Q.empty())
        Q.pop();
    memset(fa, 0, sizeof(fa));
    memset(inq, 0, sizeof(inq));
    memset(flow, 0x7f, sizeof(flow));
    rep(i, 1, n) dis[i] = INF;
    flow[s] = INF;
    dis[s] = 0;
    Q.push(s); inq[s] = 1;
    while (!Q.empty())
    {
        int p = Q.front(); Q.pop();
        inq[p] = 0;
        for (int eg = last[p]; eg; eg = e[eg].pre)
        {
            int to = e[eg].to, vol = e[eg].w;
            if (vol > 0 && dis[to] > dis[p] + e[eg].c) // 容量大于0才增广
            {
                fa[to] = eg; // 记录上一条边
                flow[to] = min(flow[p], vol); // 更新下一个点的流量
                dis[to] = dis[p] + e[eg].c; 
                if (!inq[to])
                {
                    Q.push(to);
                    inq[to] = 1;
                }
            }
        }
    }
    return fa[t] != 0;
}

int maxflow, mincost;
inline void MCMF(int n) 
{
    memset(flow, 0, sizeof(flow));
    maxflow = 0, mincost = 0;
    while (SPFA(n))
    {
        //printf("%d %d\n", dis[t], flow[t]);
        maxflow += flow[t];
        mincost += dis[t] * flow[t];
        for (int i = t; i != s; i = e[fa[i] ^ 1].to)
        {
            e[fa[i]].w -= flow[t];
            e[fa[i] ^ 1].w += flow[t];
        }
    }
}

int G[N][N];

void build(int n)
{
    tot = 1;
    memset(last, 0, sizeof(last));

    s = 2 * n + 1, t = 2 * n + 2;
    for(int i = 1; i <= n; i++) {
        add(s, i, 1, 0);
    }
    for(int i = 1; i <= n; i++) {
        add(i + n, t, 1, 0);
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            add(i, j + n, 1, G[i][j]);
        }
    }
}

int main()
{
    int n;
    cin >> n;

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++) 
            scanf("%d", &G[i][j]);

    build(n);
    MCMF(t);
    printf("%d\n", mincost);

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            G[i][j] = -G[i][j];
        }
    }

    build(n);
    MCMF(t);
    printf("%d\n", -mincost);
}