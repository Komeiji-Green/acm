#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;

const int maxn = 300050;
struct DD {
    ll x, y;
    bool operator<(const DD& b) {
        return x < b.x;
    }
} a[maxn], b[maxn];
ll ans[maxn];
int main() {
    int T, n;
    cin >> T;
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) scanf("%lld %lld", &a[i].x, &a[i].y);
        sort(a + 1, a + n + 1);

        for(int i = 1; i <= n; ++i) ans[i] = INF;
        int m = (1<<n);
        for(int i = 1; i < m; ++i) {
            int tot = 0;
            for(int j = 0; j < n; ++j) {
                if((1<<j)&i) {
                    b[++tot] = a[j+1];
                }
            }
            ll t = 0;
            for(int j = 1; j <= tot; ++j) {
                t = max(b[j].x, t);
                t += b[j].y;
            }
            ans[tot] = min(ans[tot], t);
        }
        for(int i = 1; i <= n; ++i) printf("%lld ", ans[i]);
        printf("\n");
    }
}