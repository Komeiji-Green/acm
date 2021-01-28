#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long ll;
#define rep(i, a, b) for(int i = (a); i <= (b); i++)

const ll INF = (1ll<<31) - 1;

int G[15][15];
ll dis[15][15];
int n;

// 有向图floyd
// floyd[i][j][k]: 从i到j的最短路径，满足除去i、j点外，只可以经过0 ~ k点
void floyd()
{
    rep(i, 0, n) rep(j, 0, n) {
        dis[i][j] = G[i][j];
    }

    rep(k, 0, n) {
        rep(i, 0, n)
            rep(j, 0, n) {
                //if(i == j || i == k || k == j) continue;
                //if(dis[i][j] == -1) dis[i][j] = dis[i][k] + dis[k][j];
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
    }
}

ll dp[1<<11][15];  // 人在i点，披萨剩余情况为state时的最优方案

int main()
{
    while(scanf("%d", &n) != EOF && n != 0) {
        for(int i = 0; i <= n; i++)
            for(int j = 0; j <= n; j++)
                scanf("%d", &G[i][j]);
        floyd();

        memset(dp, 0, sizeof(dp));
        for(int i = 0; i <= n; i++) {
            dp[0][i] = dis[i][0];
        }
        for(int st = 1; st < (1 << n); st++) {
            for(int i = 0; i <= n; i++) {
                dp[st][i] = INF;
                for(int j = 1; j <= n; j++) {
                    if((1 << (j - 1)) & st) {
                        dp[st][i] = min(
                            dp[st][i],
                            dp[st ^ (1 << (j - 1))][j] + dis[i][j]
                        );
                    }
                }
            }
        }
        printf("%lld\n", dp[(1<<n) - 1][0]);
    }
}