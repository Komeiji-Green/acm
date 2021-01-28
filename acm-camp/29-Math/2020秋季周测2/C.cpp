#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ll; // here, ll is unsigned!

ll pre(ll n, int k) {
    if(k == 0) return n;
    else if(k == 1) {
        ll a = n, b = n + 1;
        if(n % 2 == 0) a /= 2;
        else b /= 2;
        return a * b;
    } else if(k == 2) {
        ll a = n, b = n + 1, c = 2 * n + 1;
        if(a % 2 == 0) a /= 2;
        else b /= 2;
        if(a % 3 == 0) a /= 3;
        else if(b % 3 == 0) b /= 3;
        else c /= 3;
        return a * b * c;
    } if(k == 3) {
        ll a = n, b = n + 1;
        if(n % 2 == 0) a /= 2;
        else b /= 2;
        return a * b * a * b;
    }
}

ll calc(ll n, int k) {
    ll ans = 0;
    for(ll i = 1, j; i <= n; i = j + 1) {
        j = n / (n / i);
        ans += (n / i) * (pre(j, k) - pre(i - 1, k));
    }
    return ans;
}

int main() {
    int T;
    cin >> T;
    while(T--) {
        int a, b; ll n;
        cin >> a >> b >> n;
        ll aa = calc(n, a), bb = calc(n, b);
        ll ans = aa ^ bb;
        cout << ans << endl;
    }
}