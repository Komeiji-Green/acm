#include<bits/stdc++.h>
using namespace std;
typedef int ll;

const int N = 200007;
const ll INF = 0x7fffffff;
ll a[N], mx[N<<2], se[N<<2], nu[N<<2], su[N<<2][30], xsu[N<<2];
void pushup(int k) {
    xsu[k] = xsu[k<<1] ^ xsu[k<<1|1];
    // 第i位为1的元素个数
    for(int i = 0; i < 30; ++i) su[k][i] = su[k<<1][i] + su[k<<1|1][i];
    mx[k] = min(mx[k<<1], mx[k<<1|1]); // 最小值（标记）
    ll tmp[4] = {mx[k<<1], mx[k<<1|1], se[k<<1], se[k<<1|1]};
    sort(tmp, tmp + 4); unique(tmp, tmp + 4);
    se[k] = tmp[1]; // 次小值（子树中的最小有效标记）
    nu[k] = 0; // 最小值个数
    if(mx[k<<1] == mx[k]) nu[k] += nu[k<<1];
    if(mx[k<<1|1] == mx[k]) nu[k] += nu[k<<1|1]; 
}
void build(int k, int l, int r) {
    if(l == r) {
        mx[k] = a[l]; se[k] = INF; nu[k] = 1; xsu[k] = a[l];
        for(int i = 0; i < 30; ++i) su[k][i] = ((a[l]>>i)&1);
    } else {
        int m = ((l + r) >> 1);
        build(k<<1, l, m);
        build(k<<1|1, m + 1, r);
        pushup(k);
    }
}
void marking(int k, ll x) {
    if(x > mx[k]) { // 一定有 se[k] > x
        int del;
        for(int i = 0; i < 30; ++i) {
            del = (((x>>i)&1) - ((mx[k]>>i)&1)) * nu[k];
            su[k][i] += del;
        }
        if(nu[k]&1) xsu[k]^=(x^mx[k]);
        mx[k] = x;
    }
}
void pushdown(int k) {
    marking(k<<1, mx[k]);
    marking(k<<1|1, mx[k]);
}
void update(int k, int L, int R, ll x, int l, int r) {
    if(L <= l && r <= R && se[k] > x) {
        marking(k, x);
    } else {
        pushdown(k);
        int m = ((l + r) >> 1);
        if(L <= m) update(k<<1, L, R, x, l, m);
        if(R > m) update(k<<1|1, L, R, x, m + 1, r);
        pushup(k); 
    }
}
ll querybit(int k, int L, int R, int b, int l, int r) {
    if(L <= l && r <= R) {
        return su[k][b];
    } else {
        pushdown(k);
        int m = ((l + r) >> 1);
        ll res = 0;
        if(L <= m) res += querybit(k<<1, L, R, b, l, m);
        if(R > m) res += querybit(k<<1|1, L, R, b, m + 1, r);
        return res;
    }
}
ll queryxor(int k, int L, int R, int l, int r) {
    if(L <= l && r <= R) {
        return xsu[k];
    } else {
        pushdown(k);
        int m = ((l + r) >> 1);
        ll res = 0;
        if(L <= m) res ^= queryxor(k<<1, L, R, l, m);
        if(R > m) res ^= queryxor(k<<1|1, L, R, m + 1, r);
        return res;
    }
}
int main() {
    int n, q;
    cin >> n >> q;
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    build(1, 1, n);

    int op, l, r;
    ll x;
    while(q--) {
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d %d %d", &l, &r, &x);
            update(1, l, r, x, 1, n);
        } else {
            scanf("%d %d %d", &l, &r, &x);
            ll sum = queryxor(1, l, r, 1, n), res;
            sum ^= x;
            int i;
            for(i = 29; i >= 0; --i) if((1<<i)&sum) break;
            if(i==-1) res = 0;
            else {
                res = querybit(1, l, r, i, 1, n) + ((x>>i)&1);
            }
            printf("%d\n", res);
        }
    }
}