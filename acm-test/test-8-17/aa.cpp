#include<iostream>
#include <cstring>
#include <cstdio>
using namespace std;

#define rep(i, a, b) for(int i = (a); i <= (b); i++)

const int N = 205;
int a[N];
int c[N];
int len[N];

int dp[N][N][N];
bool vis[N][N][N];

int n;

int solve(int i, int j, int k) {
    if(i == j) return (len[i] + k) * (len[i] + k);
    if(vis[i][j][k]) return dp[i][j][k];
    vis[i][j][k] = true;
    int maxv = 0;
    maxv = max(maxv, solve(i, j - 1, 0) + (len[j] + k) * (len[j] + k));
    rep(t, i, j - 1) {
        if(c[t] == c[j]) {
            maxv = max(maxv, solve(t + 1, j - 1, 0) + solve(i, t, len[j] + k));
        }
    }
    return dp[i][j][k] = maxv;
}

int main()
{
    int T;
    cin >> T;
    rep(tt, 1, T) {
        cin >> n;
        int num = 0;
        rep(i, 1, n) {
            scanf("%d", &a[i]);
            if(a[i] != a[i - 1]) {
                num++;
                c[num] = a[i];
                len[num] = 1;
            } else {
                len[num]++;
            }
        }

        memset(vis, 0, sizeof(vis));

        /*rep(d, 0, num - 1) {
            rep(l, 1, num) {
                int r = l + d;
                if(r <= num) {
                    rep(k, 0, n) {
                        int maxv = 0;
                        maxv = max(
                            maxv, 
                            r - 1 >= l ? 
                            dp[l][r - 1][0] + (len[r] + k) * (len[r] + k) :
                            (len[r] + k) * (len[r] + k)
                        );
                        rep(t, l, r - 1) {
                            if(c[t] == c[r]) {
                                maxv = max(
                                    maxv,
                                    dp[t + 1][r - 1][0] + dp[l][t][len[r] + k]
                                );
                            }
                        }
                        dp[l][r][k] = maxv;
                    }
                }
            }
        }*/

        /*rep(d, 0, num - 1) {
            rep(l, 1, num) {
                int r = l + d;
                rep(k, 0, n)
                    if(r <= num) {
                        printf("%d %d %d: %d\n", l, r, k, dp[l][r][k]);
                    }
            }
        }*/

        printf("Case %d: %d\n", tt, solve(1, num, 0));
    }
}