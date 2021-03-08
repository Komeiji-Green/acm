#include<bits/stdc++.h>
#include<cmath>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int N = 333333;
const int base = 19260817, mod = 998244353;
int h1[N], h2[N], pb[N];
int n, m;
int getlcp(int x, int y) {
    int le = 0, ri = min(n-x+1, m-y+1);
    int mid = ((le + ri + 1) >> 1);
    while(le < ri) {
        if(((h1[x+mid-1] + mod - 1ll * h1[x-1] * pb[mid] % mod) -
           (h2[y+mid-1] + mod - 1ll * h2[y-1] * pb[mid] % mod)) % mod == 0) {
            le = mid;
        } else {
            ri = mid - 1;
        }
        mid = ((le + ri + 1) >> 1);
    }
    return mid;
}

int L[N], R[N]; double p[N][11], pre[N], ans[N];
int a[N], b[N];


int main() {
    int T, l, r, tmp;
    cin >> T;
    pb[0] = 1; for(int i = 1; i < N; ++i) pb[i] = 1ll * base * pb[i-1] % mod;
    for(int cas = 1; cas <= T; ++cas) {
        scanf("%d %d", &n, &m);
        for(int x = 1; x <= n; ++x) {
            scanf("%d %d", &l, &r);
            double mm = 0.0;
            for(int i = l; i <= r; ++i) {
                scanf("%d", &tmp);
                p[x][i-l] = (double)(tmp) / 1e9;
                if(p[x][i-l] > mm) a[x] = i, mm = p[x][i-l];
            }
            L[x] = l, R[x] = r;
        }
        pre[0] = 0.0;
        for(int i = 1; i <= n; ++i) pre[i] = pre[i-1] + log(p[i][a[i]-L[i]]);
        for(int i = 1; i <= m; ++i) {
            scanf("%d", &b[i]);
        }
        h1[0] = h2[0] = 0;
        for(int i = 1; i <= n; ++i) h1[i] = (1ll * h1[i-1] * base % mod + a[i]) % mod;
        for(int i = 1; i <= m; ++i) h2[i] = (1ll * h2[i-1] * base % mod + b[i]) % mod;

        //printf("a: "); for(int x = 1; x <= n; ++x) printf("%d ", a[x]); printf("\n");

        for(int x = 1; x <= n-m+1; ++x) {
            ans[x] = 1.0;
            int i = x, j = 1, cnt = 0;
            for(;i <= n && j <= m && cnt < 33; ++i, ++j, ++cnt) {
                if(ans[x] < 5e-10) break;
                int len = getlcp(i, j);
                ans[x] *= exp(pre[i+len-1] - pre[i-1]);
                //printf("x=%d: %d %d %d\n", x, i, j, len);
                i += len, j += len;
                if(i <= n && j <= m)
                    ans[x] *= (L[i] <= b[j] && b[j] <= R[i]) ? p[i][b[j]-L[i]] : 0.0;
            }
            if(cnt >= 33) ans[x] = 0.0;
        }
        printf("Case #%d:\n", cas);
        for(int x = 1; x <= n - m + 1; ++x) {
            printf("%.15f\n", fabs(ans[x]));
        }

    }
}