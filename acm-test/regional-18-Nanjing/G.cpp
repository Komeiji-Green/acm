#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
ll Pow(ll a, ll k, ll p) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = ans * a % p;
        k >>= 1; a = a * a % p;
    }
    return ans;
}

int main() {
    int T;
    cin >> T;
    ll n;
    while(T--) {
        scanf("%lld", &n);
        
        printf("%lld\n", ans);

    }
}