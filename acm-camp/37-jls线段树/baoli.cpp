#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 500007;
ll a[N];
int main() {
    int n, q;
    cin >> n >> q;
    for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);

    int op, l, r;
    ll x;
    while(q--) {
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d %d %lld", &l, &r, &x);
            for(int i = l; i <= r; ++i) a[i] = min(a[i], x);
        } else {
            scanf("%d %d", &l, &r);
            ll res = 0;
            for(int i = l; i <= r; ++i) res += a[i];
            printf("%lld\n", res);
        }
    }
}