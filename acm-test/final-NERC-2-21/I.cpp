#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll dp[405][405], S[405], f[405], G[405], G1[405], mod;
int main() {
    int T, n;
    cin >> T >> mod;
    int N = 400;
    f[0] = 1; for(ll i = 1; i <= N; ++i) f[i] = i * f[i-1] % mod;
    for(int i = 1; i <= N; ++i) dp[1][i] = f[i];
    for(int i = 2; i <= N; ++i) for(int j = i; j <= N; ++j) {
        ll sum = 0;
        for(ll k = 1; k <= j; ++k) sum = (sum + f[k] * dp[i-1][j-k] % mod) % mod;
        dp[i][j] = sum;
    }
    S[1] = 1, S[2] = 2, G[2] = 2, G1[2] = 1;
    for(int i = 3; i <= N; ++i) {
        G1[i] = (G[i-1] - G1[i-1]) % mod;
        G[i] = f[i];
        for(int k = 2; k < i; ++k) G[i] = (G[i] - G[k] * f[i-k] % mod) % mod;
        ll s2 = 0;
        for(int k = 2; k < i; ++k) s2 = (s2 + G[k] * f[i-k] % mod) % mod;
        s2 = (s2 + G1[i]) % mod;
        s2 = 2 * s2 % mod;
        ll sum = (f[i] - s2) % mod;
        for(int k = 3; k < i; ++k) {
            sum = (sum - S[k] * dp[k][i] % mod) % mod;
        }
        S[i] = sum;
    }
    /*for(int i = 2; i <= 20; ++i) {
        printf("%d: G: %lld G1: %lld S: %lld\n", i, (G[i] + mod) % mod, (G1[i] + mod) % mod, (S[i] + mod) % mod);
    }*/
    /*for(int i = 3; i <= N; ++i) {
        if(i % 2 == 0) S[i] = (S[i] - 2) % mod;
        else S[i] = (S[i] + 2) % mod;
    }*/
    
    while(T--) {
        scanf("%d", &n);
        printf("%lld\n", (S[n] + mod) % mod);
    }
}