#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 4005;
struct Seg {
    int l, r, mid;
    bool operator<(const Seg& b) {
        return mid < b.mid;
    }
} seg[maxn];
ll dp1[maxn][maxn], dp2[maxn][maxn];


ll calc(int l1, int r1, int l2 ,int r2) {
    int l = max(l1, l2), r = min(r1, r2);
    return (l <= r) ? r - l + 1 : 0;
}

int pos[maxn];
int main() {
    int n, m, k;
    cin >> n >> m >> k;
    for(int i = 1, l, r; i <= m; ++i) {
        scanf("%d%d", &l, &r);
        l = 2 * l - 1; r = 2 * r;
        seg[i].l = l; seg[i].r = r;
        seg[i].mid = (l + r) / 2;
    }
    n = 2 * n; k = 2 * k;
    sort(seg + 1, seg + m + 1);
    for(int i = 1; i <= m; ++i) pos[i] = seg[i].mid;
    for(int i = 1; i <= (n - k + 1); ++i) {
        dp1[i][0] = 0;
        for(int j = 1; j <= m; ++j) {
            dp1[i][j] = calc(i, i + k - 1, seg[j].l, seg[j].r) + dp1[i][j-1];
        }
        for(int j = 1; j <= m; ++j) {
            dp2[i][j] = dp1[i][m] - dp1[i][j - 1];
        }
    }

    ll ans = 0, cur = 0;
    int tt = (n - k + 1);
    for(int i = 1; i <= tt; i += 2) {
        for(int j = i; j <= tt; j += 2) {
            int md1 = (i + i + k - 1) / 2, md2 = (j + j + k - 1) / 2;
            int mmid = (md1 + md2) / 2;
            int idx = upper_bound(pos + 1, pos + m + 1, mmid) - pos;
            cur = dp1[i][idx - 1] + dp2[j][idx];
            ans = max(cur, ans);
        }
    }
    printf("%lld\n", ans / 2);
}