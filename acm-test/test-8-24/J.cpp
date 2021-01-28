#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
using namespace std;
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define mp make_pair

typedef long long ll;
#define P pair<ll, int>

const ll INF = 0x3f3f3f3f3f3f3f3f;
const int inf = 0x3f3f3f3f;
const int M = 500000;
const int N = 2333;

struct Edge {
    int from, to, pre;
    ll w;
} e[M], tmp[M];
int last[N];
//Edge temp_e[M];
int tot = 0;
int es = 0;

void ine(int a, int b, ll w) {
    tot++;
    e[tot].from = a; e[tot].to = b; e[tot].w = w;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b, ll w) {
    ine(a, b, w); ine(b, a, w);
}

void ine3(int a, int b, ll w) {
    es++;
    tmp[es].from = a; tmp[es].to = b; tmp[es].w = w;
    tmp[es].pre = last[a];
    last[a] = es;
}
void add(int a, int b, ll w) {
    ine3(a, b, w);
    ine3(b, a, 0);
}


#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)

// 最大流
int s, t, lv[N], cur[N];  // lv：每点层数，cur：当前弧
inline bool bfs(int n) 
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

inline ll dinic(int n)
{
    ll ans = 0;
    while(bfs(n)) {
        ll f;
        while((f = dfs()) > 0) {
            ans += f;
            //printf("%d\n", ans);
        }
    }
    return ans;
}


ll disa[N];    // 从a出发的最短路
ll disb[N];    // 从b出发的最短路
bool vis[N];
void dijkstra(int st, ll dis[], int n)
{
    rep(i, 1, n) dis[i] = INF;
    memset(vis, 0, sizeof(vis));
    priority_queue<P> q;
    q.push(mp(0, st));
    dis[st] = 0;
    while(!q.empty()) {
        P pr = q.top(); q.pop();
        int x = pr.second;
        if(vis[x]) continue;
        ll cost = -pr.first;
        dis[x] = cost;
        vis[x] = true;
        reg(i, x) {
            int y = e[i].to;
            if(dis[y] > cost + e[i].w) dis[y] = cost + e[i].w;
            if(!vis[y]) {
                q.push(mp(-dis[y], y));
            }
        }
    }
}

ll G[505][505];

int main()
{
    //freopen("network1.in", "r", stdin);
    int n, m;
    cin >> n >> m;
    int a, b;
    ll d;

    rep(i, 1, n) rep(j, 1, n) {
        G[i][j] = INF;
    }
    rep(i, 1, m) {
        scanf("%d %d %lld", &a, &b, &d);
        G[a][b] = min(G[a][b], d);
    }
    tot = 1;
    rep(i, 1, n) rep(j, 1, n) {
        if(G[i][j] != INF) {
            ine2(i, j, G[i][j]);
        }
    }


    dijkstra(1, disa, n);
    dijkstra(n, disb, n);

    //printf("%lld %lld\n", disa[n], disb[1]);

    es = 1;
    memset(last, 0, sizeof(last));

    ll c;
    rep(i, 1, n) {
        scanf("%lld", &c);
        add(i, i + n, c);
    }
    rep(i, 2, tot) {
        int u = e[i].from, v = e[i].to;
        // 这样可以遍历正反边各一次
        if(disa[u] + disb[v] + e[i].w == disa[n]) {
            add(u + n, v, INF);
            //printf("%d %d\n", u, v);
        }
    }

    s = n + 1;
    t = n;
    memcpy(e, tmp, sizeof(tmp));
    tot = es;

    ll ans = dinic(2 * n);

    printf("%lld\n", ans);
}