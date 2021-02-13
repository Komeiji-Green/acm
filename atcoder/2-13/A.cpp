#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 333333;
int b[maxn];
int main() {
    int T;
    ll L, R;
    cin >> T;
    while(T--) {
        scanf("%lld %lld", &L, &R);
        ll len = R - 2 * L + 1;
        if(len < 1) {
            printf("0\n");
        } else {
            ll ans = len * (len + 1) / 2;
            printf("%lld\n", ans);
        }
    }
}