#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define mp make_pair

typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int M = 200000;
const int N = 3000;

struct Edge {
    int from, to, pre;
    ll w;
} e[M];
int last[N];
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
        while((f = dfs()) > 0)
            ans += f;
    }
    return ans;
}

int main()
{
    int T;
    cin >> T;
    for(int test = 1; test <= T; test++) {
        int task, machine;
        cin >> task >> machine;
        n = task + 500 + 2; // 全部任务、全部时间点、源点汇点
        s = n - 1; t = n;

        tot = 1;
        memset(last, 0, sizeof(last));

        rep(i, 1, 500) {    // 时间点
            ine(s, i, (ll)machine); // 每天最多委派machine个机器
            ine(i, s, 0);
        }
        int pi, si, ei;
        ll sum = 0;
        rep(i, 501, n - 2) {    // 任务点
            scanf("%d %d %d", &pi, &si, &ei);
            rep(j, si, ei) {
                ine(j, i, 1);   // 每天至多有一台机器
                ine(i, j, 0);
            }
            ine(i, t, pi);  // 每个任务做pi天即可
            ine(t, i, 0);
            sum += pi;
        }
        
        ll ans = dinic();
        printf("Case %d: ", test);
        printf(ans == sum ? "Yes\n" : "No\n");
        printf("\n");
    }
}