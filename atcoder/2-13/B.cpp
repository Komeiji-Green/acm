#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int T;
    ll L, R, B, C;
    cin >> B >> C;
    ll l1, r1, l2, r2;
    l1 = B - C / 2;
    r1 = (C >= 2) ? B + (C - 2) / 2 : B;
    l2 = -B - (C - 1) / 2;
    r2 = -B + (C - 1) / 2;
    ll ans;
    if(r1 < l2 || r2 < l1) {
        ans = (r1-l1+1) + (r2-l2+1);
    } else {
        L = min(l1, l2);
        R = max(r1, r2);
        ans = (R-L+1);
    }
    printf("%lld\n", ans);
}