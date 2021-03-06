#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
ll a[maxn], dp[maxn];
int main() {
    int T, n;
    cin >> T;
    ll k;
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
        dp[1] = 0;
        for(int i = 2; i <= n; ++i) {
            dp[i] = dp[i-1];
            if(a[i] < a[i-1]) dp[i] += (a[i-1] - a[i]);
        }
        printf("%lld\n", dp[n]);
    }
}