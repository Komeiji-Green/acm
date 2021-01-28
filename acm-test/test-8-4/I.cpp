#include<iostream>
#include<algorithm>
using namespace std;

int a[120][120];
int dp[120][120];
int main()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= i; j++)
            scanf("%d", &a[i][j]);

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= i; j++)
            dp[i][j] = max(dp[i - 1][j - 1], dp[i - 1][j]) + a[i][j];
    
    int ans = 0;
    for(int j = 1; j <= n; j++)
        ans = max(dp[n][j], ans);

    cout << ans << endl;
}