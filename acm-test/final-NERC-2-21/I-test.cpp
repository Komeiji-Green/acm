#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll dp[405][405], S[405], f[405], mod;
int main() {
    int T, n;
    cin >> T >> mod;
    int N = 400;
    f[0] = 1; for(ll i = 1; i <= N; ++i) f[i] = i * f[i-1];
    for(int i = 1; i <= N; ++i) dp[1][i] = f[i];
    for(int i = 2; i <= N; ++i) for(int j = i; j <= N; ++j) {
        ll sum = 0;
        for(ll k = 1; k <= j; ++k) sum = (sum + f[k] * dp[i-1][j-k]);
        dp[i][j] = sum;
    }
    S[1] = 1;
    for(int i = 2; i <= N; ++i) {
        ll sum = f[i];
        for(int k = 2; k < i; ++k) {
            sum = (sum - S[k] * dp[k][i]);
        }
        S[i] = sum;
    }
    while(T--) {
        scanf("%d", &n);
        printf("%lld\n", (S[n]));
    }
}