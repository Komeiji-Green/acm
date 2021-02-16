#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll dp[3][2077][12][2]; // 组号、差值、位号、0/1
ll sum[3][2077][12][2]; // 前缀和
ll a[3], b[3], cnt[3][2];

ll gao(int st) {
    int cur = 0;
    ll res = 0, now;
    for(int i = 0; i < 8; ++i) {
        cur = st;
        for(int j = 0; j < 3; ++j) {
            if((1<<j)&i) cur ^= 1;
        }
        if(!cur) continue;
        now = 1;
        for(int j = 0, k; j < 3; ++j) {
            k = ((i>>j)&1);
            now *= cnt[j][k];
        }
        res += now;
    }
    return res;
}
int main() {
    int T;
    cin >> T;
    for(int cas = 1; cas <= T; ++cas) {
        cin >> a[0] >> a[1] >> a[2];
        cin >> b[0] >> b[1] >> b[2];
        for(int z = 0; z < 3; ++z) {
            int A = a[z], B = b[z];
            for(int k = 0; k <= 2000; ++k) {
                for(int i = 0; i < 12; ++i) for(int j = 0; j < 2; ++j) dp[z][k][i][j] = 0;
                for(int x = 0, y, s; x <= A && x + k <= B; ++x) {
                    y = x + k; s = x ^ y;
                    for(int i = 0, j; i < 12; ++i) {
                        j = ((s>>i)&1);
                        dp[z][k][i][j]++;
                    }
                }
                if(!k) continue;
                for(int y = 0, x, s; y <= B && y + k <= A; ++y) {
                    x = y + k; s = x ^ y;
                    for(int i = 0, j; i < 12; ++i) {
                        j = ((s>>i)&1);
                        dp[z][k][i][j]++;
                    }
                }
            }
        }
        for(int z = 0; z < 3; ++z) {
            for(int i = 0; i < 12; ++i) {
                for(int j = 0; j < 2; ++j) {
                    sum[z][0][i][j] = dp[z][0][i][j];
                    for(int k = 1; k <= 2000; ++k) {
                        sum[z][k][i][j] = dp[z][k][i][j] + sum[z][k-1][i][j];
                    }
                }
            }
        }
        ll res = 0;
        ull ans = 0;
        for(int k = 0; k <= 2000; ++k) { // max值
            for(int i = 0; i < 12; ++i) { // 各位
                int st = ((k>>i)&1); // max值在该位的bit
                for(int j = 0; j < 2; ++j) cnt[0][j] = dp[0][k][i][j];
                for(int j = 0; j < 2; ++j) cnt[1][j] = sum[1][k][i][j];
                for(int j = 0; j < 2; ++j) cnt[2][j] = sum[2][k][i][j];
                res = gao(st);
                ans += res * (1ll<<i);
                if(!k) continue;
                for(int j = 0; j < 2; ++j) cnt[0][j] = sum[0][k-1][i][j];
                for(int j = 0; j < 2; ++j) cnt[1][j] = dp[1][k][i][j];
                for(int j = 0; j < 2; ++j) cnt[2][j] = sum[2][k][i][j];
                res = gao(st);
                ans += res * (1ll<<i);
                for(int j = 0; j < 2; ++j) cnt[0][j] = sum[0][k-1][i][j];
                for(int j = 0; j < 2; ++j) cnt[1][j] = sum[1][k-1][i][j];
                for(int j = 0; j < 2; ++j) cnt[2][j] = dp[2][k][i][j];
                res = gao(st);
                ans += res * (1ll<<i);
            }
        }
        printf("Case #%d: ", cas);
        cout << ans << endl;
    }
}