#include<iostream>
#include <cstring>
#include <cstdio>
using namespace std;

#define rep(i, a, b) for(int i = (a); i <= (b); i++)

//合并区间[l, r]中的块，且留下k个与尾块同色的块，所获得的最大分数
int dp[205][205][205];

int a[205];

int main()
{
    int T;
    cin >> T;
    rep(tt, 1, T) {
        int n;
        cin >> n;
        rep(i, 1, n) {
            scanf("%d", &a[i]);
        }

        rep(i, 1, n) {
            dp[i][i][0] = 1;
            rep(k, 2, n) {
                dp[i][i][k] = -1;
            }
        }

        int m1, m2, m3;

        rep(d, 1, n - 1) {
            rep(l, 1, n) {
                int r = l + d;
                if(l >= 1 && r <= n) {
                    int max0 = 0;
                    rep(k, 1, n) {
                        int maxv = -1;
                        rep(t, l, r - 1) {
                            if(a[t] == a[r]) {
                                rep(j, 0, k) {
                                    m1 = dp[l][t][j];
                                    m2 = dp[t + 1][r][k - j];
                                    maxv = max(
                                        maxv,
                                        m1 >= 0 && m2 >= 0 ? m1 + m2 : -1
                                    );
                                }
                            } else {
                                m3 = dp[t + 1][r][k];
                                maxv = max(
                                    maxv,
                                    m3 >= 0 ? dp[l][t][0] + m3 : -1
                                );
                            }
                        }
                        dp[l][r][k] = maxv;
                        max0 = max(max0, maxv >= 0 ? maxv + k * k : -1);
                    }
                    dp[l][r][0] = max0;
                }
            }
        }

        /*rep(d, 0, n - 1) {
            rep(l, 1, n) {
                int r = l + d;
                if(l >= 1 && r <= n) {
                    rep(k, 0, 4) {
                        printf("%d %d %d: %d\n", l, r, k, dp[l][r][k]);
                    }
                }
            }
        }*/

        printf("Case %d: %d\n", tt, dp[1][n][0]);
    }
}