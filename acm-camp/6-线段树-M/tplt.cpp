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
ll sum, pos;
ll query(int L, int R, int k, int l, int r, ll cur) {
    if(l >= L && r <= R && t[k] + cur <= sum)
        return t[k];
    else if(l == r) {
        // t[k] + cur > sum
        pos = l;
        return t[k];
    }
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

int A[maxn][maxn], C[maxn][maxn], n;  // 二维树状数组
// C[i][j] 看管 (i - lowbit(i), j - lowbit(j)) 到 (i, j) 间的点
void add(int x, int y, int v) {
    for(int i = x; i <= n; i += i & (-i))
        for(int j = y; j <= n; j += j & (-j))
            C[i][j] ^= v;
}
int query(int x, int y) {
    int ans = 0;
    for(int i = x; i > 0; i -= i & (-i))
        for(int j = y; j > 0; j -= j & (-j))
            ans ^= C[i][j];
    return ans;
}


const int N = 300007;
struct ST {
    int su[N*20], lch[N*20], rch[N*20], tot;
    void init() {
        for(int i = 0; i <= tot; ++i) su[i] = 0, lch[i] = 0, rch[i] = 0;
        tot = 0;
    }
    void pushup(int k) {
        su[k] = su[lch[k]] + su[rch[k]];
    }
    void update(int &k, int x, int v, int l, int r) {
        if(!k) k = ++tot;
        if(l == r) {
            su[k] += v;
        } else {
            int m = ((l + r) >> 1);
            if(x <= m) update(lch[k], x, v, l, m);
            else update(rch[k], x, v, m + 1, r);
            pushup(k);
        }
    }
    int query(int k, int L, int R, int l, int r) {
        if(!k) return 0;
        if(L <= l && r <= R) {
            return su[k];
        } else {
            int m = ((l + r) >> 1);
            int res = 0;
            if(L <= m) res += query(lch[k], L, R, l, m);
            if(R > m) res += query(rch[k], L, R, m+1, r);
            return res;
        }
    }
} tr, tc;

struct BIT {
    ll C[N];
    void add(int x, ll v) {
        for(int i = x; i <= n; i += i & (-i)) C[i] += v;
    }
    ll query(int x) {
        ll res = 0;
        for(int i = x; i; i -= i & (-i)) res += C[i];
        return res;
    }
} Ta[2], Tb[2];