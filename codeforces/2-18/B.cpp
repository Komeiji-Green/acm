#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 233333;

ll x[N], y[N];
int main() {
    int T, n;
    cin >> T;
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n ;++i) scanf("%lld %lld", &x[i], &y[i]);
        sort(x + 1, x + n + 1);
        sort(y + 1, y + n + 1);
        int le, ri;
        if(n % 2 == 0) {
            le = n / 2; ri = le + 1; 
        } else {
            le = ri = (n + 1) / 2;
        }
        ll xx = x[ri] - x[le] + 1;
        ll yy = y[ri] - y[le] + 1;
        ll ans = xx * yy;
        printf("%lld\n", ans);
    }
}