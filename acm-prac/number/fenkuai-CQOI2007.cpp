#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

ll pre(ll n) {
    return n * (n + 1) / 2;
}
int main() {
    ll n, k;
    cin >> n >> k;
    ll m = min(n, k);
    ll sum = 0;
    for(int i = 1, j; i <= m; i = j + 1) {
        j = min(k / (k / i), m);
        sum += k * (j - i + 1) - (k / i) * (pre(j) - pre(i - 1));
    }
    if(n > k) {
        sum += k * (n - k);
    }
    printf("%lld\n", sum);
}

int main() {

    for(int i = a, j; i <= b; i = j + 1) {
        j = min(n / (n / i), b);
        ans += (n / i) * (pre(j) - pre(i - 1));
    }
    
}