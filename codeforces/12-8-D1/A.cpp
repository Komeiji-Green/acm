#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
char s[maxn];
ll sum[maxn];
ll ans[maxn];
int main() {
    int T;
    cin >> T;
    int n, p, k;
    ll x, y;
    while(T--) {
        scanf("%d %d %d", &n, &p, &k);
        scanf("%s", s);
        scanf("%lld%lld", &x, &y);
        memset(sum, 0, sizeof(sum));
        for(int i = n - 1; i >= 0; --i) {
            sum[i] = (s[i] == '1' ? 0 : 1) + sum[i + k];
        }
        sum[n] = 0;
        for(ll i = 0; i <= n - p; ++i) {
            ans[i] = y * i + x * sum[i + p - 1];
        }
        ll minv = ans[0];
        for(int i = 1; i <= n - p; ++i) {
            minv = min(minv, ans[i]);
        }
        printf("%lld\n", minv);
    }
}