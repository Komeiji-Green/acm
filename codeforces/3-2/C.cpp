#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 333333;
const int inf = 0x3f3f3f3f;

ll a[maxn], b[maxn], c[maxn];

// 0 1
// 3 2
ll pre(ll *a, int len, ll key) {
    int idx = upper_bound(a + 1, a + len + 1, key) - a - 1;
    return idx;
}
int m;

int sum[maxn], pos[maxn];
int gao(int tot) {
    for(int i = 1; i <= tot; ++i) {
        pos[i] = c[i] - i + 1;
    }
    sum[tot+1] = 0;
    for(int i = tot; i >= 1; --i) {
        int idx = lower_bound(b + 1, b + m + 1, c[i]) - b;
        if(idx <= m && b[idx] == c[i]) sum[i] = sum[i+1] + 1;
        else sum[i] = sum[i+1];
    }
    int ans = 0, cur = 0;
    for(int j = 1; j <= m; ++j) {
        int idx = upper_bound(pos + 1, pos + tot + 1, b[j]) - pos - 1;
        if(idx == 0) cur = sum[1];
        else {
            cur = sum[idx + 1];
            cur += pre(b, m, b[j] + idx - 1) - pre(b, m, b[j] - 1);
        }
        ans = max(ans, cur);
    }
    return ans;
}
int main() {
    int T, n;
    cin >> T;
    while(T--) {
        scanf("%d %d", &n, &m);
        for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
        for(int i = 1; i <= m; ++i) scanf("%lld", &b[i]);
        int cnt = 0, tot = 0;
        for(int i = 1; i <= n; ++i) {
            if(a[i] < 0) ++cnt;
            else c[++tot] = a[i];
        }
        int res = gao(tot);
        tot = 0;
        for(int i = cnt; i >= 1; --i) c[++tot] = -a[i];
        for(int i = 1; i <= m; ++i) b[i] = -b[i];
        sort(b + 1, b + m + 1);
        res += gao(tot);
        printf("%d\n", res);

        /*
        sum[0] = 0;
        for(int i = 1; i <= cnt; ++i) {
            if((pre(b, m, a[i]) - pre(b, m, a[i]-1)) > 0) sum[i] = sum[i-1] + 1;
            else sum[i] = sum[i-1];
        }
        int cur, ans = 0;
        for(int i = 1; i <= cnt; ++i) {
            int idx = lower_bound(b + 1, b + m + 1, a[i]) - b;
            for(int j = idx; j <= m; ++j) {
                if(i+1<=cnt && b[j] >= a[i+1]) break;
                cur = sum[i-1] + pre(b[j] + (cnt - i))
            }
            cur = sum[i-1] + 
        }*/
    }
}