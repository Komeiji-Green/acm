#include<iostream>
using namespace std;

const int N = 100;

int dp[N][N];   // (i, 0/1): i位数，第i位数

void getDP() {
    for(int i = 0; i <= 9; i++) {
        dp[1][i] = 1;
    }
    dp[1][4] = 0;
    for(int i = 2; i <= 7; i++) {
        int sum = 0;
        for(int k = 0; k <= 9; k++) {
            sum += dp[i - 1][k];
        }
        for(int j = 0; j <= 9; j++) {
            if(j == 4) dp[i][j] = 0;
            else if(j == 6) dp[i][j] = sum - dp[i - 1][2];
            else dp[i][j] = sum;
        }
    }
}

int digit[10];
int gao(int x) {
    if(x == 0) return 1;
    if(x < 0) return 0;
    int k = 0;
    while(x) {
        digit[++k] = x % 10;
        x /= 10;
    }
    //printf("k: %d\n", k);
    int ans = 0;
    for(int i = k; i >= 1; i--) {
        for(int j = 0; j < digit[i]; j++) {
            if(i != k && digit[i + 1] == 6 && j == 2) continue;
            ans += dp[i][j];
        }
        if((i != k && digit[i + 1] == 6 && digit[i] == 2) || digit[i] == 4) break;
        if(i == 1) ans++;
    }
    return ans;
}

int main()
{
    int l, r;
    getDP();
    /*for(int i = 1; i <= 7; i++) {
        for(int j = 0; j <= 9; j++) {
            printf("%d %d: %d\n", i, j, dp[i][j]);
        }
    }*/
    while(scanf("%d %d", &l, &r) != EOF && (l != 0 || r != 0)) {
        int ans = gao(r) - gao(l - 1);
        printf("%d\n", ans);
    }
}