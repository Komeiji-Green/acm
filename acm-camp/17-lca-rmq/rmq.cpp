#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;

const int N = 233333;

int mm[N];
int dp[N][25];
int a[N];
void initrmq(int n) {
    mm[0] = -1;
    for(int i = 1; i <= n; i++) {
        if(i & (i - 1)) mm[i] = mm[i - 1];
        else mm[i] = mm[i - 1] + 1;
    }

    for(int i = 1; i <= n; i++) {
        dp[i][0] = a[i];
    }

    for(int k = 1; k <= 20; k++) {
        for(int i = 1; i <= n; i++) {
            if((i + (1 << k)) > (n + 1)) break;
            dp[i][k] = min(dp[i][k - 1], dp[i + (1 << (k - 1))][k - 1]);
        }
    }
}

int rmq(int l, int r) {
    int k = mm[r - l + 1];
    return min(dp[l][k], dp[r + 1 - (1 << k)][k]);
}

int main()
{
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    initrmq(n);
    for(int i = 1; i <= (n - m + 1); i++) {
        printf("%d\n", rmq(i, i + m - 1));
    }
}