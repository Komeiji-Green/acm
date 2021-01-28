#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;

const int N = 233333;

int mm[N];
int dp[N][25];  // 最大出现次数
int pre[N];   // 表示第i大的数(去重)的最先出现的位置
int pos[N];
int a[N];   // 第i大的数出现了多少次
int num = 0;
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
            dp[i][k] = max(dp[i][k - 1], dp[i + (1 << (k - 1))][k - 1]);
        }
    }
}

int rmq(int l, int r) {
    if(l > r) return 0;
    int k = mm[r - l + 1];
    return max(dp[l][k], dp[r + 1 - (1 << k)][k]);
}

int main()
{
    int n, q;
    while(scanf("%d", &n) != EOF && n != 0) {
        scanf("%d", &q);

        int x, cur;
        scanf("%d", &x);
        cur = x; num = 1;
        pre[1] = 1; a[1] = 1; pos[1] = 1;
        for(int i = 2; i <= n; i++) {
            scanf("%d", &x);
            if(x == cur) {
                a[num]++;
            } else {
                num++;
                a[num] = 1;
                pre[num] = i;
                cur = x;
            }
            pos[i] = num;
        }
        
        initrmq(num);

        int l, r;
        for(int i = 1; i <= q; i++) {
            scanf("%d %d", &l, &r);
            int minp = pos[l];
            int maxp = pos[r];
            if(minp == maxp) {
                printf("%d\n", r - l + 1);
            } else {
                int c1 = pre[minp] + a[minp] - l;
                int c2 = r - pre[maxp] + 1;
                int c3 = rmq(minp + 1, maxp - 1);
                int ans = max(c1, max(c2, c3));
                printf("%d\n", ans);
            }
        }
    }
}