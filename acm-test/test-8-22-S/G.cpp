#include<iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 140;
int a[3][N];

int dp[N][15][5];   
int main()
{
    for(int i = 2; i <= n; i++) {
        for(int j = 0; j <= k; j++) {
            dp[i][j][0] = j == 0 ? 0 : -1;
            dp[i][j][1] = max(
                dp[i][j][1] >= 0 ? dp[i][j][1] + a[i][1] : -1,
                dp[i][j-1][0] >= 0 ? dp[i][j-1][0] + a[i][1] : -1,
                dp[i][j][1] >= 0 ? dp[i][j][1] : -1
            );
            dp[i][j][2] = max(
                dp[i][j][2] >= 0 ? dp[i][j][2] + a[i][2] : -1,
                dp[i][j-1][0] >= 0 ? dp[i][j-1][0] + a[i][2] : -1,
                dp[i][j][2] >= 0 ? dp[i][j][2] : -1
            );
            dp[i][j][3] = max(
                dp[i][j][3] >= 0 ? dp[i][j][3] + max(a[i][1], 0) : -1,
            )
        }
    }
}