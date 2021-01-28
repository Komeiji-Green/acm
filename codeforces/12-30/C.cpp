#include<bits/stdc++.h>
using namespace std;
const int maxn  = 100010, inf = 0x3f3f3f3f;
char s[maxn];
int a[maxn];
int dp[2][27][27];
int main() {
    int T;
    cin >> T;
    while(T--) {
        scanf("%s", s);
        int n = strlen(s);
        for(int i = 0; i < n; ++i) a[i] = s[i] - 'a';
        if(n <= 1) {
            printf("0\n");
        } else {
            for(int i = 0; i < 26; ++i) {
                for(int j = 0; j < 26; ++j) {
                    if(i == j) dp[1][i][j] = inf;
                    else dp[1][i][j] = (a[0] != i) + (a[1] != j);
                }
            }
            int k = 1;
            for(int uu = 2; uu < n; ++uu) {
                int m1, m2;
                for(int j = 0; j < 26; ++j) {
                    m1 = m2 = inf;
                    for(int i = 0; i < 26; ++i) {
                        if(dp[k][i][j] < m1) {
                            m2 = m1; m1 = dp[k][i][j];
                        } else if(dp[k][i][j] < m2) {
                            m2 = dp[k][i][j];
                        }
                    }
                    for(int i = 0; i < 26; ++i) {
                        if(i == j) dp[k^1][j][i] = inf;
                        else if(dp[k][i][j] == m1) {
                            dp[k^1][j][i] = m2 + (a[uu]!=i);
                        } else {
                            dp[k^1][j][i] = m1 + (a[uu]!=i);
                        }
                    }
                }
                k^=1;
            }
            int ans = inf;
            for(int i = 0; i < 26; ++i) {
                for(int j = 0; j < 26; ++j) {
                    ans = min(dp[k][i][j], ans);
                }
            }
            printf("%d\n", ans);
        }
    }
}
/*kksk*/