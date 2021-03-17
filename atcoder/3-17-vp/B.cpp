#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 233333;
const int mod = 10;
const int phi = 4;

ll Pow(ll a, ll k, ll p) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = ans * a % p;
        k >>= 1; a = a * a % p;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    ll a, b, c;
    cin >> a >> b >> c;
    ll m = Pow(b, c, phi), ans;
    if(b == 1 || b == 2 && c == 1) {
        ans = Pow(a, m, mod);
    } else {
        ans = Pow(a, m + phi, mod);
    }
    cout << (ans+mod)%mod << endl;
}