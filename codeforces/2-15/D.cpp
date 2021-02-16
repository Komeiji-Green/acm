#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 233333;

ll a[N], b[N], c[N];

const ll M = 1e9;
int main() {
    int tot = 0;
    for(ll i = 3; ; i += 2) {
        ll B = (i * i - 1) / 2;
        ll C = B + 1;
        if(C > M) break;
        a[++tot] = i;
        b[tot] = B; c[tot] = C;
    }
    int T;
    cin >> T;
    ll n;
    while(T--) {
        scanf("%lld", &n);
        int idx = upper_bound(c + 1, c + tot + 1, n) - c;
        --idx;
        printf("%d\n", idx);
    }
}