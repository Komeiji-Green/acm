#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxn = 5050;
ll dp[maxn][maxn];

char s[maxn], t[maxn];
int main() {
    int n, m;
    cin >> n >> m;
    scanf("%s", s + 1);
    scanf("%s", t + 1);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(s[i] == t[j]) {
                dp[i][j] = max(dp[i-1][j-1], 0ll) + 2;
            } else {
                dp[i][j] = max(max(dp[i][j-1], dp[i-1][j]) - 1, 0ll);
            }
        }
    }
    ll ans = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            ans = max(ans, dp[i][j]);
        }
    }
    cout << ans << endl;
}