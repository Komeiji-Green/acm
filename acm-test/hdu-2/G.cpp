#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 23333, M = 46666;
const ll INF = 0x3f3f3f3f3f3f3f;
struct Edge {
    int from, to, pre;
    ll a, b;
} e[M];
int last[N], tot;
void ine(int a, int b, ll x, ll y) {
    ++tot;
    e[tot].from = a; e[tot].to = b; e[tot].a = x; e[tot].b = y;
    e[tot].pre = last[a]; last[a] = tot;
}
inline void ine2(int a, int b, ll x, ll y) {
    ine(a, b, x, y); ine(b, a, x, y);
}

void chk(ll &x, ll y) {
    if(x > y) x = y;
}
ll dp[N][25], tmp[25]; // 树上背包 + 滚动
ll m;   // 最大直径
int k, size[N]; // 可动边的个数，防止被菊花图卡。
void dfs(int x, int dad) {
    ll va, vb;
    for(int i = 1; i <= k; ++i) dp[x][i] = INF;
    dp[x][0] = 0;
    size[x] = 0;
    int sz = 0;
    for(int i = last[x], y; i; i = e[i].pre) {
        y = e[i].to; if(y == dad) continue;
        va = e[i].a; vb = e[i].b;
        dfs(y, x); 
        sz = min(size[x] + size[y] + 1, k);
        for(int u = 0; u <= sz; ++u) tmp[u] = INF;
        for(int u = 0; u <= size[y]; ++u) {
            for(int v = 0; v <= size[x] && u + v <= sz; ++v) {
                if(dp[y][u] + dp[x][v] + vb <= m)
                    chk(tmp[u + v], max(dp[y][u] + vb, dp[x][v]));
                if(u + v + 1 <= sz && dp[y][u] + dp[x][v] + va <= m)
                    chk(tmp[u + v + 1], max(dp[y][u] + va, dp[x][v]));
            }
        }
        size[x] = sz;
        for(int u = 0; u <= sz; ++u) dp[x][u] = tmp[u];
    }
}
int main() {
    int T, n;
    cin >> T;
    while(T--) {
        scanf("%d %d", &n, &k);
        ll a, b;
        tot = 0;
        for(int i = 1; i <= n; ++i) last[i] = 0;
        for(int i = 1, u, v; i < n; ++i) {
            scanf("%d %d %lld %lld", &u, &v, &a, &b);
            ine2(u, v, a, b);
        }
        ll le = 1, ri = (ll)(n - 1) * 1000000000ll;
        ll mid = ((le + ri) >> 1);
        while(le < ri) {
            m = mid;
            dfs(1, 0);
            if(dp[1][k] < INF) {
                ri = mid;
            } else {
                le = mid + 1;
            }
            mid = ((le + ri) >> 1);
        }
        //m = 6;
        //dfs(1, 0);
        /*for(int i = 1; i <= n; ++i) {
            printf("%d: ", i);
            for(int j = 0; j <= k; ++j) {
                printf("%lld ", dp[i][j]);
            }
            printf("\n\n");
        }*/
        printf("%lld\n", mid);
    }
}