#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2000005;

ll a[maxn], b[maxn];
int main() {
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
    ll sum = 0;
    for(int i = 1; i <= n; ++i) sum += a[i];
    for(int i = 1; i <= n; ++i) {
        b[i] = i - 1;
        sum -= b[i];
    }
    ll r = sum % n, h = sum / n;
    for(int i = 1; i <= n; ++i) {
        b[i] += h;
    }
    for(ll i = 1; i <= r; ++i) b[i]++;
    for(int i = 1; i <= n; ++i) printf("%lld ", b[i]);
    printf("\n");
}