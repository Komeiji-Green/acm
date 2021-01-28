#include<iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

#define rep(i, a, b) for(int i = (a); i <= (b); i++)

const ll INF = 0x3f3f3f3f3f3f3f3f;
const int N = 1006;

ll p[N];

// 反向dp
// dp[l][r][0/1] : 表示在区间[l, r]的左/右端点出发，去吃区间外的草，所得到的最小腐败值
// 这样的状态设置其实源于一个性质：牛总是先吃内圈的草，再吃外圈的草，于是吃过的草为一个连续区间
// 为什么不能正向dp？如果正向dp，下一次吃草的腐败度是过程状态
// 这种累加求和的最值题，往往是反向dp

ll dp[N][N][2];

int main()
{
    int n;
    ll L;
    cin >> n >> L;
    rep(i, 1, n) {
        scanf("%lld", &p[i]);
    }

    sort(p + 1, p + n + 1);

    int idx = 1;
    while(p[idx] <= L) idx++;
    for(int i = n; i >= idx; i--) {
        p[i + 1] = p[i];
    }
    p[idx] = L;
    
    n = n + 1;

    /*for(int i = 1; i <= n; i++) {
        printf("%lld ", p[i]);
    }
    printf("\n");*/

    for(int d = n - 2; d >= 0; d--) {
        for(int l = 1; l <= n; l++) {
            int r = l + d;
            int num = n - (r - l + 1);  // 剩余草的数量
            if(l >= 0 && l <= idx && r >= idx && r <= n) {
                dp[l][r][1] = min(
                    r + 1 <= n ? dp[l][r + 1][1] + num * (p[r + 1] - p[r]) : INF,
                    l - 1 >= 1 ? dp[l - 1][r][0] + num * (p[r] - p[l - 1]) : INF
                );
                dp[l][r][0] = min(
                    r + 1 <= n ? dp[l][r + 1][1] + num * (p[r + 1] - p[l]) : INF,
                    l - 1 >= 1 ? dp[l - 1][r][0] + num * (p[l] - p[l - 1]) : INF
                );
            }
        }
    }

    /*for(int d = n - 1; d >= 0; d--) {
        for(int l = 1; l <= n; l++) {
            int r = l + d;
            printf("%d %d: %lld %lld\n", l, r, dp[l][r][0], dp[l][r][1]);
        }
    }*/
    printf("%lld\n", dp[idx][idx][0]);
}