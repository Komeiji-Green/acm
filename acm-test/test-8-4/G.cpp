#include<iostream>
#include<algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;
int dp[10005];
int p[505];
int w[505];

void init()
{
    dp[0] = 0;
    for(int i = 1; i < 10005; i++)
        dp[i] = INF;
}

int main()
{
    int T;
    cin >> T;
    while(T--) {
        int E,F;
        cin >> E >> F;
        int W = F - E;
        int n;
        cin >> n;
        for(int i = 1; i <= n; i++)
            scanf("%d %d", &p[i], &w[i]);

        init();
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= W; j++)
                if(j - w[i] >= 0) {
                    dp[j] = min(dp[j - w[i]] + p[i], dp[j]);
                }
        if(dp[W] == INF)
            printf("This is impossible.\n");
        else
            printf("The minimum amount of money in the piggy-bank is %d.\n", dp[W]);
    }
}