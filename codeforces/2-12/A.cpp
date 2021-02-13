#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll  INF = 0x3f3f3f3f3f3f3f3f;
const int maxn = 233333;
int a[maxn];
int main() {
    int T, n;
    cin >> T;
    ll a, b;
    while(T--) {
        scanf("%lld %lld", &a, &b);
        ll x, y;
        ll ans = INF;
        for(int i = 0; i <= 50; ++i) {
            y = b + i;
            if(y == 1) continue;
            int cnt = 0;
            x = a;
            while(x > 0) {
                x /= y; ++cnt;
            }
            ans = min(ans, (ll)(i + cnt));
        }
        printf("%lld\n", ans);
    }
    
}