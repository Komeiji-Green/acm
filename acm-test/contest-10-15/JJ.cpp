#include<bits/stdc++.h>
using namespace std;
const int N = 1e8 + 5;
const int M = 1e4 + 5;
const int mod = 998244353;
int inv[N];
void InvList(int n, int p)
{
    inv[0] = 0;
    inv[1] = 1;
    for(register int i = 2; i <= n; ++i) {
        inv[i] = 1ll * inv[p % i] * (p - p / i) % p;
    }
    for(register int i = 2; i <= n; ++i) {
        inv[i] = (inv[i - 1] + inv[i]) % mod;
    }
}
int p[1005], l[1005], cnt = 0;
void Fact(int x) {
    cnt = 0;
    for(int i = 2; i * i <= x; i++) {
        if(x % i == 0) {
            p[cnt] = i; l[cnt] = 0;
            while(x % i == 0) {
                x /= i; 
                l[cnt]++;
            }
            ++cnt;
        }
    }
    if(x != 1) {  // 则此时x一定是素数，且为原本x的大于根号x的唯一素因子
        p[cnt] = x; l[cnt] = 1; ++cnt;
    }
}
int main() {
    InvList(N - 1, mod);
    int T, n;
    cin >> T;
    while(T--) {
        scanf("%d", &n);
        if(n == 2) {
            printf("%d\n", ((inv[2] - inv[1]) % mod + mod) % mod);
        } else {
            Fact(n);
            int m = (1 << cnt), ans = 0;
            for(int i = 0, d, mu; i < m; ++i) {
                d = 1; mu = 1;
                for(int j = 0; j < cnt; ++j) {
                    if((1 << j) & i) {
                        d *= p[j]; mu = -mu;
                    }
                }
                ans = (ans + (1ll * (inv[d] - inv[d - 1]) * inv[n / d] % mod) * mu) % mod;
            }
            ans = 1ll * ans * (inv[n] - inv[n - 1]) % mod;
            ans = (ans + (inv[2] - inv[1]) % mod) % mod;
            printf("%d\n", (ans + mod) % mod);
        }
    }
}