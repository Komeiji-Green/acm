#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1000000 + 5;
int n;
ll t[maxn<<2], lazy[maxn<<2];
void Pushup(int k) {
    t[k] = max(t[k<<1], t[k<<1|1]);
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
    if(l == r) {
        t[k] = l;
    } else {
        int m = ((l + r) >> 1);
        build(k<<1, l, m);
        build(k<<1|1, m + 1, r);
        Pushup(k);
    }
}

void update(int k, int L, int R, ll v, int l, int r) {
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
ll query(int k, int L, int R, int l, int r) {
    if(L <= l && r <= R) {
        return t[k];
    } else {
        int m = l + ((r - l) >> 1);
        Pushdown(k);
        ll res = 0;
        if(L <= m) res = max(res, query(k<<1, L, R, l, m));
        if(R > m) res = max(res, query(k<<1|1, L, R, m + 1, r));
        return res;
    }
}

struct BIT {
    ll C[maxn];
    void add(int x, ll v) {
        for(int i = x; i <= n; i += i & (-i)) C[i] += v;
    }
    ll query(int x) {
        ll res = 0;
        for(int i = x; i; i -= i & (-i)) res += C[i];
        return res;
    }
} T;

struct node {
    int x;
    ll len;
} a[maxn];
int main() {
    int q;
    cin >> q;
    n = 1000001;
    char op[4];
    int x, j;
    ll len, res, sum, dp, ans;
    build(1, 1, n);
    for(int i = 1; i <= q; ++i) {
        scanf("%s", op);
        if(op[0] == '+') {
            scanf("%d %lld", &x, &len);
            a[i].x = x; a[i].len = len;
            T.add(x, len);
            //update(1, x, x, x, 1, n);
            update(1, x + 1, n, -len, 1, n);
        } else if(op[0] == '-') {
            scanf("%d", &j);
            x = a[j].x; len = a[j].len;
            T.add(x, -len);
            //update(1, x, x, -x, 1, n);
            update(1, x + 1, n, len, 1, n);
        } else {
            scanf("%d", &x);
            res = query(1, 1, x, 1, n);
            sum = T.query(x);
            dp = res + sum;
            ans = dp <= x ? 0ll : dp - x;
            //printf("%lld %lld\n", res, sum);
            printf("%lld\n", ans);
        }
    }

}