#include<iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

#define rep(i, a, b) for(int i = (a); i <= (b); i++)

const int N = 1100;
const ll INF = 0x3f3f3f3f3f3f3f3f;

ll dp[N][N];
ll a[N];

int main()
{
    int n;
    cin >> n;
    rep(i, 1, n) {
        a[i] = i;
        a[i + n] = i;
    }
    
    int m = 2 * n;
    rep(d, 2, n - 1) {
        rep(l, 1, m) {
            int r = l + d;
            if(r <= m) {
                dp[l][r] = INF;
                rep(k, l + 1, r - 1) {
                    dp[l][r] = min(dp[l][r], a[l] * a[r] * a[k] + dp[l][k] + dp[k][r]);
                }
            }
        }
    }

    printf("%lld\n", dp[1][n]);
}