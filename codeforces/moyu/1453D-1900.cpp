#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

// 期望dp式子: dp[i] / 2 = dp[j] / 2 + 2^k - 1; 
int ans[2005]; int tot;
ll c[100];
int main() {
    int T; cin >> T;
    ll k;
    for(ll i = 1; i <= 63; ++i) {
        c[i] = (1ll<<i) - 1ll;
    }
    while(T--) {
        scanf("%lld", &k);
        tot = 0;
        if(k&1) {
            printf("-1\n"); continue;
        }
        k >>= 1;
        while(k) {
            for(int i = 63; i >= 1; --i) {
                if(c[i] <= k) {
                    ans[++tot] = i;
                    k -= c[i];
                }
            }
        }
        int len = 0;
        for(int i = 1; i <= tot; ++i) len += ans[i];
        printf("%d\n", len);
        for(int i = 1; i <= tot; ++i) {
            printf("%d ", 1);
            for(int j = 2; j <= ans[i]; ++j) printf("%d ", 0);
        }
        printf("\n");
    }
}