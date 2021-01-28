#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

#define rep(i, a, b) for(int i = (a); i <= (b); i++)

const int N = 105;

int dp[N][N][11];   // 第1行前i个数，第2行前j个数，共组成k个矩阵，最大值
// 先考虑只有第一行的情况，
// 对于第i个数，如果它自成一个矩阵，则dp[i][j][k] = dp[i][j][k-1] + a[i]
// 如果它与前面某个连续段组成矩阵，即属于[ix, i]矩阵，则dp[i][j][k] = max(dp[ix][j][k-1])
// 若两行都有
// 如果i!=j, 则只可能发生第一行的情况
// 如果i==j, 需要在i!=j情况的基础上加入考虑高度为2的矩阵的情况

int a[3][N];
int pre[3][N];

int main()
{
    int n, m, t;
    cin >> n >> m >> t;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            scanf("%d", &a[j][i]);
        }
    }

    pre[1][0] = pre[2][0] = 0;
    rep(j, 1, 2) {
        rep(i, 1, n) {
            pre[j][i] = pre[j][i-1] + a[j][i];
        }
    } 

    rep(i, 0, n) rep(j, 0, n) rep(k, 0, t) {
        dp[i][j][k] = -1;
    }
    dp[0][0][0] = 0;

    if(m == 1) {
        rep(i, 0, n) {
            dp[i][1][0] = 0;
            rep(k, 1, t) {
                rep(ix, 1, i) dp[i][1][k] = max(dp[i][1][k], dp[ix-1][1][k-1] >= 0 ? dp[ix-1][1][k-1] + pre[1][i] - pre[1][ix-1] : -1);
                if(i) dp[i][1][k] = max(dp[i][1][k], dp[i-1][1][k]);
            }
        }

        printf("%d\n", dp[n][1][t]);
    } else {
        rep(i, 0, n) rep(j, 0, n) {
            dp[i][j][0] = 0;
            rep(k, 1, t) {
                if(i >= j && i > 0) {
                    rep(ix, 1, i) dp[i][j][k] = max(dp[i][j][k], dp[ix-1][j][k-1] >= 0 ? dp[ix-1][j][k-1] + pre[1][i] - pre[1][ix-1] : -1);
                    dp[i][j][k] = max(dp[i][j][k], dp[i-1][j][k]);
                } 
                if (i <= j && j > 0) {
                    rep(iy, 1, j) dp[i][j][k] = max(dp[i][j][k], dp[i][iy-1][k-1] >= 0 ? dp[i][iy-1][k-1] + pre[2][j] - pre[2][iy-1] : -1);
                    dp[i][j][k] = max(dp[i][j][k], dp[i][j-1][k]);
                }
                if(i == j) {
                    rep(ix, 1, i) dp[i][j][k] = max(dp[i][j][k], dp[ix-1][ix-1][k-1] >= 0 ? dp[ix-1][ix-1][k-1] + pre[1][i] - pre[1][ix-1] + pre[2][j] - pre[2][ix-1] : -1);
                }
            }
        }
        printf("%d\n", dp[n][n][t]);
    }
}