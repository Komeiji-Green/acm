#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

bool dp[25][25][5005];
int a[100], ans[5005];
char s[] = "11451419191145141919";
const int sz = 20;
int main() {
    freopen("ans.txt", "w", stdout);
    for(int i = 0; i < sz; ++i) {
        a[i+1] = s[i]-'0';
    }
    int val;
    for(int r = 1; r <= sz; ++r) {
        bool f = 1;
        for(int i = 1; i <= 5000; ++i) {
            if(!dp[1][r][i]) f = 0; 
        }
        if(f) break;
        for(int l = r; l >= 1; --l) {
            // no
            if(r-l+1<=4) {
                val = 0;
                for(int i = l; i <= r; ++i) {
                    val = 10 * val + a[i];
                }
                if(val <= 5000) dp[l][r][val] = 1;
            }

            // yes
            for(int i = l; i < r; ++i) {
                for(int j = 1; j <= 5000; ++j) 
                    for(int k = 1; j + k <= 5000; ++k) 
                        if(dp[l][i][j] && dp[i+1][r][k]) dp[l][r][j+k] = 1;
                
                for(int j = 1; j <= 5000; ++j)
                    for(int k = 1; (val = j * k) <= 5000; ++k)
                        if(dp[l][i][j] && dp[i+1][r][k]) dp[l][r][val] = 1;
            }
        }
    }
    for(int r = sz; r >= 1; --r) {
        for(int i = 1; i <= 5000; ++i) {
            if(dp[1][r][i]) {
                ans[i] = r;
            }
        }
    }
    for(int i = 1; i <= 5000; ++i) {
        printf("%d, ", ans[i]);
    }
}