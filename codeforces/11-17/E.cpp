#include<iostream>
using namespace std;
typedef long long ll;

const int maxn = 440000 + 5;
ll a[maxn], t[maxn<<2], lazy[maxn<<2], maxv[maxn<<2], minv[maxn<<2];
int n;
// 区间和
void Pushup(int k) {
    t[k] = t[k<<1] + t[k<<1|1];
    maxv[k] = max(maxv[k<<1], maxv[k<<1|1]);
    minv[k] = min(minv[k<<1], minv[k<<1|1]);
}
void marking(int k, int len, ll lz) {
    t[k] = len * lz;
    maxv[k] = minv[k] = lz;
    lazy[k] = max(lazy[k], lz);
}
void Pushdown(int k, int len1, int len2) {
    if(lazy[k]) {
        marking(k<<1, len1, lazy[k]);
        marking(k<<1|1, len2, lazy[k]);
        lazy[k] = 0;
    }
}
// 递归建树: 结点下标，结点对应的区间左右边界
void build(int k, int l, int r) {
    if(l == r) t[k] = maxv[k] = minv[k] = a[l];
    else {
        int m = l + ((r - l) >> 1);
        build(k<<1, l, m);
        build(k<<1|1, m + 1, r);
        Pushup(k);
    }
}
// 查询区间，结点下标及结点区间
ll sum; int cnt;
ll query(int L, int R, int k, int l, int r, ll cur) {
    if(cur > sum) return 0;
    if(L <= l && r <= R) {
        if(minv[k] + cur > sum) return 0;
        if(t[k] + cur <= sum) {
            cnt += r - l + 1; return t[k];
        }
        else if(l == r) return 0;
    }
    int m = l + ((r - l) >> 1);
    Pushdown(k, m - l + 1, r - m);
    ll ans = 0;
    if(L <= m) 
        ans += query(L, R, k << 1, l, m, cur);
    if(R > m) 
        ans += query(L, R, k << 1 | 1, m + 1, r, cur + ans); // [m + 1, r] [L, R]
    return ans;
}
// 区间更新
void update(int L, int R, ll v, int k, int l, int r) {
    if(L <= l && r <= R) {
        if(maxv[k] <= v) {
            marking(k, r-l+1, v); return;
        }
        else if(minv[k] >= v) return;
    }
    int m = l + ((r - l) >> 1);
    Pushdown(k, m - l + 1, r - m);
    if(L <= m)
        update(L, R, v, k << 1, l, m);
    if(R > m)
        update(L, R, v, k << 1 | 1, m + 1, r);
    Pushup(k);
}

int main() {
    int q;
    cin >> n >> q;
    for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
    build(1, 1, n);

    int op, x; ll y;
    while(q--) {
        scanf("%d %d %lld", &op, &x, &y);
        if(op == 1) {
            update(1, x, y, 1, 1, n);
        } else {
            sum = y; cnt = 0;
            query(x, n, 1, 1, n, 0);
            printf("%d\n", cnt);
        }
    }
}