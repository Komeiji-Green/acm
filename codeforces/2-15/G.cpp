#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

ll dp1, sum, ans;
ll dp2[2][405][2][2];
ll dp3[2][405][405][3][3];
ll c[26];
ll pre(int st, int A, int B, int x, int y) {
    ll res = 0;
    for(int i = 0; i < A; ++i) 
        for(int j = 0; j < B; ++j)
            res = (res + dp3[st][i][j][x][y]) % mod;
    return res;
}
int main() {
    int n, m; cin >> n; m = 2 * n;
    for(int i = 0; i < 26; ++i) scanf("%lld", &c[i]);

    //clock_t stt = clock(), ed;
    dp1 = 26 * 26;
    for(int i = 3; i <= n; ++i) {
        dp1 = dp1 * 25 % mod;
    }
    ans = dp1;
    int st = 0;
    int cnt = 0;
    for(int x = 0; x < 2; ++x) {
        for(int y = 0; y < 2; ++y) {
            cnt = 0;
            if(x) ++cnt; if(y) ++cnt;
            for(int i = 0; i <= n+1; ++i) {
                if(i <= n - cnt) dp2[st][i][x][y] = 0;
                else dp2[st][i][x][y] = 1;
            }
        }
    }
    for(int i = 3; i <= n; ++i, st^=1) {
        for(int x = 0; x < 2; ++x) {
            dp2[st^1][n+1][x][0]=dp2[st^1][n+1][x][1]=25*dp2[st][n+1][x][0]%mod;
            for(int j = 0; j <= n; ++j) {
                dp2[st^1][j][x][0] = (dp2[st][j][0][x] * 24 + dp2[st][j][1][x]) % mod;
                dp2[st^1][j][x][1] = dp2[st][j+1][0][x] * 25 % mod;
            }
        }
    }
    for(int a = 0; a < 26; ++a) {
        sum = (dp2[st][n-c[a]][0][0] * 25 * 25 + dp2[st][n-c[a]][0][1] * 25 + dp2[st][n-c[a]][1][0] * 25 + dp2[st][n-c[a]][1][1]) % mod;
        ans = (ans - sum) % mod;
    }

    ll mul[3] = {1, 24, 24 * 24};

    st = 0;
    int cnta, cntb;
    for(int x = 0; x < 3; ++x) {
        for(int y = 0; y < 3; ++y) {
            cnta=cntb=0;
            if(x == 1) cnta++; if(x == 2) cntb++;
            if(y == 1) cnta++; if(y == 2) cntb++;
            for(int i = 0; i <= n+1; ++i) {
                for(int j = 0; j <= n+1; ++j) {
                    if(i == n - cnta && j == n - cntb) dp3[st][i][j][x][y] = 1;
                    else dp3[st][i][j][x][y] = 0;
                }
            }
        }
    }
    for(int i = 3; i <= n; ++i, st ^= 1) {
        for(int j = 0; j <= n; ++j) {
            for(int k = 0; k <= n; ++k) {
                for(int x = 0; x < 3; ++x) {
                    dp3[st^1][j][k][x][0] = (dp3[st][j][k][0][x] * 23 + dp3[st][j][k][1][x] + dp3[st][j][k][2][x]) % mod;
                    dp3[st^1][j][k][x][1] = (dp3[st][j+1][k][0][x] * 24 + dp3[st][j+1][k][2][x]) % mod;
                    dp3[st^1][j][k][x][2] = (dp3[st][j][k+1][0][x] * 24 + dp3[st][j][k+1][1][x]) % mod;
                }
            }
        }
    }
    //printf("!!!!!!\n");
    for(int a = 0; a < 26; ++a) {
        for(int b = a + 1; b < 26; ++b) {
            sum = 0;
            for(int x = 0; x < 3; ++x) {
                for(int y = 0; y < 3; ++y) {
                    cnt = 0;
                    if(!x) cnt++; if(!y) cnt++;
                    sum = (sum + mul[cnt] * pre(st, n-c[a], n-c[b], x, y) % mod);
                }
            }
            ans = (ans + sum) % mod;
        }
    }
    
    //ed = clock();
    //cout << (double)(ed-stt)/ 1000 << endl;
    printf("%lld\n", (ans + mod) % mod);
}