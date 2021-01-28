#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 563333;
const ll mod=1e9+7;
ll a[maxn];
ll ans[maxn];
ll p[100];
ll w[100], s1[maxn], s2[maxn];
int main() {
    int T;
    cin >> T;
    for(int b=0; b<60;++b) p[b]=(1ll<<b);
    while(T--) {
        int n;
        scanf("%d", &n);
        for(int i =1;i<=n;++i) scanf("%lld", &a[i]);
        for(int j = 0; j < 60; ++j) w[j] = 0;
        for(int i = 1; i <= n; ++i) {
            for(int j = 0; j < 60; ++j) {
                w[j]=(w[j]+(p[j]&a[i])%mod)%mod;
            }
        }
        for(int i = 1; i <= n; ++i) {
            s1[i]=s2[i]=0;
            for(int j = 0; j < 60; ++j) {
                if(p[j]&a[i]) {
                    s1[i]=(s1[i] + w[j])%mod;
                    s2[i]=(s2[i] + (p[j]%mod)*n%mod)%mod;
                } else {
                    s2[i]=(s2[i] + w[j]) % mod;
                }
            }
        }
        ll ans= 0;
        for(int i = 1; i <= n; ++i) {
            ans = (ans + s1[i] * s2[i] % mod) % mod;
        }
        printf("%lld\n", (ans + mod) % mod);

    }
}