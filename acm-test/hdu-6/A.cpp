#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
const int N = 233333;
ll inv[N], su[N];
void init() {
    inv[0] = 0, inv[1] = 1;
    for(int i = 2; i < N; ++i) inv[i] = inv[mod % i] * (mod - mod / i) % mod;
    su[1] = inv[1];
    for(int i = 2; i < N; ++i) su[i] = (su[i-1] + inv[i]) % mod;
}
ll s[N];
int main() {
    init();
    int T, n;
    cin >> T;
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) scanf("%lld", &s[i]);
        ll ans = 0, cur;
        for(int i = 1, j; i <= n; ++i) {
            j = min(i, n-i+1);
            cur = 0;
            cur = (cur + (su[n-j+1]-su[j-1])*j%mod) % mod;
            cur = (cur + (su[n]-su[n-j+1])*(n+1)%mod) % mod;
            ans = (ans + cur*s[i]%mod) % mod;
        }
        ll Q = (2ll*inv[n]%mod)*inv[n+1]%mod;
        ans = ans*Q%mod;
        printf("%lld\n", (ans+mod)%mod);
    }
}