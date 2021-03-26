#pragma optimize(2)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2005, M = 1000010;
const ll mod = 1e9 + 7;

vector<int> G[N];
int a[N], n, m, cnt;
int rk[M], kth[M], vis[N], rt, sum;
ll dp[N][4005];
void add(ll &x, ll y) {
    x = (x + y) % mod;
}

ll ans = 0;
namespace DFS {
    int dfn[N], wh[N], siz[N], clc;
    void dfs(int x, int dad) {
        siz[x] = 1;
        for(auto y : G[x]) {
            if(y == dad || vis[y]) continue;
            dfs(y, x); siz[x] += siz[y];
        }
        ++clc;
        dfn[x] = clc; wh[clc] = x;
    }
    ll gao() {
        dfs(rt, 0);
        int n;
        for(int i = 1; i <= clc; ++i)
            for(int j = 1; j <= cnt; ++j)
                dp[i][j] = 0;
        ll nex, res = 0;
        for(int i = 1, j, k, x, y, z; i <= clc; ++i) {
            // z ---> x -> y
            // k ---> i -> j
            x = wh[i];
            j = i + 1; k = i - siz[x];
            y = wh[j]; z = wh[k];
            //printf("%d %d:\n", i, x);
            if(m/a[x] > 0) {
                add(dp[i][rk[m/a[x]]], 1);
                //printf("dp[%d][%d] += 1\n", x, m/a[x]);
            }
            for(int jj = 1; jj <= cnt; ++jj) {
                add(dp[i][jj], dp[k][jj]);
               // printf("dp[%d][%d] += dp[%d][%d] = %lld\n", wh[i], kth[jj], wh[k], kth[jj], dp[k][jj]);
            }
            if(i < clc) {
                for(int jj = 1; jj <= cnt; ++jj) {
                    nex = kth[jj] / a[y];
                    if(nex > 0) {
                        add(dp[j][rk[nex]], dp[i][jj]);   
                        //printf("dp[%d][%d] += dp[%d][%d] = %lld\n", wh[j], kth[rk[nex]], wh[i], kth[jj], dp[i][jj]);
                    }
                }
            }
            //printf("\n\n"); 
        }
        /*for(int i = 1, x; i <= n; ++i) {
            x = wh[i];
            add(dp[x][rk[m]], 1);
            for(int j = 1; j <= cnt; ++j) {
                // 先更新x
                
                add(dp[x][j], dp[wh[i-siz[x]]][j]);
                if(i < n) {
                    ll nex = kth[j]/a[wh[i+1]];
                    //cerr << " " << rk[nex] << endl;
                    if(nex > 0) add(dp[wh[i+1]][rk[nex]], dp[x][j]);
                }
            }
        }*/
        for(int i = 1; i <= cnt; ++i) {
            add(res, dp[clc][i]);
        }
        //printf("res: %lld\n", res);
        return res;
    }
}

namespace DFZ {
    int siz[N], mx[N];
    void getsz(int x, int dad) {
        mx[x] = 0; siz[x] = 1;
        for(auto y : G[x]) {
            if(y == dad || vis[y]) continue;
            getsz(y, x);
            siz[x] += siz[y]; mx[x] = max(mx[x], siz[y]);
        }
        mx[x] = max(mx[x], sum - siz[x]);
        if(mx[x] < mx[rt]) rt = x;
    }

    void dfz(int x) {
        //printf("%d\n", x);
        getsz(x, 0); vis[rt] = 1;

        //printf("cent: %d\n\n", rt);
        DFS::clc = 0;
        add(ans, DFS::gao());

        int tmp = rt, psum = sum;
        for(auto y : G[tmp]) {
            if(vis[y]) continue;
            rt = tmp;
            sum = (siz[y] > siz[tmp] ? psum - siz[tmp] : siz[y]);
            dfz(y);
        }
    }
} 

int main() {
    int T;
    cin >> T;
    while(T--) {
        scanf("%d %d", &n, &m);
        for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
        for(int i = 1; i <= n; ++i) G[i].clear();
        for(int i = 2, u, v; i <= n; ++i) {
            scanf("%d %d", &u, &v);
            G[u].push_back(v); G[v].push_back(u);
        }

        cnt = 0;
        for(int i = 1, j; i <= m; i = j + 1) {
            j = m / (m / i); ++cnt;
            rk[m/i] = cnt;
            kth[cnt] = m/i;
        }

        // dfz
        using namespace DFZ;
        rt = 0; sum = n; mx[0] = n + 1;
        for(int i = 1; i <= n; ++i) vis[i] = 0;
        ans = 0;
        dfz(1);
        printf("%lld\n", (ans+mod)%mod);
    }
}