#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 233333;
ll a[maxn], s[maxn];

int main() {
    int T;
    int n, k;
    cin >> T;
    while(T--) {
        scanf("%d %d", &n, &k);
        for(int i = 0; i < n; ++i) scanf("%lld", &a[i]);
        s[0] = 0;
        for(int i = 1; i < n; ++i) s[i] = s[i-1] + a[i];
        ll minv = a[0];
        for(int i = 1; i < n; ++i) {
            minv = max(minv, (100ll * a[i] - 1) / k + 1 - s[i - 1]);
        }
        ll ans = minv - a[0];
        printf("%lld\n", ans);

    }
}