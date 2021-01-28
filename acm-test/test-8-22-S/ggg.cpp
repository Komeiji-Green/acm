#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

#define rep(i, a, b) for(int i = (a); i <= (b); i++)

const int N = 105;

int dp[N][N][15];   // 考虑：第一行前i个数，第2行前j个数，选了k个矩阵
// 分情况：考虑最后一列的某个数，
// 如果i != j
// 如果它不在某个矩阵中或在某个矩阵中且并非自成一组，dp[i][j][k] = dp[i-1][j][k] + max(0, a[1][i])
// 如果它自成一个矩阵，dp[i][j][k] = dp[i-1][j][k-1] + a[1][i];
// 如果i == j，那么在上述情况的基础上，还有：
// 如果它属于某个高度为2的矩阵且这一列不自成一组，dp[i][j][k] = dp[i-1][j-1][k] + max(0, a[1][i] + a[2][i])
// 如果这一列自成某个高度为2的矩阵，dp[i][j][k] = dp[i-1][j-1][k-1] + a[1][i] + a[2][i]
int a[N][N];

int main()
{
    int n, m, t;
    cin >> n >> m >> t;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            scanf("%d", &a[j][i]);
        }
    } 
    
    if(m == 1) {
        dp[1][1][0] = 0;
        dp[1][1][1] = max(0, a[1][1]);
        rep(k, 2, t) dp[1][1][k] = -1;
        rep(i, 2, n) {
            dp[i][1][0] = 0;
            rep(k, 1, t) {
                dp[i][1][k] = max(
                    (dp[i-1][1][k-1] >= 0 ? dp[i-1][1][k-1] + a[1][i] : -1),
                    (dp[i-1][1][k] >= 0 ? dp[i-1][1][k] + max(0, a[1][i]) : -1)
                );
            }
        }
        printf("%d\n", dp[n][1][t]);
    } else if(m == 2) {
        dp[1][1][0] = 0;
        dp[1][1][1] = max(max(a[1][1], a[2][1]), a[1][1] + a[2][1]);
        dp[1][1][2] = a[1][1] + a[2][1];
        rep(k, 3, t) dp[1][1][k] = -1;
        rep(i, 1, n) rep(j, 1, n) {
            if(i == 1 && j == 1) continue;
            dp[i][j][0] = 0;
            rep(k, 1, t) {
                int ans = -1;
                if(i == 1) {
                    ans = max(
                        (dp[i][j-1][k-1] >= 0 ? dp[i][j-1][k-1] + a[2][j] : -1),
                        (dp[i][j-1][k] >= 0 ? dp[i][j-1][k] + max(0, a[2][j]) : -1)
                    );
                } else {
                    ans = max(
                        (dp[i-1][j][k-1] >= 0 ? dp[i-1][j][k-1] + a[1][i] : -1),
                        (dp[i-1][j][k] >= 0 ? dp[i-1][j][k] + max(0, a[1][i]) : -1)
                    );
                }
                if(i == j) {
                    ans = max(
                        ans, max(
                            (dp[i-1][j-1][k-1] >= 0 ? dp[i-1][j-1][k-1] + a[1][i] + a[2][j] : -1),
                            (dp[i-1][j-1][k] >= 0 ? dp[i-1][j-1][k] + max(0, a[1][i] + a[2][j]) : -1)
                        )
                    );
                }
                dp[i][j][k] = ans;
            }
        }
        printf("%d\n", dp[n][n][t]);
    }
    
}