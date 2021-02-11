#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 100007;

char s[maxn], t[maxn];
int nxt[maxn][26];
int dp[maxn][25][25];
void chk(int &x, int y) {
    if(x > y) x = y;
}
int main() {
    int T;
    cin >>  T;
    while(T-- ){
        scanf("%s %s", s + 1, t + 1);
        int n = strlen(s + 1), m = strlen(t + 1);
        for(int i = 0; i < 26; ++i) nxt[n + 1][i] = n + 1;
        for(int i = n; i >= 1; --i) {
            for(int j = 0; j < 26; ++j) {
                if(j == s[i]-'a') nxt[i][j]=i;
                else nxt[i][j]=nxt[i+1][j];
            }
        }
        for(int l = 1; l <= n; ++l) {
            for(int j = 0; j <= m; ++j) {
                dp[l][j][0] = l-1;
                for(int k = 1; k <= m; ++k) {
                    dp[l][j][k] = n + 1;
                    if(j >= 1 && dp[l][j-1][k] <= n) chk(dp[l][j][k], dp[l][j-1][k]);
                    if(j >= 1 && dp[l][j-1][k-1] <= n) chk(dp[l][j][k], nxt[dp[l][j-1][k-1]+1][t[j]-'a']);
                }
            }
        }
        //printf("test: %d\n", nxt[4]['w'-'a']);
        /*for(int l = 1; l <= n; ++l) {
            for(int j = 0; j <= m; ++j) {
                printf("%d: ",j);
                for(int k = 0; k <= m; ++k) {
                    printf("%d ", dp[l][j][k]);
                }
                printf("\n");
            }
            printf("\n\n");
        }*/
        int q; cin >> q;
        while(q--) {
            int l, r;
            scanf("%d %d", &l, &r);
            int lcs = upper_bound(dp[l][m], dp[l][m] + m + 1, r) - dp[l][m];
            --lcs;
            int ans = (r-l+1)+m-2*lcs;
            printf("%d\n", ans);

        }
    }
}