#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
int a[maxn];
int main() {
    int T, n;
    cin >> T;
    ll x,y;
    while(T--) {
        scanf("%lld %lld", &x, &y);
        ll q = 1, cnt = 0;
        ll le, ri;
        for(;q <= y; ++q) {
            le = q + 1; ri = min((x / q) - 1, y);
            if(le > ri) break;
            cnt += ri - le + 1;
        }
        printf("%lld\n", cnt);
    }
    
}