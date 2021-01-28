#include <iostream>
#include <algorithm>
using namespace std;

#define rep(i, a, b) for(int i = (a); i <= (b); i++)

const int N = 105;

int dp[N][11][11][11];   
// dp(i, j) 表示前i个数，选j组，最大值
// dp[i][j] = max(dp[i-1][j] + max(0, a[1][i]), dp[i-1][j-1] + a[1][i])
// dp(i, j) 表示前i列，选j个长为2的矩阵，上方选k个长为1的矩阵，下方选l个长为1的矩阵，最大值
// 如果第i列两个数属于一个长度为2的矩阵，则可以1.加入原有矩阵，2.自成一个矩阵
// dp(i, j, k) = max( dp(i-1, j, k) + max(0, a[1][i] + a[2][i] , dp(i-1, j-1, k) + a[1][i] + a[2][i])
// 否则，第i列两个数独立，分别都可能1.加入原有矩阵 2.自成一个矩阵
// dp(i, j, k, l) = max( dp(i-1, j, k) + max(0, a[1][i]) , dp(i-1, j, k-1) + a[1][i])

int a[N][N];
int main()
{
    int n, m, t;
    cin >> n >> m >> t;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            scanf("%d", a[j][i]);
        }
    }

    dp[1][0] = 0;
    dp[1][1] = max(0, a[1][1]);
    for(int i = 2; i <= k; i++) {
        dp[1][k] = -1;
    }
    for(int i = 2; i <= n; i++) {
        dp[i][0] = 0;
        for(int j = 1; j <= k; j++) {
            dp[i][j] = max(
                dp[i-1][j] >= 0 ? dp[i-1][j] + max(0, a[1][i]) : -1,
                dp[i-1][j-1] >= 0 ? dp[i-1][j-1] + a[1][i] : -1
            );
        }
    }

    // dp(i, j, k, l) 表示前i列，选j个长为2的矩阵，上方选k个长为1的矩阵，下方选l个长为1的矩阵，最大值
    rep(i, 0, n) rep(j, 0, t) rep(k, 0, t) rep(l, 0, t) {
        dp[i][j][k][l] = -1;
    }
    dp[0][0][0][0] = 0;
    rep(i, 1, n) rep(j, 0, t) rep(k, 0, t) rep(l, 0, t) {
        if(j == 0 && k == 0 && l == 0) dp[i][j][k][l] = 0;
        else {
            dp[i][j][k][l] = max(
                j > 0 ? max(
                    dp[i-1][j][k][l] >= 0 ? dp[i-1][j][k][l] + max(0, a[1][i] + a[2][i]) : -1,
                    dp[i-1][j-1][k][l] >= 0 ? dp[i-1][j-1][k][l] + a[1][i] + a[2][i] : -1
                ) : -1,
                k > 0 ? max(
                    dp[i-1][j][k-1][l] >= 0 ? dp[i-1][j][k-1][l] + max(0, a[1][i])
                )
            )
        }
    }


}