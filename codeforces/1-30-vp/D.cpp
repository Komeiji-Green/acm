#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int dp[2][1<<10];
char s[300030][10];
vector<int> link[300030];
int sg[300030];
int ans[300030];
int main() {
    int n;
    cin >> n;
    int st = 0;
    const int M = (1<<8);
    for(int i = 0; i < M; ++i) {
        dp[st][i] = (i&1);
    }
    ans[1] = 2;
    scanf("%s", s[1]);
    for(int i = 2; i <= n; ++i) {
        scanf("%s", s[i]);
        for(int j = i - 8; j < i; ++j) {
            if(j <= 0) continue;
            int cnt = 0;
            for(int k = 0; k < 8; ++k) {
                if(s[i][k] == s[j][k]) ++cnt;
            }
            if(i - j <= cnt) {
                link[j].push_back(i);
            }
        }
        int bit = 0;
        sg[i] = 0;
        for(int x = i - 1; x >= i - 8; --x) {
            if(x <= 0)  continue;
            sg[x] = 0;
            for(auto y : link[x]) {
                if(!sg[y]) sg[x] = 1, bit |= (1 << (i - 1 - x));
            }
        }
        ans[i] = 2 - dp[st][bit];
        for(int j = 0; j < M; ++j) {
            for(int b = 0; b < 8; ++b) {
                sg[i - b] = ((1 << b) & j);
            }
            int hb = 0;
            int x = i - 8;
            if(x > 0) {
                for(auto y : link[x]) {
                    if(!sg[y]) hb = 1;
                }
            }
            int k = ((j >> 1) | (hb << 7));
            dp[st^1][j] = dp[st][k];
        }
        st ^= 1;
    }
    for(int i= 1; i <= n; ++i) printf("%d", ans[i]);
    printf("\n");
}