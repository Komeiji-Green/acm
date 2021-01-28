#include <iostream>
#include <queue>
#include <cstring>
#include <cmath>
using namespace std;
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define mp make_pair

typedef long long ll;
const int INF = 0x3f3f3f3f;
const int M = 233333;
const int N = 1333;
// 最小费用流

struct Edge {
    int from, to, w, c, pre;
} e[M];
int last[N];
Edge temp[M];

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

int dist = 0;
int maxflow, mincost;
inline void MCMF() 
{
    //memset(flow, 0, sizeof(flow));
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

bool check(int f) {
    memcpy(e, temp, sizeof(temp));
    e[last[s]].w = f;
    e[last[t] ^ 1].w = f;
    MCMF();
    if(maxflow == f && (ll)mincost <= 1ll * f * dist) return true;
    return false;
}

int main()
{
    int T;
    cin >> T;
    while(T--) {
        int num;
        cin >> num >> m;
        int a, b, c;
        tot = 1;
        memset(last, 0, sizeof(last));
        rep(i, 1, m) {
            scanf("%d %d %d", &a, &b, &c);
            if(a == b) continue;
            ine(a, b, 1, c);
            ine(b, a, 0, -c);
        }
        int A, B;
        scanf("%d %d", &A, &B);
        s = num + 1;
        t = num + 2;
        n = t;
        ine(s, A, 1, 0);
        ine(A, s, 0, 0);
        ine(B, t, 1, 0);
        ine(t, B, 0, 0);
        
        memcpy(temp, e, sizeof(e));

        MCMF();
        if(maxflow == 0) {
            printf("0\n");
            continue;
        }
        dist = mincost;
        int le = 0, ri = m;
        int mid = (le + ri + 1) >> 1;
        while(le < ri) {
            if(check(mid)) {
                le = mid;
            } else {
                ri = mid - 1;
            }
            mid = (le + ri + 1) >> 1; 
        }
        printf("%d\n", mid);
    }
}