#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
using namespace std;
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define mp make_pair
#define P pair<int, int>

typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int inf = 0x3f3f3f3f;
const int M = 233333;
const int N = 2333;

struct Edge {
    int from, to, pre;
    ll w;
} e[M];
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
    e[es].from = a; e[es].to = b; e[es].w = w;
    e[es].pre = last[a];
    last[a] = es;
}


#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)

// 最大流
int n, m, s, t, lv[N], cur[N];  // lv：每点层数，cur：当前弧
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
        while((f = dfs()) > 0) {
            ans += f;
            //printf("%d\n", ans);
        }
    }
    return ans;
}


int disa[N];    // 从a出发的最短路
int disb[N];    // 从b出发的最短路
bool vis[N];
void dijkstra(int st, int dis[], int d)
{
    rep(i, 1, n) dis[i] = inf;
    memset(vis, 0, sizeof(vis));
    priority_queue<P> q;
    q.push(mp(0, st));
    dis[st] = 0;
    while(!q.empty()) {
        P pr = q.top(); q.pop();
        int x = pr.second;
        if(vis[x]) continue;
        int cost = -pr.first;
        dis[x] = cost;
        vis[x] = true;
        reg(i, x) {
            if((i % 2) != d) continue;
            int y = e[i].to;
            if(dis[y] > cost + e[i].w) dis[y] = cost + e[i].w;
            if(!vis[y]) {
                q.push(mp(-dis[y], y));
            }
        }
    }
}

int main()
{
    int T;
    cin >> T;
    while(T--) {
        cin >> n >> m;
        int a, b, c;

        tot = 1;
        memset(last, 0, sizeof(last));
        rep(i, 1, m) {
            scanf("%d %d %d", &a, &b, &c);
            if(a == b) continue;
            ine(a, b, c);    // 偶数为正向边
            ine(b, a, c);    // 奇数为反向边
        }
        scanf("%d %d", &s, &t);

        dijkstra(s, disa, 0);
        dijkstra(t, disb, 1);

        int dist = disa[t];
        if(dist == inf) {
            printf("0\n");
            continue;
        }

        es = 1;
        memset(last, 0, sizeof(last));
        for(int i = 2; i <= tot; i += 2) {
            int u = e[i].from, v = e[i].to;
            if(disa[u] != inf && disb[v] != inf && disa[u] + disb[v] + e[i].w == dist) {
                ine3(u, v, 1);
                ine3(v, u, 0);
            }
        }

        ll ans = dinic();
        printf("%lld\n", ans);
    }
}