#include<cstdio>
#include<iostream>
#include<cmath>
using namespace std;

typedef long long ll;
int main() {
    int T;
    cin >> T;
    ll x1, y1, x2, y2;
    while(T--) {
        scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
        if(x1 == x2) {
            printf("%lld\n", abs(y2 - y1));
        } else if(y1 == y2) {
            printf("%lld\n", abs(x2 - x1));
        } else {
            printf("%lld\n", abs(x2 - x1) + abs(y2 - y1) + 2);
        }
    }
}