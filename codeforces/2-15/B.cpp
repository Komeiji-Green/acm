#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 233333;

int a[N];
int main() {
    int T;
    cin >> T;
    while(T--) {
        ll n, k, ans;
        scanf("%lld %lld", &n, &k);
        if(n % 2 == 0) {
            ans= (k - 1) % n + 1;
        } else {
            ll m = (n - 1) / 2;
            ll d = (k - 1) / m * m + 1;
            ll pos = n + 1 - ((d - 1) % n + 1);
            ll r = k - d;
            pos = (pos + r + 1) % n;
            if(pos == 0) pos = n;
            ans = pos;
        }
        printf("%lld\n", ans);
    }
}