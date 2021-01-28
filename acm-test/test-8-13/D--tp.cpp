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
const int N = 3000;
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

int n, m, s, t;

int fa[N], flow[N], inq[N], dis[N];
queue<int> Q;
bool SPFA()
{
    while (!Q.empty())
        Q.pop();
    memset(fa, 0, sizeof(fa));
    memset(inq, 0, sizeof(inq));
    memset(flow, 0x3f, sizeof(flow));
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
inline void MCMF() 
{
    memset(flow, 0, sizeof(flow));
    maxflow = 0, mincost = 0;
    while (SPFA())
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

struct Pos {
    Pos() {}
    Pos(int _x, int _y): x(_x), y(_y) {}
    int x, y;
};
char in[105];
Pos man[105];
int pm;
Pos room[106];
int pr;

int main()
{
    int r, c;
    while(scanf("%d %d", &r, &c) != EOF && r != 0) {
        pm = pr = 0;
        rep(i, 0, r - 1) {
            scanf("%s", in);
            rep(j, 0, c - 1) {
                if(in[j] == 'm') man[++pm] = Pos(i, j);
                else if(in[j] == 'H') room[++pr] = Pos(i, j);
            }
        }
        tot = 1;
        memset(last, 0, sizeof(last)); 
    
        rep(i, 1, pm) rep(j, 1, pr) {
            int d = abs(man[i].x - room[j].x) + abs(man[i].y - room[j].y);
            ine(i, 100 + j, 1, d);
            ine(100 + j, i, 0, -d);
        }
        s = 201, t = 202;
        rep(i, 1, pm) {
            ine(s, i, 1, 0);
            ine(i, s, 0, 0);
        }
        rep(j, 1, pr) {
            ine(j + 100, t, 1, 0);
            ine(t, j + 100, 0, 0);
        }
        n = t;
        MCMF();
        printf("%d\n", mincost);
    }
}