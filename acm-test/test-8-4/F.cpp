#include<iostream>
using namespace std;

const int maxn = 1000000 + 5;
int n, m;

int cnt[maxn];
int dp[maxn][3][3]; 
//状态子空间：[i - 1, i, i + 1] 有j个， [i, i + 1, i + 2] 有k个
//记录值：所有有前i个数出现的三元组个数的最大值。

int main()
{
    cin >> n >> m;
    for(int i = 1, x; i <= n; i++) {
        scanf("%d", &x);
        cnt[x]++;
    }

    for(int i = 1; i <= m; i++) {
        for(int j = 0; j <= 2; j++) {
            for(int k = 0; k <= 2; k++) {
                for(int l = 0; l <= 2; l++) {
                    if(j + k + l <= cnt[i])
                        dp[i][k][l] = max(dp[i][k][l], dp[i - 1][j][k] + l + (cnt[i] - j - k - l) / 3);
                        // 枚举j，逐j刷新，对j取完最值后，就完成了一次状态转移
                }
            }
        }
    }
    cout << dp[m][0][0] << endl;
}