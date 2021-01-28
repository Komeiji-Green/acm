#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int T;
int main() {
    cin >> T;
    ll d1, d2, d3, ans = 0;
    for(int cas = 1; cas <= T; ++cas) {
        scanf("%lld%lld%lld", &d1, &d2, &d3);
        if(d1 > d2) swap(d1, d2);
        if((d1 + d2 + d3) % 2) ans = 0;
        else if(d1 == 0) {
            if(d2 == 0) {
                if(d3 == 0) ans = 1;
                else ans = 0;
            } else {
                if(d2 == d3) {
                    ans = 4 * d2;
                } else ans = 0;
            }
        } else {
            if(d3 == 0) {
                if(d1 == d2) ans = 4 * d1;
                else ans = 0;
            } else {
                if(d3 == d2 - d1) {
                    ans = 4 * (d1 + 1) * (d3 + 1) - 4;
                } else if(d3 == d2 + d1) {
                    ans = 4 * (d1 + 1) * (d2 + 1) - 4;
                } else if(d3 > d2 + d1 || d3 < d2 - d1) ans = 0;
                else {
                    ans = 4 * (d1 + d2 + d3);
                }
            }
        }
        printf("Case #%d: %lld\n", cas, ans);
    }
}