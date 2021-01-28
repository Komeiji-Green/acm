#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;
const int N = 100500;
const int mod = 1000000007;
ll Pow[N];      // 1000
ll _1[N];       // 1111
ll cnt[N];      // 4444 ~ 7777 个数 - 1 : 2 ^ (i)
ll dp_sum[N];
ll sum[N];      // 4444 ~ 7444 双求和 : sum[i] = 2 * (4e(i-1) * (cnt[i-1]) + dp_sum[i-1]) + 3e(i-1)
ll dp_multi[N]; // 4444 ~ 7777 临项乘积 : 7e3 * 7e3 * (cnt[i-1] - 1) + 7e3 * (2 * dp_sum[i-1] - 444 - 777) + dp_multi[i-1]
ll multisum[N]; // 4444 ~ 7444 临项乘积 : 4444 * 4447 + ... + 4777 * 7444        


// ans += sum((head + ai)*(head + ai-1))
// ans += head * head * cnt[i] + head * sum[i] + multisum

void DP(int n) {
    cnt[0] = 1;
    Pow[1] = 1;
    _1[1] = 1;
    cnt[1] = 2;
    dp_sum[1] = 11;
    sum[1] = 11;
    dp_multi[1] = 28;
    multisum[1] = 28;
    for(int i = 2; i <= n; i++) {
        Pow[i] = 10 * Pow[i-1] % mod;
        _1[i] = (10 * _1[i-1] + 1) % mod;
        cnt[i] = 2 * cnt[i - 1] % mod;

        // dp_sum[i] = (4 + 7) * Pow[i] * cnt[i-1] + 2 * dp_sum[i-1]
        dp_sum[i] = (Pow[i] * cnt[i-1] % mod * (4 + 7) % mod + 2 * dp_sum[i-1] % mod) % mod;

        sum[i] = (2 * (Pow[i] * cnt[i-1] % mod * 4 + dp_sum[i-1]) + 3 * Pow[i]) % mod;

        multisum[i] 
        = (Pow[i] * Pow[i] % mod * 4 * 4 % mod * (cnt[i-1] - 1) % mod
        + Pow[i] * 4 % mod * ((2 * dp_sum[i-1] - (4 + 7) * _1[i-1]) % mod) % mod
        + dp_multi[i-1]) % mod;

        multisum[i] += (Pow[i] * 4 + _1[i-1] * 7) % mod * ((Pow[i] * 7 + _1[i-1] * 4) % mod) % mod;
        multisum[i] %= mod;

        dp_multi[i] 
        = (multisum[i]
        + (Pow[i] * Pow[i] % mod * 7 * 7 % mod * (cnt[i-1] - 1) % mod
        + Pow[i] * 7 % mod * ((2 * dp_sum[i-1] - (4 + 7) * _1[i-1]) % mod) % mod
        + dp_multi[i-1])) % mod;
    }

    /*for(int i = 1; i <= n; i++) {
        printf("%d: dp_sum: %d, sum: %d, dp_multi: %d, multisum: %d\n", i, dp_sum[i], sum[i], dp_multi[i], multisum[i]);
    }*/
}

ll get(char *s, int k) {
    ll ans = 0;
    ll head = 0;
    for(int i = k; i >= 1; i--) {
        char c = s[k - i];
        if(c == '7') {
            ans = (ans 
                + (head * head % mod * (cnt[i-1]) % mod)
                + (head * sum[i] % mod)
                + (multisum[i])) % mod;
        }
        int d = c - '0';
        head = (head + Pow[i] * d % mod) % mod;
    }
    return ans;
}

char l[N], r[N];

int main()
{
    scanf("%s %s", l, r);
    int n = strlen(l);
    DP(n);

    ll ansl = get(l, n);
    ll ansr = get(r, n);
    ll ans = (ansr - ansl) % mod;
    ans = (ans + mod) % mod;
    //printf("%lld = %lld - %lld\n", ans, ansr, ansl);    
    printf("%lld\n", ans);
}