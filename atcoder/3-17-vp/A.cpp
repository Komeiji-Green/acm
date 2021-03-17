#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 233333;
const int phi = 4;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    ll n;
    cin >> n;
    ll sum = 0;
    for(ll i = 1; i <= n; ++i) {
        for(ll j = 1; i * j <= n; ++j) {
            sum += (n / (i*j));
        }
    }
    cout << sum << endl;
}