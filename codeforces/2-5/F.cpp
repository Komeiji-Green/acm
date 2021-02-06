#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 100005;
vector<int> ch[maxn], vec[maxn];
int a[maxn], h[maxn], maxd;
int leaf[maxn];
void dfs(int x, int d) {
    h[x] = d; vec[d].push_back(x);
    a[d]++; maxd = max(maxd, d);
    //printf("%d: ", x); for(auto y : ch[x]) printf("%d ", y); printf("\n");
    for(auto y : ch[x]) {
        dfs(y, d + 1);
    }
    if(ch[x].size() == 0) leaf[x] = 1;
}

int big[512], cnt[512];
bool dp[350][maxn], tag[350][maxn]; int dp2[350][maxn];
int vis[maxn]; int vis2[512];
char ans[maxn];
int main() {
    int n, x;
    cin >> n >> x;
    for(int i = 2, p; i <= n; ++i){
        scanf("%d", &p);
        ch[p].push_back(i);
    }
    dfs(1, 1);
    int sq = 1, num = 0;
    for(sq = 1; sq * sq < n; ++sq);
    for(int i = 1; i <= maxd; ++i) {
        if(a[i] >= sq) {
            big[++num] = i;
        } else if(a[i] > 0) {
            cnt[a[i]]++;
        }
    }
    dp[0][0] = 1;
    for(int i = 1; i <= num; ++i) {
        int w = a[big[i]];
        int res;
        for(int j = 0; j <= n; ++j) {
            res = 0;
            if(dp[i-1][j]) res = 1;
            if(j >= w && dp[i-1][j-w]) res = 1, tag[i][j] = 1;
            dp[i][j] = res;
        }
    }
    for(int i = 0; i < sq; ++i) for(int j = 0; j <= n; ++j) dp2[i][j] = -1;
    dp2[0][0] = 0;
    for(int i = 1; i < sq; ++i) {
        for(int j = 0; j <= n; ++j) {
            if(dp2[i-1][j] != -1) {
                dp2[i][j] = 0;
            } else if(j >= i && dp2[i][j-i] != -1) {
                dp2[i][j] = dp2[i][j-i] + 1;
                if(dp2[i][j] > cnt[i]) dp2[i][j] = -1;
            }
        }
    }
    bool f = 0;
    int k;
    for(k = 0; k <= x; ++k) {
        if(dp[num][k] && dp2[sq-1][x-k]!=-1) {
            f = 1; break;
        }
    }
    if(f) {
        for(int i = num, w = k; i >= 1; --i) {
            //printf("i:%d w:%d\n", i, w);
            if(tag[i][w]) w -= a[big[i]], vis[big[i]] = 1;
        }
        for(int i = sq - 1, w = x - k; i >= 1; --i) {
            vis2[i] = dp2[i][w];
            w -= dp2[i][w] * i;
        }
        for(int i = 1; i <= maxd; ++i) {
            if(a[i] < sq) {
                if(vis2[a[i]]) vis[i] = 1, vis2[a[i]]--; // 哪层被选中了
            }
        }
        for(int i = 1; i <= n; ++i) {
            if(vis[h[i]]) ans[i] = 'a';
            else ans[i] = 'b';
        }
        printf("%d\n", maxd);
    } else {
        int m = n, y = x;
        for(int i = 1; i <= maxd; ++i) {
            if(a[i] <= y) {
                for(auto u : vec[i]) ans[u] = 'a';
                y -= a[i];
            } else if(a[i] <= m - y) {
                for(auto u : vec[i]) ans[u] = 'b';
            } else { // m - a[i] < m - y, m - a[i] < y
                for(int j = i + 1; j <= maxd; ++j) {
                    for(auto u : vec[j]) ans[u] = 'b';
                }
                for(auto u : vec[i]) if(!leaf[u]) ans[u] = 'a', --y;
                for(auto u : vec[i]) {
                    if(leaf[u]) {
                        if(y) ans[u] = 'a', --y;
                        else ans[u] = 'b';
                    }
                }
                break;
            }
            m -= a[i];
        }
        printf("%d\n", maxd+1);
    }

    //printf("tag: %d\n", f);
    ans[n+1] = '\0';
    printf("%s\n", ans + 1);
    /*
    for(int i = 0; i < sq; ++i) {
        printf("%d: ", i);
        for(int j = 0; j <= n; ++j) {
            printf("%d ", dp2[i][j]);
        }
        printf("\n");
    }
    printf("dp2:\n");
    for(int i = 0; i <= num; ++i) {
        printf("%d: ", i);
        for(int j = 0; j <= n; ++j) {
            printf("(%d, %d) ", dp[i][j], tag[i][j]);
        }
        printf("\n");
    }
    */
    //for(int i = 1; i <= maxd; ++i) printf("%d: %d\n", i, a[i]);
    //for(int i = 1; i <= maxd; ++i) printf("%d: %d\n", i, vis[i]);
    //for(int i = 1; i <= n; ++i) printf("%d: %d\n", i, h[i]);
    
    
}