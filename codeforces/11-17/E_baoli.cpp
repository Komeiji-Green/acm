#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;
ll a[maxn];
int main() {
    int n, q;
    cin >> n >> q;
    for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
    int op, x; ll y;
    while(q--) {
        scanf("%d %d %lld", &op, &x, &y);
        if(op == 1) {
            for(int i = 1; i <= x; ++i) a[i] = max(a[i], y);
        } else {
            int cnt = 0;
            for(int i = x; i <= n; ++i) {
                if(a[i] <= y) y -= a[i], ++cnt;
            }
            printf("%d\n", cnt);
        }
    }
}