#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 5050;
ll col[N], xx[N], yy[N];

int main() {
    int T;
    cin >> T;
    for(int cas = 1; cas <= T; ++cas) {
        int n, m;
        scanf("%d %d", &n, &m);
        ll x, y;
        for(int i = 1, c; i <= n; ++i) {
            scanf("%lld %lld %d", &x, &y, &c);
            col[i] = c; xx[i] = x; yy[i] = y;
        }
        int op, k, c, l, r;
        ll res = 0;
        printf("Case #%d:\n", cas);
        while(m--) {
            scanf("%d", &op);
            if(op == 1) {
                scanf("%d %lld %lld", &k, &x, &y);
                xx[k] += x; yy[k] += y;
            } else if(op == 2) {
                scanf("%d %d", &k, &c);
                col[k] = c;
            } else {
                scanf("%d %d", &l, &r);
                res = 0;
                for(int i = l; i <= r; ++i) {
                    for(int j = l; j <= r; ++j) {
                        if(col[i] != col[j]) {
                            res = max(res, abs(xx[i] - xx[j]) + abs(yy[i] - yy[j]));
                        }
                    }
                }
                printf("%lld\n", res);
            }
        }
    }
}