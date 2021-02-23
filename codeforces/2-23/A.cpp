#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 233333;

int a[N];
int main() {
    int T, n;
    ll a, b, c, p;
    cin >> T;
    while(T--) {
        cin >> p >> a >> b >> c;
        ll t = (p % a) ? (a - p % a) : 0;
        t = min(t, (p % b) ? (b - p % b) : 0);
        t = min(t, (p % c) ? (c - p % c) : 0);
        printf("%lld\n", t);
    }
}