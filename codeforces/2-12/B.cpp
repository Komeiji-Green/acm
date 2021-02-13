#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
int a[maxn], cnt[maxn];
int main() {
    int T, n, q, k;
    cin >> n >> q >> k;
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for(int i = 2; i < n; ++i) {
        cnt[i] = a[i+1]-a[i-1]-2;
    }
    for(int i = 2; i < n; ++i) cnt[i] = cnt[i-1] + cnt[i];
    while(q--) {
        int l, r;
        scanf("%d%d", &l, &r);
        ll ans = 0;
        if(l == r) {
            ans = k - 1;
        } else {
            ans = a[l+1] - 2 + k - a[r-1] - 1;
            ans += cnt[r-1] - cnt[l];
        }
        printf("%lld\n", ans);
    }
    
}