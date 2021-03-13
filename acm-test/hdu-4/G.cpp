#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;
#define rep(i, a, b) for(int i = (a); i <= (b); ++i)
#pragma comment(linker, "/STACK:102400000,102400000")

typedef int ll;
const int M = 2333333;
const int N = 233333;
const int INF = 0x3f3f3f3f;

// 最大流
struct Edge {
    int from, to, pre;
    ll w;
} e[M];
int last[M], tot = 1;

void ine(int a, int b, ll w) {
    ++tot;
    e[tot].from = a; e[tot].to = b; e[tot].w = w;
    e[tot].pre = last[a];
    last[a] = tot;
}

void add(int a, int b, ll w) {
    ine(a, b, w); ine(b, a, 0);
}

int s, t, lv[N], cur[M];  // lv：每点层数，cur：当前弧
inline bool bfs(int n)  {
    rep(i, 1, n) lv[i] = -1, cur[i] = last[i];
    lv[s] = 0;
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
        while((f = dfs()) > 0)
            ans += f;
    }
    return ans;
}

ll a[N], b[N], sa[N], sb[N];
int lsh(ll *v, int n, ll key) {
    int idx = lower_bound(v + 1, v + n + 1, key) - v;
    return idx;
}
int main() {
    int T, n;
    ll x, y;
    cin >> T;
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) {
            scanf("%d %d", &x, &y);
            a[i] = y-x; b[i] = y+x;
        }
        for(int i = 1; i <= n; ++i) sa[i] = a[i], sb[i] = b[i];
        sort(sa + 1, sa + n + 1);
        int n1 = unique(sa + 1, sa + n + 1) - sa - 1;
        sort(sb + 1, sb + n + 1);
        int n2 = unique(sb + 1, sb + n + 1) - sb - 1;
        s = n1 + n2 + 1, t = n1 + n2 + 2;

        tot = 1; for(int i = 1; i <= t; ++i) last[i] = 0;
        for(int i = 1; i <= n; ++i) {
            int u = lsh(sa, n1, a[i]), v = lsh(sb, n2, b[i]) + n1;
            add(u, v, 1);
        }
        for(int i = 1; i <= n1; ++i) add(s, i, 1);
        for(int i = 1; i <= n2; ++i) add(n1 + i, t, 1);
        int res = dinic(t);
        printf("%d\n", res);
    }
}