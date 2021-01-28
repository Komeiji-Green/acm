#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
typedef long long ll;

const ll mod = 10007;
const int maxn = 100000 + 5;
struct Val {
    ll a[4];
    Val operator+ (const Val &rhs) {
        Val ans;
        for(int i = 0; i < 4; i++) {
            ans.a[i] = (a[i] + rhs.a[i]) % mod;
        }
        return ans;
    }
} t[maxn << 2], _0;

struct Lazy {
    Lazy():a(1), b(0) {}
    ll a, b;
    Lazy operator* (const Lazy &rhs) {  // 对应映射的复合
        Lazy ret;
        ret.a = a * rhs.a % mod;
        ret.b = (a * rhs.b + b) % mod;
        return ret;
    }
    Val func(Val x) { // 懒标记对权值向量的影响（矩阵：向量变换）
        Val y;
        y.a[0] = x.a[0];
        y.a[1] = a * x.a[1] + b * x.a[0];
        y.a[2] = a * a * x.a[2] + 2 * a * b * x.a[1] + b * b * x.a[0];
        y.a[3] = a * a * a * x.a[3] + 3 * a * a * b * x.a[2] + 3 * a * b * b * x.a[1] + b * b * b * x.a[0];
        for(int i = 0; i < 4; i++) y.a[i] %= mod;
        return y;
    }
} lazy[maxn<<2], e;

// 区间和
void Pushup(int k) {
    t[k] = t[k<<1] + t[k<<1|1];
}
void marking(int k, int len, Lazy lz) {
    lazy[k] = lz * lazy[k];
    t[k] = lz.func(t[k]);
}
void Pushdown(int k, int len1, int len2) {
    marking(k<<1, len1, lazy[k]);
    marking(k<<1|1, len2, lazy[k]);
    lazy[k] = e;
}

// 递归建树: 结点下标，结点对应的区间左右边界
void build(int k, int l, int r) {
    lazy[k] = e;
    if(l == r) t[k].a[0] = 1;
    else {
        int m = l + ((r - l) >> 1);
        build(k<<1, l, m);
        build(k<<1|1, m + 1, r);
        Pushup(k);
    }
}

// 查询区间，结点下标及结点区间
Val query(int L, int R, int k, int l, int r) {
    if(l >= L && r <= R)
        return t[k];
    else {
        int m = l + ((r - l) >> 1);
        Pushdown(k, m - l + 1, r - m);
        Val ans = _0;
        if(L <= m) 
            ans = ans + query(L, R, k << 1, l, m);
        if(R > m) 
            ans = ans + query(L, R, k << 1 | 1, m + 1, r); // [m + 1, r] [L, R]
        return ans;
    }
}
// 区间更新
void update(int L, int R, Lazy v, int k, int l, int r) {
    if(L <= l && r <= R) {
        lazy[k] = v * lazy[k];
        t[k] = v.func(t[k]);
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

int main() {
    int n, m;
    while(scanf("%d %d", &n, &m) != EOF && n && m) {
        memset(t, 0, sizeof(t));
        build(1, 1, n);
        int op, l, r, p;
        ll c;
        while(m--) {
            scanf("%d", &op);
            if(op >= 1 && op <= 3) {
                scanf("%d %d %lld", &l, &r, &c);
                Lazy v;
                if(op == 1) {
                    v.a = 1, v.b = c;
                } else if(op == 2) {
                    v.a = c, v.b = 0;
                } else if(op == 3) {
                    v.a = 0, v.b = c;
                }
                update(l, r, v, 1, 1, n);
            } else {
                scanf("%d %d %d", &l, &r, &p);
                Val ans = query(l, r, 1, 1, n);
                printf("%lld\n", ans.a[p]);
            }
        }
    }
}