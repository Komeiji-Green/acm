#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

typedef long long ll;

const ll mod = 1e9 + 7;

const int maxn = 233333;
char s[maxn];

ll po[maxn], val[maxn], sum[maxn], dp[maxn];
int main() {
    scanf("%s", s);
    int n = strlen(s);
    po[0] = 1;
    val[0] = 0;
    sum[0] = 0;
    dp[0] = 0;
    ll a;
    for(int i = 1; i <= n; ++i) {
        a = s[i-1] - '0';
        dp[i] = ((10 * dp[i-1] % mod + ((1ll * (i-1) * i / 2) % mod) * a % mod) % mod + sum[i-1] % mod) % mod;
        //dp[i] = (((a * po[i-1]) % mod) * (1ll * (i-1) * i / 2) % mod + (dp[i-1] + sum[i-1]) % mod) % mod;
        val[i] = (10 * val[i-1] % mod + a) % mod;
        //val[i] = (a * po[i-1] % mod + val[i-1]) % mod;
        sum[i] = (sum[i-1] + val[i]) % mod;
        //sum[i] = (val[i] + sum[i-1]) % mod;
        //po[i] = 10 * po[i-1] % mod; 
        //printf("%d: %lld %lld %lld\n", i, val[i], sum[i], dp[i]);
    }
    printf("%lld\n", dp[n]);
}