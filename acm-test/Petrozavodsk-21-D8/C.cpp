#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

// dp[i] += dp[x] - dp[i^x], i^x < x < i;

const ll mod = 998244353;
const int N = 2333333;
ll dp[N], pre[N];
int main() {
    int n;
    cin >> n;
    dp[0] = 0; pre[0] = 0;
    for(int i = 1; i <= n; ++i) {
        int cnt = 0;
        dp[i] = (pre[i-1] + 1);
        for(int j = 20; j >= 0; --j) {
            if((1<<j) & i) {
                ++cnt;
                if(cnt == 1) {
                    //dp[i] = (dp[i] + (pre[i-1] - pre[(1<<j) - 1]) % mod) % mod;
                } else {
                    dp[i] = (dp[i] - (pre[(1<<(j+1))-1] - pre[(1<<j)-1]) % mod) % mod;
                }
            }
        }
        pre[i] = (pre[i-1] + dp[i]) % mod;
    }
    //for(int i = 1; i <= n; ++i) {
        //printf("%d: %lld\n", i, (dp[i] + mod) % mod);
    //}
    printf("%lld\n", (pre[n] + mod) % mod);
}