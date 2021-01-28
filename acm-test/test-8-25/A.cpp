#include<iostream>
#include <cstdio>
using namespace std;

const int N = 15;
const int mod = 100000000;

int dp[N][1<<13];
int F[N];

// 判断一个二进制数是否有相邻1
bool check(int n) {
    bool flag = false;
    while(n) {
        if((n & 1) && flag) return false;
        flag = (n & 1);
        n >>= 1;
    }
    return true;
}
int main()
{
    int m, n;
    cin >> m >> n;

    int x;
    for(int i = 1; i <= m; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &x);
            if(x == 1) F[i] |= (1 << j);
        }
    }
    for(int st = 0; st < (1 << n); st++) {
        if((st & F[1]) == st && check(st)) dp[1][st] = 1;
        else dp[1][st] = 0;
    }
    for(int i = 2; i <= m; i++) {
        for(int st = 0; st < (1<<n); st++) {
            if((st & F[i]) != st || !check(st)) continue;
            for(int pre = 0; pre < (1<<n); pre++) {
                if((pre & F[i-1]) == pre && (pre & st) == 0) {
                    dp[i][st] = (dp[i-1][pre] + dp[i][st]) % mod;
                }
            }
        }
    }

    /*for(int i = 1; i <= m; i++) {
        for(int st = 0; st < (1<<n); st++) {
            printf("%d %d: %d\n", i, st, dp[i][st]);
        }
    }*/
    int sum = 0;
    for(int st = 0; st < (1<<n); st++) {
        sum = (sum + dp[m][st]) % mod;
    }
    printf("%d\n", (sum + mod) % mod); 
}