
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1000007, inf = 0x3f3f3f3f;
int a[N], t[N<<2], lp[N<<2], rp[N<<2];
// 区间最小值
void Pushup(int k) {
    if(t[k<<1] <= t[k<<1|1]) lp[k] = lp[k<<1];
    else lp[k] = lp[k<<1|1];
    if(t[k<<1|1] <= t[k<<1]) rp[k] = rp[k<<1|1];
    else rp[k] = rp[k<<1];
    t[k] = min(t[k<<1], t[k<<1|1]);
}
void build(int k, int l, int r) {
    if(l == r) t[k] = a[l], lp[k] = l, rp[k] = l;
    else {
        int m = ((l + r) >> 1);
        build(k<<1, l, m);
        build(k<<1|1, m + 1, r);
        Pushup(k);
    }
}
int query(int k, int L, int R, int l, int r) {
    if(L <= l && r <= R) return t[k];
    else {
        int m = ((l + r) >> 1);
        int res = inf;
        if(L <= m) res = min(res, query(k<<1, L, R, l, m));
        if(R > m) res = min(res, query(k<<1|1, L, R, m + 1, r));
        //Pushup(k);
        return res;
    }
}
int query(int k, int L, int R, int l, int r, int &lpos, int &rpos) {
    if(L <= l && r <= R) {
        lpos = lp[k]; rpos = rp[k]; return t[k];
    } else {
        int m = ((l + r) >> 1);
        int l1, r1, l2, r2;
        int lmin = inf, rmin = inf;
        if(L <= m) lmin = query(k<<1, L, R, l, m, l1, r1);
        if(R > m) rmin = query(k<<1|1, L, R, m + 1, r, l2, r2);
        if(lmin <= rmin) lpos = l1;
        else lpos = l2;
        if(rmin <= lmin) rpos = r2;
        else rpos = r1;
        //Pushup(k);
        return min(lmin, rmin);
    }
}
int le[N], ri[N], tp[N], minv[N], ans[N];
void chk(int &y, int w) {
    if(!w) y = w;
}
ll x[N];
int main() {
    int n, k;
    cin >> n >> k;
    for(int i = 1; i <= k; ++i) {
        scanf("%d %d %lld", &le[i], &ri[i], &x[i]);
        ans[i] = 1;
    }
    for(int b = 0; b < 60; ++b) {
        for(int i = 1; i <= n; ++i) a[i] = 0;
        for(int i = 1; i <= k; ++i) {
            if((1ll<<b)&x[i]) { // type 1
                tp[i] = 1;
                a[le[i]] += 1; a[ri[i] + 1] -= 1;
            } else {
                tp[i] = 2;
            }
        }
        a[n+1] = 0;
        for(int i = 1; i <= n; ++i) a[i] += a[i-1];

        build(1, 1, n);
        int cnt = 0, bad = 0;
        int rmin = n, lmax = 1;
        for(int i = 1; i <= k; ++i) {
            if(tp[i] == 2) {
                minv[i] = query(1, le[i], ri[i], 1, n);
                if(minv[i]) ++cnt;
                if(minv[i] >= 2) bad = 1;
                if(minv[i] == 1) {
                    rmin = min(rmin, ri[i]);
                    lmax = max(lmax, le[i]);
                }
            }
        }
        for(int i = 1; i <= k; ++i) {
            if(tp[i] == 2) {
                if(cnt >= 2) chk(ans[i], 0);
                else if(cnt == 0) chk(ans[i], 1);
                else if(minv[i]) chk(ans[i], 1);
                else chk(ans[i], 0);
            }
        }
        int lpos, rpos;
        for(int i = 1; i <= k; ++i) {
            if(tp[i] == 1){
                if(bad) chk(ans[i], 0);
                else if(!cnt) chk(ans[i], 1);
                else {
                    minv[i] = query(1, le[i], ri[i], 1, n, lpos, rpos);
                    if(minv[i] >= 2) {
                        if(cnt == 0) chk(ans[i], 1);
                        else chk(ans[i], 0);
                    } else { // minv[i] == 1
                        //printf("%d: lpos=%d, rpos=%d\n", i, lpos, rpos);
                        if(lpos <= rmin && rpos >= lmax) chk(ans[i], 1);
                        else chk(ans[i], 0);
                    }
                }
            }
        }
       // printf("%d\n", b);
        //printf("L: %d, R: %d\n", lmax, rmin);
        //for(int i = 1; i <= k; ++i) printf("%d ", minv[i] = query(1, le[i], ri[i], 1, n));
        //printf("\n");
    }
    for(int i = 1; i <= k; ++i) {
        printf("%d",ans[i]);
    }
    printf("\n");
}