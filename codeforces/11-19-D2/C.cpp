#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
ll a[maxn];
int main() {
    int T;
    cin >> T;
    while(T--) {
        ll n;
        scanf("%lld", &n);
        ll mm = 0, sum = 0;
        for(int i = 1; i <= n; ++i) {
            scanf("%lld", &a[i]);
            mm = max(mm, a[i]);
            sum += a[i];
        }
        if(sum <= mm * (n - 1)) {
            printf("%lld\n", mm*(n-1)-sum);
        } else {
            ll r = 0;
            if(sum % (n - 1) == 0) r = 0;
            else {
                r = (n - 1) - sum % (n - 1);
            }
            printf("%lld\n", r);
        }
    }
}