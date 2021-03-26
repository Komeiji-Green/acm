#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

double dp[100][100];
int main() {
    int n = 10;
    for(int j = 1; j <= n; ++j) dp[1][j] = 2 * j;
    for(int i = 2; i <= n; ++i) {
        dp[i][i-1] = dp[i-1][i-1] + 1;
        for(int j = i; j <= n; ++j) {
            dp[i][j] = 0.5 * (dp[i-1][j] + dp[i][j-1]) + 1;
        }
    }
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            printf("%.5f ", dp[i][j]);
        }
        printf("\n");
    }
}