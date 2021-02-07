#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = (1<<18) + 50;
ll t[maxn<<2], a[maxn];
int st[50], bit[maxn];
void Pushup(int k) {
    t[k] = t[k<<1] + t[k<<1|1];
}
void build(int k, int l, int r) {
    //int d = bit[r-l+1];
    if(l == r) {
        t[k] = a[l];
    } else {
        int m = ((l + r) >> 1);
        build(k<<1, l, m);
        build(k<<1|1, m + 1, r);
        Pushup(k);
    }
}
void update(int k, int x, ll v, int l, int r) {
    int d = bit[r - l + 1];
    if(l == r) t[k] = v;
    else {
        int m = ((l + r) >> 1);
        int lch = (k<<1), rch = (k<<1|1);
        if(st[d]) swap(lch, rch);
        if(x <= m) update(lch, x, v, l, m);
        else update(rch, x, v, m + 1, r);
        Pushup(k);
    }
}
ll query(int k, int L, int R, int l, int r) {
    int d = bit[r - l + 1];
    if(L <= l && r <= R) {
        return t[k];
    } else {
        int lch = (k<<1), rch = (k<<1|1);
        if(st[d]) swap(lch, rch);
        ll res = 0;
        int m = ((l + r) >> 1);
        if(L <= m) res += query(lch, L, R, l, m);
        if(R > m) res += query(rch, L, R, m + 1, r);
        return res;
    }
}
int main() {
    int n, q, op;
    cin >> n >> q;
    int len = (1<<n);
    for(int i = 1; i <= len; ++i) scanf("%lld", &a[i]);
    int x, k, l, r;
    for(int i = 0; i <= 18; ++i) bit[1<<i] = i;
    build(1, 1, len);
    while(q--) {
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d %d", &x, &k);
            update(1, x, k, 1, len);
        } else if(op == 2) {
            scanf("%d", &k);
            for(int i = 0; i <= k; ++i) st[i] ^= 1;
        } else if(op == 3) {
            scanf("%d", &k);
            st[k+1] ^= 1;
        } else {
            scanf("%d %d", &l, &r);
            ll res = query(1, l, r, 1, len);
            printf("%lld\n", res);
        }

    }
}