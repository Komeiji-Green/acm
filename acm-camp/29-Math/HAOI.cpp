#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 122222;
const int N = 100050;
ll c[5], d[5], f[maxn];
#include<map>
int main() {
    ll n, s;
    scanf("%lld%lld%lld%lld%lld", &c[1], &c[2], &c[3], &c[4], &n);
    f[0] = 1;
    for(int j = 1; j <= 4; ++j)
        for(int i = 1; i <= N; ++i)
            if(i >= c[j]) f[i] += f[i - c[j]];
    int sz = (1<<4);
    while(n--) {
        scanf("%lld%lld%lld%lld%lld", &d[1], &d[2], &d[3], &d[4], &s);
        ll m; int sgn; ll ans = 0;
        for(int i = 0; i < sz; ++i) {
            m = s, sgn = 1;
            for(int j = 0; j < 4; ++j) {
                if(i & (1<<j)) m -= (d[j+1]+1)*c[j+1], sgn = -sgn;
            }
            if(m >= 0) ans += sgn * f[m];
        }
        printf("%lld\n", ans);
    }
}

