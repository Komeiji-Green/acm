#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define mp make_pair

typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f;
const int N = 3050;
const int M = 1000005;

struct Edge {
    int to, pre;
    ll w;
} e[M];
int last[N], tot;

void ine(int a, int b, ll w) {
    tot++;
    e[tot].to = b; e[tot].w = w;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b, ll w) {
    ine(a, b, w); ine(b, a, w);
}


#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)


// 最大流
int n, s, t, lv[N], cur[N];  // lv：每点层数，cur：当前弧
inline bool bfs() {
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

inline ll dinic() {
    ll ans = 0;
    while(bfs()) {
        ll f;
        while((f = dfs()) > 0)
            ans += f;
    }
    return ans;
}

int a[N], b[N];
const ll maxv = 100000;
vector<int> vec[105];
int main() {
    cin >> n;
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for(int i = 1; i <= n; ++i) vec[a[i]].push_back(i);
    for(int i = 1; i <= 100; ++i) sort(vec[i].begin(), vec[i].end());
    for(int i = 1; i <= n; ++i) scanf("%d", &b[i]);
    s = n + 1; t = n + 2;
    tot = 1; // 方便获取反向边
    rep(i, 1, n) {
        ine(s, i, maxv); ine(i, s, 0); // 若i属于T，则i的cost为maxv
        ine(i, t, maxv - b[i]); ine(t, i, 0); // 若i属于S，则i的cost为maxv-b[i]
        //ine(i, t + a[i], INF); ine(t + a[i], i, 0);
    }
    for(int i = 1, k; i <= n; ++i) {
        for(k = a[i]; k <= 100; k += a[i]) {
            for(auto j : vec[k]) {
                if(j > i) {
                    ine(j, i, INF); ine(i, j, 0);
                    break;
                }
            }
        }
    }
    n += 2;
    ll ans = dinic();
    n -= 2;
    cout << -(ans - n * maxv) << endl;
}