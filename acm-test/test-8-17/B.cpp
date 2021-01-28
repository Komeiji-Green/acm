#include<iostream>
#include <cstring>
#include <cstdio>
using namespace std;

#define rep(i, a, b) for(int i = (a); i <= (b); i++)

int dp[105][105];

char s[105];
int main()
{
    while(scanf("%s", s) != EOF && s[0] != 'e') {
        memset(dp, 0, sizeof(dp));
        int len = strlen(s);
        rep(d, 1, len - 1) {
            rep(l, 0, len - 1) {
                int r = l + d;
                if(r < len) {
                    if(s[l] == '(' && s[r] == ')' || s[l] == '[' && s[r] == ']') {
                        dp[l][r] = max(dp[l][r], 2 + dp[l + 1][r - 1]);
                    }
                    rep(k, l, r - 1) {
                        dp[l][r] = max(dp[l][r], dp[l][k] + dp[k + 1][r]);
                    }
                }
            }
        }

        printf("%d\n", dp[0][len - 1]);
    }
}