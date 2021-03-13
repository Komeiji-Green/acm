#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1000007, inf = 0x3f3f3f3f;
int a[N], t[N<<2], lazy[N<<2], lp[N<<2], rp[N<<2];
// 区间最小值
void Pushup(int k) {
    if(t[k<<1] <= t[k<<1|1]) lp[k] = lp[k<<1];
    else lp[k] = lp[k<<1|1];
    if(t[k<<1|1] <= t[k<<1]) rp[k] = rp[k<<1|1];
    else rp[k] = rp[k<<1];
    t[k] = min(t[k<<1], t[k<<1|1]);
}
void Pushdown(int k) {
    if(lazy[k]) {
        lazy[k << 1] += lazy[k];
        lazy[k << 1 | 1] += lazy[k];
        t[k << 1] += lazy[k];
        t[k << 1 | 1] += lazy[k];
        lazy[k] = 0;
    }
}
void build(int k, int l, int r) {
    lazy[k] = 0;
    if(l == r) t[k] = a[l], lp[k] = l, rp[k] = l;
    else {
        int m = l + ((r - l) >> 1);
        build(k<<1, l, m);
        build(k<<1|1, m + 1, r);
        Pushup(k);
    }
}
int query(int k, int L, int R, int l, int r) {
    if(L <= l && r <= R) return t[k];
    else {
        int m = l + ((r - l) >> 1);
        Pushdown(k);
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
        int m = l + ((r - l) >> 1);
        Pushdown(k);
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
void update(int k, int L, int R, int v, int l, int r) {
    if(L <= l && r <= R) {
        lazy[k] += v;
        t[k] += v;
    } else {
        int m = l + ((r - l) >> 1);
        Pushdown(k);
        if(L <= m) update(k<<1, L, R, v, l, m);
        if(R > m) update(k<<1|1, L, R, v, m + 1, r);
        Pushup(k);
    }
}

int main() {
    int n, q, op, l, r;
    cin >> n >> q;
    while(q--) {
        scanf("%d %d %d", &op, &l, &r);
        if(op == 1) {
            update(1, l, r, 1, 1, n);
        } else {
            int res = query(1, l, r, 1, n);
            printf("%d\n", res);
        }
    }
}