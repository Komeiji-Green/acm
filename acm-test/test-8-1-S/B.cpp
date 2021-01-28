#include<iostream>
#include<cmath>
#include<cstdlib>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

int main()
{
    ll n, k, a, b;
    cin >> n >> k >> a >> b;
    ll mingcd = n * k, maxgcd = 1;
    ll l[4] = { abs(a - b), k - abs(a - b), abs(a + b), k - abs(a + b) };
    ll g[4];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 4; j++) {
            g[j] = abs(gcd(n * k, l[j] + i * k));
        }
        for(int j = 0; j < 4; j++)
        {
            mingcd = min(mingcd, g[j]);
            maxgcd = max(maxgcd, g[j]);
        }
    }
    ll x = n * k / maxgcd;
    ll y = n * k / mingcd;
    cout << x << " " << y << endl;
}