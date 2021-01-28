#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define mp make_pair

typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int M = 20000;
const int N = 3000;

struct Edge {
    int from, to, pre;
    ll w;
} e[M];
int last[M];
int tot = 0;

void ine(int a, int b, ll w) {
    tot++;
    e[tot].from = a; e[tot].to = b; e[tot].w = w;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b, ll w) {
    ine(a, b, w); ine(b, a, w);
}


#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)


// 最大流
int n, m, s, t, lv[N], cur[M];  // lv：每点层数，cur：当前弧
inline bool bfs() 
{
    rep(i, 1, n) lv[i] = -1;
    lv[s] = 0;
    memcpy(cur, last, sizeof(last));
    queue<int> q;
    q.push(s);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int i = cur[u]; i; i = e[i].pre) {
            int to = e[i].to;
            ll vol = e[i].w;
            if(vol > 0 && lv[to] == -1)
                lv[to] = lv[u] + 1, q.push(to);
        }
    }
    return lv[t] != -1; // 如果汇点未访问过则不可达
}

ll dfs(int u = s, ll f = INF) {
    if(u == t) 
        return f;
    for(int &i = cur[u]; i; i = e[i].pre) {
        int to = e[i].to;
        ll vol = e[i].w;
        if(vol > 0 && lv[to] == lv[u] + 1) {
            ll c = dfs(to, min(vol, f));
            if(c) {
                e[i].w -= c;
                e[i ^ 1].w += c;    // 反向边
                return c;
            }
        }
    }
    return 0; // 输出流量大小
}

inline ll dinic()
{
    ll ans = 0;
    while(bfs()) {
        ll f;
        while((f = dfs()) > 0)
            ans += f;
    }
    return ans;
}

int main()
{
    cin >> n >> m >> s >> t;
    int u, v;
    ll w;
    tot = 1;
    rep(i, 1, m) {
        scanf("%d %d %lld", &u, &v, &w);
        ine(u, v, w);
        ine(v, u, 0);
    }

    cout << dinic() << endl;
}



// 最小费用流

struct Edge
{
    int to, w, c, next;
} edges[MAXM * 2];
inline void add(int from, int to, int w, int c)
{
    edges[++cnt].to = to;
    edges[cnt].w = w;
    edges[cnt].c = c;
    edges[cnt].next = last[from];
    last[from] = cnt;
}

int fa[N], flow[N], inq[N], dis[N];
queue<int> Q;
bool SPFA()
{
    while (!Q.empty())
        Q.pop();
    memset(fa, -1, sizeof(fa));
    memset(inq, 0, sizeof(inq));
    memset(dis, 127, sizeof(dis));
    flow[s] = INF;
    dis[s] = 0;
    Q.push(s);
    while (!Q.empty())
    {
        int p = Q.front();
        Q.pop();
        inq[p] = 0;
        for (int eg = last[p]; eg != 0; eg = edges[eg].next)
        {
            int to = edges[eg].to, vol = edges[eg].w;
            if (vol > 0 && dis[to] > dis[p] + edges[eg].c) // 容量大于0才增广
            {
                fa[to] = eg; // 记录上一条边
                flow[to] = min(flow[p], vol); // 更新下一个点的流量
                dis[to] = dis[p] + edges[eg].c; // 注意这里是c不是w
                if (!inq[to])
                {
                    Q.push(to);
                    inq[to] = 1;
                }
            }
        }
    }
    return fa[t] != -1;
}
int maxflow, mincost;
inline void MCMF() // 这里要求两个值，直接改成给全局变量赋值了，传pair也可以吧
{
    while (SPFA())
    {
        maxflow += flow[t];
        mincost += dis[t] * flow[t];
        for (int i = t; i != s; i = edges[fa[i] ^ 1].to)
        {
            edges[fa[i]].w -= flow[t];
            edges[fa[i] ^ 1].w += flow[t];
        }
    }
}