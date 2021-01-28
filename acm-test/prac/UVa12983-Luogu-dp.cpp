#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;

const int N = 1050;
const ll mod = 1e9 + 7;

ll C[N];
int n;

void add(int x, ll v) {
    for(int i = x; i <= n; i += (i & (-i))) {
        C[i] = (C[i] + v) % mod;
    }
}
ll query(int x) {
    ll ans = 0;
    for(int i = x; i > 0; i -= (i & (-i))) {
        ans = (ans + C[i]) % mod;
    }
    return ans;
}

ll dp[N][N];    // dp(i, j): 尾元素i位，长度为j的严格递增子序列的个数

int a[N], tmp[N];
int main()
{
    int T;
    cin >> T;
    for(int cas = 1; cas <= T; cas++) {
        int m;
        scanf("%d %d", &n, &m);

        for(int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }

        // 离散化
        memcpy(tmp, a, sizeof(a));
        sort(tmp + 1, tmp + n + 1);
        int idx = unique(tmp + 1, tmp + n + 1) - tmp;
        for(int i = 1; i <= n; i++) {
            int fd = lower_bound(tmp + 1, tmp + idx, a[i]) - tmp;
            a[i] = fd;
        }

        /*for(int i = 1; i <= n; i++) {
            printf("%d ", a[i]);
        }
        printf("\n");*/

        for(int i = 1; i <= n; i++) {
            dp[i][1] = 1;
        }
        for(int j = 2; j <= m; j++) {
            memset(C, 0, sizeof(C));
            for(int i = 1; i <= n; i++) {
                dp[i][j] = query(a[i] - 1);
                add(a[i], dp[i][j - 1]);
            }
        }

        ll sum = 0;
        for(int i = 1; i <= n; i++) {
            sum = (sum + dp[i][m]) % mod;
        }
        sum = (sum + mod) % mod;
        printf("Case #%d: %lld\n", cas, sum);
    }
}