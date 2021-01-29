#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 233333;
ll a[maxn], b[maxn], c[maxn], dp[maxn];

int main() {
    int T;
    int n, k;
    ll u, v;
    cin >> T;
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) scanf("%lld", &c[i]);
        //scanf("%lld", &u);
        for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);

        for(int i = 1; i <= n; ++i) scanf("%lld", &b[i]);
        /*ll cur = abs(a[1]-b[1]); ll ans = 0;
        for(int i = 2; i <= n; ++i) {
            if(i == n || a[i] == b[i]) {
                cur += 2 + c[i] - 1;
                ans = max(ans, cur);
                cur = 0;
            } else {
                cur += 2 + c[i] - 1 - abs(a[i] - b[i]);
            }
        }*/
        dp[1] = 0;
        for(int i = 2; i <= n; ++i) {
            if(a[i] == b[i]) dp[i] = 1 + c[i];
            else {
                dp[i] = 1 + c[i] + max(abs(a[i] - b[i]), dp[i-1] - abs(a[i] - b[i]));
            }
        }
        ll ans = 0;
        for(int i= 2; i <= n; ++i) ans = max(ans, dp[i]);
        printf("%lld\n", ans);
    }
}