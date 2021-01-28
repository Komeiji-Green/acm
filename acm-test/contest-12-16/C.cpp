#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 1e9+7;
ll dp[33][2][2];
int bit[33];
int main() {
    int T;
    cin >> T;
    int x, y, hx, hy;
    bit[0] = 0;
    for(int i = 1; i <= 31; ++i) bit[i] = (1<<(i-1));
    while(T--) {
        scanf("%d %d", &x, &y);
        for(hx = 31; hx >= 1; --hx) if(bit[hx]&x) break;
        for(hy = 31; hy >= 1; --hy) if(bit[hy]&y) break;
        dp[0][0][0] = 1;
        for(int k = 1; k <= 31; ++k) {
            dp[k][0][0] = (dp[k-1][0][0]+dp[k-1][0][1]+dp[k-1][1][0])%mod;
            if(k < hx) {
                dp[k][1][0] = dp[k][0][0];
            } else if(k == hx) {
                int sum = 0;
                for(int i = k - 1; i >= 1; --i) {
                    if(bit[i]&x) {
                        dp[k][1][0] = (dp[k][1][0] + ((dp[i][0][0] + dp[i][0][1])%mod)*p2[sum]) 
                    } else {
                        ++sum;
                    }
                }
            }
            
        }
    }
}