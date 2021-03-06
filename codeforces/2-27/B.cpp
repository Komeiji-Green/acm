#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
ll a[maxn];
int main() {
    int T, n;
    cin >> T;
    ll k;
    while(T--) {
        scanf("%d %lld", &n, &k);
        for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
        ll minv = a[1], maxv = a[1];
        for(int i = 2; i <= n; ++i) minv = min(minv, a[i]), maxv = max(maxv, a[i]);
        if(k % 2) {
            for(int i = 1; i <= n; ++i) {
                a[i] = maxv - a[i]; printf("%lld ", a[i]);
            }
            printf("\n");
        } else {
            for(int i = 1; i <= n; ++i) {
                a[i] = a[i] - minv; printf("%lld ", a[i]);
            }
            printf("\n");
        }
        
    }
}