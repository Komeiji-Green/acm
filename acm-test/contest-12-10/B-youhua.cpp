#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int maxn = 233333;
ll a[maxn];
int n;

ull psum[maxn], msum[maxn], csum[maxn];
void add(int idx, ull vp, ull vm, ull cm) {
    for(int i = idx; i <= n; i += i & (-i)) psum[i] += vp, msum[i] += vm, csum[i] += cm;
}
void query(int idx, ull& vp, ull& vm, ull& cm) {
    vp = vm = cm = 0ull;
    for(int i = idx; i; i -= i & (-i)) vp += psum[i], vm += msum[i], cm += csum[i];
}

struct sbd {
    ll key; int id;
    bool operator<(const sbd& b) { return key < b.key; }
};

ll pre[maxn];
ll prer[maxn], mssr[maxn], prel[maxn], mssl[maxn], maxr[maxn], maxl[maxn];
ull ans;
ll lsh[maxn]; int id2[maxn];
sbd uu[maxn]; int tot = 0;
void gao(int l, int r) {
    if(l == r) { ans += a[l]; return; }
    int m = (l + r) >> 1;
    maxr[m+1] = mssr[m+1] = prer[m+1] = a[m+1];
    for(int i = m + 2; i <= r; ++i) maxr[i] = a[i] + max(maxr[i-1], 0ll);
    for(int i = m + 2; i <= r; ++i) mssr[i] = max(mssr[i-1], maxr[i]);
    for(int i = m + 2; i <= r; ++i) prer[i] = max(pre[i]-pre[m], prer[i-1]);
    maxl[m] = mssl[m] = prel[m] = a[m];
    for(int i = m - 1; i >= l; --i) maxl[i] = a[i] + max(maxl[i+1], 0ll);
    for(int i = m - 1; i >= l; --i) mssl[i] = max(mssl[i+1], maxl[i]);
    for(int i = m - 1; i >= l; --i) prel[i] = max(pre[m]-pre[i-1], prel[i+1]);

    for(int i = m + 1; i <= r; ++i) lsh[i] = mssr[i] - prer[i];
    sort(lsh + m + 1, lsh + r + 1);
    for(int i = m + 1; i <= r; ++i) id2[i] = lower_bound(lsh + m + 1, lsh + r + 1, mssr[i] - prer[i]) - lsh;

    tot = 0;
    for(int i = m; i >= l; --i) {
        int bd1 = upper_bound(prer + m + 1, prer + r + 1, mssl[i] - prel[i]) - prer - 1;
        int bd2 = upper_bound(mssr + m + 1, mssr + r + 1, mssl[i]) - mssr - 1;
        ++tot; uu[tot].key = min(bd1, bd2);
        uu[tot].id = i;
    }
    sort(uu + 1, uu + tot + 1);
    for(int i = m + 1; i <= r; ++i) add(id2[i], prer[i], mssr[i], 1);
    int t = m + 1;
    ull cnt, pp, mm, cc, pp1,mm1,cc1;
    for(int i = 1, id; i <= tot; ++i) {
        while(t <= r && t <= uu[i].key) {
            add(id2[t], -prer[t], -mssr[t], -1); ++t;
        }
        id = uu[i].id;
        cnt = t - (m + 1);
        ans += cnt * (ull)mssl[id];
        int bd = upper_bound(lsh + m + 1, lsh + r + 1, prel[id]) - lsh - 1;
        query(bd, pp1, mm1, cc1); query(n, pp, mm, cc);
        ans += cc1 * (ull)(prel[id]) + pp1;
        mm -= mm1; ans += mm;
    }

    while(t <= r) {
        add(id2[t], -prer[t], -mssr[t], -1); ++t;
    }

    gao(l, m); gao(m + 1, r);
}

int main() {
    cin >> n;
    for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
    pre[0] = 0;
    for(int i = 1; i <= n; ++i) pre[i] = pre[i-1] + a[i];
    gao(1, n);
    cout << ans << endl;
}