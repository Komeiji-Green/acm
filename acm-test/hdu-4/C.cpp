#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = 0x3f3f3f3f3f3f3f3f;

void chk(ll &x, ll y) {
    if(x < y) x = y;
}
const int N = 2333;
struct A {
    int w; ll c;
} a[N];
ll dp[N*N];
int n, m;
int main() {
    srand(time(NULL));
    int T;
    cin >> T;
    while(T--) {
        scanf("%d %d", &n, &m);
        for(int i = 1; i <= n; ++i) scanf("%d %lld", &a[i].w, &a[i].c);
        for(int i = n + 1; i <= n + m; ++i) {
            scanf("%d %lld", &a[i].w, &a[i].c);
            a[i].w = -a[i].w;
        }
        int sz = n + m;
        random_shuffle(a + 1, a + sz + 1);
        int mid = min(50000, 1000 * sz), len = 2 * mid;
        for(int i = 0; i <= len; ++i) dp[i] = -INF;
        dp[mid] = 0;
        ll c;
        for(int i = 1, w; i <= sz; ++i) {
            c = a[i].c;
            if((w=a[i].w) > 0) {
                for(int j = len; j >= w; --j)
                    chk(dp[j], dp[j-w] + c);
            } else {
                w = -w;
                for(int j = 0; j <= len - w; ++j) {
                    chk(dp[j], dp[j+w] + c);
                }
            }
        }
        ll ans = dp[mid];
        printf("%lld\n", ans);        
    }
}