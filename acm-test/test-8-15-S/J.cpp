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

void add(int a, int b, int w, int c) {
    ine(a, b, w, c);
    ine(b, a, 0, -c);
}

int num, m, s, t;

int fa[N], flow[N], inq[N], dis[N];
queue<int> Q;
bool SPFA()
{
    while (!Q.empty())
        Q.pop();
    memset(fa, 0, sizeof(fa));
    memset(inq, 0, sizeof(inq));
    memset(flow, 0x7f, sizeof(flow));
    rep(i, 1, num) dis[i] = INF;
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

// 让流等价于糖果数量
// 如果不考虑喜欢与否，糖果是一样的，所以应该先把喜欢的糖果分配完
// 对于每个孩子，容量为bi，将其拆成两个点A，B
// 如果一个糖果与该孩子匹配，则向A连一条容量为1、费用为k的边，
// 向B连一条容量为1、费用为bi % k的边（如果bi % k != 0）
// A向终点t连一条容量为bi/k的边，表示所有能够不浪费的糖的总量
// B向终点t连一条容量为1的边，表示能浪费的糖只有一个
// 求最大费用最大流，即表示尽可能多地将有like关系的糖与孩子匹配，
// 并且使这些的效益最大，即浪费最小
// 最后sum(bi) - maxcost即为剩余的满意度，这些满意度只能用非like关系的糖去填补，
// 将此值与剩余糖的数量比较即可，注意：糖的使用数量是最大流

int b[100];
int like[100][100];

int main()
{
    int T;
    cin >> T;
    for(int test = 1; test <= T; test++) {
        int k;
        int n;
        cin >> n >> m >> k;
        rep(i, 1, m) {
            scanf("%d", &b[i]);
        }

        rep(i, 1, m) {
            rep(j, 1, n) {
                scanf("%d", &like[i][j]);
            }
        }

        tot = 1;
        memset(last, 0, sizeof(last));

        s = n + 2 * m + 1;
        t = s + 1;

        rep(i, 1, n) {  //  n个糖果
            add(s, i, 1, 0);
        }

        rep(i, 1, n) rep(j, 1, m) {
            if(like[j][i]) {
                add(i, n + 2 * j - 1, 1, -k);
                if(b[j] % k != 0) {
                    add(i, n + 2 * j, 1, -(b[j] % k));
                }
            }
        }

        rep(j, 1, m) {
            add(n + 2 * j - 1, t, b[j] / k, 0);
            if(b[j] % k != 0) {
                add(n + 2 * j, t, 1, 0);
            }
        }

        num = t;
        MCMF();

        int maxcost = -mincost;
        int sum = 0;
        rep(i, 1, m) {
            sum += b[i];
        }

        //printf("%d %d\n", maxflow, maxcost);

        if((sum - maxcost) > (n - maxflow)) {
            printf("Case #%d: NO\n", test);
        } else {
            printf("Case #%d: YES\n", test);
        }
    }
}
