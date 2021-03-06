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

        int cnt = 0;
        for(int i = 1; i <= n; ++i) {
            while(a[i] > 1) {
                ++cnt;
                for(int p = i, j; p <= n; p = j) {
                    j = p + a[p];
                    if(a[p] > 1) a[p]--;
                }
            }
        }

        printf("%d\n", cnt);
    }
}