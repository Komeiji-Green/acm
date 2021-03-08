#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1000007;
ll a[maxn], dp[maxn];
int pos[maxn][61];
int main() {
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j <= 60; ++j) pos[i][j] = pos[i-1][j];
        for(int j = 0; j <= 60; ++j) {
            if((1ll<<j) & a[i]) pos[i][j] = i;
        }
    }
    for(int i = 1; i <= n; ++i) {
        dp[i] = 0;
        for(int j = 0, x; j <= 60; ++j) {
            x = pos[i-1][j];
            dp[i] = max(dp[i], dp[x] + (a[i] & a[x]));
        }
    }
    ll ans = 0;
    for(int i = 0; i <= n; ++i) {
        ans = max(ans, dp[i]);
    }
    printf("%lld\n", ans);
}