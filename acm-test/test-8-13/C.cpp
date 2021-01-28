#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define mp make_pair

typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int M = 50000;
const int N = 2000;

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

int nums[2000]; //每种人的个数
int main()
{
    // 总共只有1024种人！！！！！
    int people;
    while(scanf("%d", &people) != EOF) {
        scanf("%d", &m);
        
        int w;
        tot = 1;
        memset(last, 0, sizeof(last));
        memset(nums, 0, sizeof(nums));
        rep(i, 1, people) {  // 第i个人
            int d = 1;  // 第d种人
            rep(j, 0, m - 1) {  // 第j位
                scanf("%d", &w);
                if(w == 1)
                    d += (1 << j);
            }
            nums[d]++;
        }
        s = 1050, t = 1051;
        rep(d, 1, 1024) {
            int num = nums[d];
            if(nums[d]) {
                ine(s, d, (ll)num);
                ine(d, s, 0);
            }
            rep(j, 0, m - 1) {
                if((1 << j) & (d - 1)) {
                    ine(d, 1025 + j, (ll)num);
                    ine(1025 + j, d, 0);
                }
            }
        }
        rep(j, 0, m - 1) {
            scanf("%d", &w);
            ine(1025 + j, t, (ll)w);
            ine(t, 1025 + j, 0);
        }
        
        n = t;
        ll ans = dinic();
        printf(ans == people ? "YES\n" : "NO\n");
    }
}