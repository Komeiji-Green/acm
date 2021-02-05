#include<bits/stdc++.h>
using namespace std;
typedef int ll;

const int maxn = 333333;
const int inf = 0x3f3f3f3f;

ll t[maxn<<2], lazy[maxn<<2];
// 区间和
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

int pos;
void bsearch(int k, ll key, int l, int r) {
    if(l == r) pos = l;
    else {
        int m = ((l + r) >> 1);
        Pushdown(k);
        if(key <= t[k<<1|1]) bsearch(k<<1|1, key, m + 1, r);
        else if(key <= t[k<<1]) bsearch(k<<1, key, l, m);
        else return;
    }
}

int n, a[maxn], req[maxn], p[maxn];

struct ST {
    vector<int> vec[maxn<<2];
    void build(int k, int l, int r) {
        for(int i = l; i <= r; ++i) {
            vec[k].push_back(p[i]);
        }
        sort(vec[k].begin(), vec[k].end());
        if(l == r) return;
        int m = ((l + r) >> 1);
        build(k<<1, l, m); build(k<<1|1, m + 1, r);
    }
    int query(int k, int L, int R, int key, int l, int r) {
        if(L <= l && r <= R) {
            int num = vec[k].end() - lower_bound(vec[k].begin(), vec[k].end(), key);
            return num;
        } else {
            int m = ((l + r) >> 1);
            int res = 0;
            if(L <= m) res += query(k<<1, L, R, key, l, m);
            if(R > m) res += query(k<<1|1, L, R, key, m + 1, r);
            return res;
        }
    }
} T;
int main() {
    int q;
    cin >> n >> q;
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for(int i = 1; i <= n; ++i) req[i] = i - a[i];
    for(int i = 1; i <= n; ++i) {
        if(req[i] < 0) p[i] = -1;
        else {
            pos = -1;
            bsearch(1, req[i], 0, n);
            if(pos >= 0) pos = min(pos, i - 1);
            if(pos >= 0) update(1, 0, pos, 1, 0, n);
            if(pos < 0) p[i] = -1;
            else p[i] = pos;
        }
    }
    //printf("test:\n");
    //for(int i = 1; i <= n; ++i) printf("(%d: %d) ", req[i], p[i]); printf("\n");
    T.build(1, 1, n);
    while(q--) {
        int x, y;
        scanf("%d %d", &x, &y);
        int le = x, ri = n - y;
        int res = T.query(1, le + 1, ri, le, 1, n);
        printf("%d\n", res);
    }
}