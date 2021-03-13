#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 500007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
ll a[N], mx[N<<2], su[N<<2], se[N<<2], nu[N<<2];
void pushup(int k) {
    su[k] = su[k<<1] + su[k<<1|1]; // 区间和
    mx[k] = max(mx[k<<1], mx[k<<1|1]); // 最大值（标记）
    ll tmp[4] = {mx[k<<1], mx[k<<1|1], se[k<<1], se[k<<1|1]};
    sort(tmp, tmp + 4, greater<ll>()); unique(tmp, tmp + 4, greater<ll>());
    se[k] = tmp[1]; // 次大值（子树中的最大有效标记）
    nu[k] = 0; // 最大值个数
    if(mx[k<<1] == mx[k]) nu[k] += nu[k<<1];
    if(mx[k<<1|1] == mx[k]) nu[k] += nu[k<<1|1]; 
}
void build(int k, int l, int r) {
    if(l == r) {
        mx[k] = a[l]; su[k] = a[l]; se[k] = -INF; nu[k] = 1;
    } else {
        int m = ((l + r) >> 1);
        build(k<<1, l, m);
        build(k<<1|1, m + 1, r);
        pushup(k);
    }
}
void marking(int k, ll x) {
    if(x < mx[k]) { // 一定有 se[k] < x
        su[k] -= (mx[k]-x)*nu[k];
        mx[k] = x;
    }
}
void pushdown(int k) {
    marking(k<<1, mx[k]);
    marking(k<<1|1, mx[k]);
}
void update(int k, int L, int R, ll x, int l, int r) {
    if(L <= l && r <= R && se[k] < x) {
        marking(k, x);
    } else {
        pushdown(k);
        int m = ((l + r) >> 1);
        if(L <= m) update(k<<1, L, R, x, l, m);
        if(R > m) update(k<<1|1, L, R, x, m + 1, r);
        pushup(k); 
    }
}
ll query(int k, int L, int R, int l, int r) {
    if(L <= l && r <= R) {
        return su[k];
    } else {
        pushdown(k);
        int m = ((l + r) >> 1);
        ll res = 0;
        if(L <= m) res += query(k<<1, L, R, l, m);
        if(R > m) res += query(k<<1|1, L, R, m + 1, r);
        return res;
    }
}
int main() {
    int n, q;
    cin >> n >> q;
    for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
    build(1, 1, n);

    int op, l, r;
    ll x;
    while(q--) {
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d %d %lld", &l, &r, &x);
            update(1, l, r, x, 1, n);
        } else {
            scanf("%d %d", &l, &r);
            ll res = query(1, l, r, 1, n);
            printf("%lld\n", res);
        }
    }
}