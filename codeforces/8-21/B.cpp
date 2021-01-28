#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long ll;
int main()
{
    int T;
    cin >> T;
    while(T--) {
        ll x1, y1, z1, x2, y2, z2;
        //  0   1   2   0   1   2
        scanf("%lld %lld %lld %lld %lld %lld", &x1, &y1, &z1, &x2, &y2, &z2);
        ll ans = 0;
        if(y2 <= z1) {
            ans += 2 * y2;
            ll c = z2 - (z1 - y2 + x1);
            if(c > 0) {
                ans -= 2 * c;
            }
        } else {
            ans += 2 * z1;
            ll c = z2 - x1;
            if(c > 0)
                ans -= 2 * c;
        }
        printf("%lld\n", ans);
    }
};
