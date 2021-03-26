#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 998244353;
ll Pow(ll a, ll k) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = ans * a % mod;
        k >>= 1; a = a * a % mod;
    }
    return ans;
}

const int L = 105, M = 233333;
ll a[L][L];
ll gauss(int n, int m) {
    ll inv, del, ans = 1;
    int r, c;
    for(r = 0, c = 0; c < m; ++c) {
        int sig = -1;
        for(int i = r; i < n; ++i) 
            if(a[i][c]) {
                sig = i; break;
            }
        if(sig == -1) continue; // 空列
        if(sig != r) swap(a[sig], a[r]);
        ans = ans * a[r][c] % mod;
        inv = Pow(a[r][c], mod - 2);
        for(int i = 0; i < n; ++i) {
            if(i == r) continue;
            del = inv * a[i][c] % mod;
            for(int j = c; j <= m; ++j) a[i][j] = (a[i][j] - del * a[r][j] % mod) % mod; 
        }
        ++r;
    }
    if(r < n) ans = 0;
    return ans;
}

struct Edge {
    int u, v, w;
} e[M];
int main() {
    int T, n, m, u, v, w;
    ll ans = 0, sum, cur;
    cin >> T;
    while(T--) {
        scanf("%d %d", &n, &m);
        for(int i = 1; i <= m; ++i) {
            scanf("%d %d %d", &e[i].u, &e[i].v, &e[i].w);
            e[i].u--; e[i].v--;
        }
        // 总生成树个数
        sum = 0;
        for(int i = 0; i <= n; ++i) 
            for(int j = 0; j <= n; ++j)
                a[i][j] = 0;
        for(int i = 1; i <= m; ++i) {
            u = e[i].u; v = e[i].v;
            a[u][u]++; a[v][v]++;
            a[u][v]--; a[v][u]--;
        }
        sum = gauss(n-1,n-1);

        // 分别计数
        ans = 0;
        for(int b = 0; b < 30; ++b) {
            for(int i = 0; i <= n; ++i) 
                for(int j = 0; j <= n; ++j)
                    a[i][j] = 0;
            for(int i = 1; i <= m; ++i) {
                if(e[i].w&(1<<b)) {
                    u = e[i].u; v = e[i].v;
                    a[u][u]++; a[v][v]++;
                    a[u][v]--; a[v][u]--;
                }
            }
            cur = gauss(n-1,n-1);
            ans = (ans + cur * (1ll<<b) % mod) % mod;
        }
        ans = ans * Pow(sum, mod-2) % mod;
        printf("%lld\n", (ans+mod)%mod);
    }
}
