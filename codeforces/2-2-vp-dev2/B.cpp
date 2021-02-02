#include<bits/stdc++.h>
using namespace std;


bool chk(int x, int d) {
    int a = x % 10,b = x / 10;
    return a == d || b == d;
}

int dp[10][105];
int main() {
    int T;
    cin >> T;
    for(int d = 1; d <= 9; ++d) {
        for(int i = 1; i <= 100; ++i) {
            dp[d][i] = chk(i, d);
        }
        dp[d][0] = 1;
        for(int i = 1; i <= 100; ++i) {
            for(int j = 0; j < i; ++j) {
                if(dp[d][j] && dp[d][i-j]) dp[d][i] = 1;
            }
        }
    }
    while(T--) {
        int q, d;
        cin >> q >> d;
        for(int i  = 1, x; i <= q;  ++i) {
            scanf("%d", &x);
            if(x >= 100) {
                printf("YES\n");
            } else {
                if(dp[d][x]) {
                    printf("YES\n");
                } else {
                    printf("NO\n");
                }
            }
        }
    }
}