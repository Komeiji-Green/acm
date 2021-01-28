#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const ll INF = 2147483647;

#define rep(i, a, b) for (int i = a; i <= b; i++)
const int maxn = 100 + 5;
ll G[maxn][maxn];
ll dis[maxn][maxn]; 
// 在第k次循环前，dis[i][j]表示从i到j且中途经过点[1, k)的最短路径
// 每次循环开始时，我们更新minCircle的答案，即更新：有一点为k，全部点均位于[1, k]中的最小环


int n, m;

int floyd()
{
    rep(i, 1, n) rep(j, 1, n) {
        dis[i][j] = G[i][j];
    }

    ll minCircle = INF;
    rep(k, 1, n) {
        rep(i, 1, k - 1)
            rep(j, 1, k - 1) {
                if(G[i][k] == 0 || G[k][j] == 0) continue;
                minCircle = min(minCircle, G[i][k] + G[k][j] + dis[i][j]);
            }
        rep(i, 1, n)
            rep(j, 1, n) {
                //if(i == j || i == k || k == j) continue;
                //if(dis[i][j] == -1) dis[i][j] = dis[i][k] + dis[k][j];
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
    }

    return minCircle;
}


int main()
{
    int T;
    cin >> T;
    while(T--) {
        cin >> n >> m;
        rep(i, 1, m) {
            
        }
    }

    while(scanf("%d", &n) != EOF) {
        scanf("%d", &m);
        
        rep(i, 1, n) rep(j, 1, n) {
            if(i == j) G[i][j] = 0;
            else G[i][j] = INF;
        }
    
        int u, v;
        ll w;
        rep(i, 1, m) {
            scanf("%d %d %lld", &u, &v, &w);
            G[u][v] = (G[u][v] ? min(G[u][v], w) : w);
            G[v][u] = G[u][v];
        }
        ll ans = floyd();
        if(ans == INF)
            cout << "It's impossible." << endl;
        else 
            cout << ans << endl;
    }
}

rep(i, 0, n) {
    rep(j, 0, n) {
        reg(k, j) {
            dp[i + 1][e[k].to] = max(dp[i + 1][e[k].to], dp[i][j] + M[j]);
        }
    }
}