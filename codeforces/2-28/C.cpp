#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 10005;
const int inf = 0x3f3f3f3f;

ll a[maxn];
ll cnt[maxn];
int main() {
    int T, n, u, v;
    cin >> T;
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
        for(int i = 1; i <= n; ++i) cnt[i] = 0;
        ll sum = 0, cur;
        for(int i = 1; i <= n; ++i) {
            cur = max(a[i] - 1 - cnt[i], 0ll);
            //printf("%d: %lld\n", i, cur);
            sum += cur;
            if(cnt[i] >= a[i]) cnt[i+1] += (cnt[i] - a[i] + 1);
            for(int j = 2; i + j <= n; ++j) {
                if(j <= a[i]) cnt[i+j]++;
            }
            //for(int j = 1; j <= n; ++j) printf("%lld ",cnt[i]);
            //printf("\n");
        }
        printf("%lld\n", sum);
    }
}