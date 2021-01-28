#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int maxn = 233333;
ll a[maxn];
int n;

struct SegTree {
    ull cnt[maxn*100], psum[maxn*100], msum[maxn*100];
    int ch[maxn*100][2], tot;
    void Pushup(int k) {
        int l = ch[k][0], r = ch[k][1];
        cnt[k] = cnt[l]+cnt[r]; psum[k] = psum[l] + psum[r]; msum[k] = msum[l] + msum[r];
    }
    int idx; ull vp, vm;
    void addproc(int &k, int l, int r) {
        if(!k) k = ++tot;
        if(l == r) {
            ++cnt[k]; psum[k] += vp; msum[k] += vm;
        } else {
            int m = (l + r) >> 1;
            if(idx <= m) addproc(ch[k][0], l, m);
            else addproc(ch[k][1], m + 1, r);
            Pushup(k);
        }
    }
    void add(int &k, int _idx, ull _vp, ull _vm) {
        idx = _idx; vp = _vp; vm = _vm; addproc(k, 1, n);
    }
    ull cres, pres, mres; int L, R;
    void queryproc(int k, int l, int r) {
        if(!k) return;
        if(L <= l && r <= R) {
            cres += cnt[k]; pres += psum[k]; mres += msum[k];
        } else {
            int m = (l + r) >> 1;
            if(L <= m) queryproc(ch[k][0], l, m);
            if(R > m) queryproc(ch[k][1], m + 1, r);
        }
    }
    void query(int k, int _L, int _R, ull& _cres, ull& _pres, ull& _mres) {
        L = _L; R = _R; cres = pres = mres = 0ull;
        queryproc(k, 1, n); _cres = cres; _pres = pres; _mres = mres;
    }
    void clear() {
        for(int i = 0; i <= tot; ++i) cnt[i] = psum[i] = msum[i] = ch[i][0] = ch[i][1] = 0ull;
        tot = 0;
    }
} ST;

int rt[maxn];
void add(int id1, int id2, ull vp, ull vm) {
    for(register int i = id1; i <= n; i += i & (-i)) ST.add(rt[i], id2, vp, vm);
}
void query(int id1, int id2l, int id2r, ull& _cres, ull& _pres, ull& _mres) {
    ull c1, c2, c3; _cres = _pres = _mres = 0ull;
    for(register int i = id1; i; i -= i & (-i)) {
        ST.query(rt[i], id2l, id2r, c1, c2, c3); _cres += c1; _pres += c2; _mres += c3;
    }
}


ll pre[maxn];
ll prer[maxn], mssr[maxn], prel[maxn], mssl[maxn], maxr[maxn], maxl[maxn];
ull ans;
ll lsh[maxn]; int id2[maxn];
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
    for(int i = m + 1; i <= r; ++i) add(i, id2[i], prer[i], mssr[i]);

    ull cnt, psum, msum, cnt1, psum1, msum1;
    for(int i = m; i >= l; --i) {
        int bd1 = upper_bound(prer + m + 1, prer + r + 1, mssl[i] - prel[i]) - prer - 1;
        int bd2 = upper_bound(mssr + m + 1, mssr + r + 1, mssl[i]) - mssr - 1;
        int mbd = min(bd1, bd2);
        int uu = upper_bound(lsh + m + 1, lsh + r + 1, prel[i]) - lsh - 1;
        query(mbd, 1, n, cnt, psum, msum); ans += cnt * (ull)mssl[i];
        query(bd1, 1, uu, cnt, psum, msum); query(n, 1, uu, cnt1, psum1, msum1);
        cnt = cnt1 - cnt; psum = psum1 - psum; ans += cnt * (ull)prel[i] + psum;
        query(bd2, uu + 1, n, cnt1, psum1, msum1); query(n, uu + 1, n, cnt, psum, msum);
        msum -= msum1; ans += msum;
    }
    for(int i = 1; i <= n; ++i) rt[i] = 0;
    ST.clear();

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