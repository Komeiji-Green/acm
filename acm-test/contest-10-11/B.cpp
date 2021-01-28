#include<bits/stdc++.h>
#include<queue>
#include<iostream>
using namespace std;

const int INF = 0x3f3f3f3f;

const int M = 2333333;
const int N = 2333333;
struct Edge {
    int from, to, pre, w, c;
} e[M];
int last[N], tot = 0;

#define rep(i, a, b) for(int i = (a); i <= (b); ++i)
#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)

void ine(int a, int b, int w, int c) {
    ++tot;
    e[tot].from = a; e[tot].to = b; e[tot].w = w; e[tot].c = c;
    e[tot].pre = last[a];
    last[a] = tot;
}

void add(int a, int b, int w, int c) {
    ine(a, b, w, c);
    ine(b, a, 0, -c);
}

int s, t;

// 最小费用最大流
int fa[N], flow[N], inq[N], dis[N];
queue<int> Q;
bool SPFA(int n)
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

int func(int a, int b, int mod) {
    return ((a + b) * (a ^ b) % mod + mod) % mod;
}

int A[500], AA[500], B[500], C[500], va[500], vb[500], vc[500];

int main() {
    int T;
    cin >> T;
    int n, m, M;
    while(T--) {
        scanf("%d %d %d", &n, &m, &M);
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &va[i]);
        }
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &vb[i]);
        }
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &vc[i]);
        }
        for(int i = 1; i <= n; ++i) {
            A[i] = i, B[i] = n + i, C[i] = 2 * n + i;
            AA[i] = 3 * n + i;
        }
        s = 4 * n + 1, t = 4 * n + 2;
        int ss = 4 * n + 3;
        add(s, ss, m, 0);
        for(int i = 1; i <= n; ++i) {
            add(ss, B[i], 1, 0);
        }
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                add(B[i], A[j], 1, -func(vb[i], va[j], M));
            }
        }
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                add(AA[i], C[j], 1, -func(va[i], vc[j], M));
            }
        }
        for(int i = 1; i <= n; ++i) {
            add(A[i], AA[i], 1, 0);
        }
        for(int i = 1; i <= n; ++i) {
            add(C[i], t, 1, 0);
        }
        MCMF(ss);
        int ans = -mincost;
        printf("%d\n", ans);
    }
} 