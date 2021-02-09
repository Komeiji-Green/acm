#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
const int inf = 0x3f3f3f3f;
int a[maxn], dp[maxn][3], col[maxn][3];

int cnt[maxn];
int le, ri;
int main() {
    int n;
    cin >> n;
    for(int i = 1; i<= n; ++i) scanf("%d", &a[i]);
    int tot = 1; cnt[1] = 1;
    for(int i = 2; i <= n; ++i) {
        if(a[i] == a[tot]) cnt[tot]++;
        else {
            ++tot;
            a[tot] = a[i]; cnt[tot] = 1;
        }
    }
    for(int i = 1; i <= tot; ++i) for(int j = 0; j < 3; ++j) dp[i][j] = -inf; 
    for(int i = 1; i <= tot; ++i) {
        int x = a[i], cur = a[i-1], p = col[i-1][1], pp = col[i-1][2];
        col[i][0] = x; col[i][1] = cur; col[i][2] = p;
        if(cnt[i] > 1) {
            dp[i][0] = dp[i-1][0] + 2;
            if(x == p) dp[i][0] = max(dp[i][0], dp[i-1][1] + 1);
            else dp[i][0] = max(dp[i][0], dp[i-1][1] + 2);
            if(x == pp) dp[i][0] = max(dp[i][0], dp[i-1][2] + 1);
            else dp[i][0] = max(dp[i][0], dp[i-1][2] + 2);
        } else {
            if(x == p) dp[i][0] = max(dp[i][0], dp[i-1][1] + 1);
            if(x == pp) dp[i][0] = max(dp[i][0], dp[i-1][2] + 1);
        }
        dp[i][1] = max(dp[i][1], dp[i-1][0] + 1);
        if(x == p) dp[i][1] = max(dp[i][1], dp[i-1][1]);
        else dp[i][1] = max(dp[i][1], dp[i-1][1] + 1);
        if(x == pp) dp[i][1] = max(dp[i][1], dp[i-1][2]);
        else dp[i][1] = max(dp[i][1], dp[i-1][2] + 1);
        if(p == x) dp[i][2] = dp[i][0];
        else if(p == cur) dp[i][2] = dp[i][1];
        else {
            dp[i][2] = dp[i-1][1] + 1;
            if(p == pp) dp[i][2] = max(dp[i][2], dp[i-1][2] + 1);
        }
    }
    int ans = max(max(dp[tot][0], dp[tot][1]), dp[tot][2]);
    printf("%d\n", ans);
    /*for(int i = 1; i <= tot; ++i) {
        int c = a[i], pre = a[i-1];
        if(cnt[i] > 1) {
            if(col[i-1][0] != c) dp[i][0] = max(dp[i][0], dp[i-1][0] + 2);
            else dp[i][0] = max(dp[i][0], dp[i-1][0] + 1);
            col[i][0] = c;
            if(col[i-1][1] != c) dp[i][0] = max(dp[i][0], dp[i-1][0] + 2);
            else dp[i][0] = max(dp[i][0], dp[i-1][0] + 1);
            col[i][1] = c;
        } else {
            if(col[i-1][0] != c) {
                col[i][0] = pre;
                col[i][1] = col[i-1][0];
                dp[i][0] = max(dp[i-1][0], dp[i-1][1]) + 1;
                dp[i][1] = dp[i-1][0] + 1;
            } else {
                
            } 

        }
        int c = a[i];
        if(c != a[i])
    }*/
}
/*
11
1 1 1 2 3 2 2 2 1 1 1

8
*/

/*
13
1 1 1 2 2 3 4 2 2 2 1 1 1

10
*/