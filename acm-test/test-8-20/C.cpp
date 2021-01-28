#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;

const int N = 233333;

int mm[N];
int dp[N][25];
int dp2[N][25];
int a[N];
void initrmq(int n) {
    mm[0] = -1;
    for(int i = 1; i <= n; i++) {
        if(i & (i - 1)) mm[i] = mm[i - 1];
        else mm[i] = mm[i - 1] + 1;
    }

    for(int i = 1; i <= n; i++) {
        dp[i][0] = a[i];
        dp2[i][0] = a[i];
    }

    for(int k = 1; k <= 20; k++) {
        for(int i = 1; i <= n; i++) {
            if((i + (1 << k)) > (n + 1)) break;
            dp[i][k] = min(dp[i][k - 1], dp[i + (1 << (k - 1))][k - 1]);
            dp2[i][k] = max(dp2[i][k - 1], dp2[i + (1 << (k - 1))][k - 1]);
        }
    }
}

int rmq(int l, int r) {
    int k = mm[r - l + 1];
    return max(dp2[l][k], dp2[r + 1 - (1 << k)][k]) - min(dp[l][k], dp[r + 1 - (1 << k)][k]);
}

int main()
{
    int n, q;
    cin >> n >> q;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    initrmq(n);
    int l, r;
    for(int i = 1; i <= q; i++) {
        scanf("%d %d", &l, &r);
        printf("%d\n", rmq(l, r));
    }
}