#include<iostream>
using namespace std;
typedef long long ll;

const int maxn = 100000 + 5;
ll a[maxn], t[maxn<<2], lazy[maxn<<2];

// 区间和
void Pushup(int k) {
    t[k] = t[k<<1] + t[k<<1|1];
}
void Pushdown(int k, int len1, int len2) {
    if(lazy[k]) {
        lazy[k << 1] += lazy[k];
        lazy[k << 1 | 1] += lazy[k];
        t[k << 1] += lazy[k] * 1ll * len1;
        t[k << 1 | 1] += lazy[k] * 1ll * len2;
        lazy[k] = 0;
    }
}
// 递归建树: 结点下标，结点对应的区间左右边界
void build(int k, int l, int r) {
    if(l == r) t[k] = a[l];
    else {
        int m = l + ((r - l) >> 1);
        build(k<<1, l, m);
        build(k<<1|1, m + 1, r);
        Pushup(k);
    }
}
// 查询区间，结点下标及结点区间
ll query(int L, int R, int k, int l, int r) {
    if(l >= L && r <= R)
        return t[k];
    else {
        int m = l + ((r - l) >> 1);
        Pushdown(k, m - l + 1, r - m);
        ll ans = 0;
        if(L <= m) 
            ans += query(L, R, k << 1, l, m);
        if(R > m) 
            ans += query(L, R, k << 1 | 1, m + 1, r); // [m + 1, r] [L, R]
        return ans;
    }
}
// 区间更新
void update(int L, int R, ll v, int k, int l, int r) {
    if(L <= l && r <= R) {
        lazy[k] += v;
        t[k] += v * (r - l + 1);
    } else {
        int m = l + ((r - l) >> 1);
        Pushdown(k, m - l + 1, r - m);
        if(L <= m)
            update(L, R, v, k << 1, l, m);
        if(R > m)
            update(L, R, v, k << 1 | 1, m + 1, r);
        Pushup(k);
    }
}


int main()
{
    int n, q;
    cin >> n >> q;

    for(int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);

    build(1, 1, n);
    char op[4];
    int l, r;
    ll v;
    while(q--) {
        scanf("%s", op);
        if(op[0] == 'Q') {
            scanf("%d%d",&l,&r);
            printf("%lld\n", query(l, r, 1, 1, n));
        } else {
            scanf("%d%d%lld", &l,&r,&v);
            update(l, r, v, 1, 1, n);
        }
    }
}