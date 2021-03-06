#include<bits/stdc++.h>
using namespace std;
typedef int ll;

const int N = 233333;

int n;
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
} T;

int t[N<<2], a[N];
void pushup(int k) {
    t[k] = min(t[k<<1], t[k<<1|1]);
}
void build(int k, int l, int r) {
    if(l == r) t[k] = a[l];
    else {
        int m = ((l + r) >> 1);
        build(k<<1, l, m);
        build(k<<1|1, m + 1, r);
        pushup(k);
    }
}
int query(int k, int L, int R, int l, int r) {
    if(L <= l && r <= R) {
        return t[k];
    } else {
        int m = ((l + r) >> 1);
        int res = n + 1;
        if(L <= m) res = min(res, query(k<<1, L, R, l, m));
        if(R > m) res = min(res, query(k<<1|1, L, R, m + 1, r));
        return res;
    }
} 

int pv[N], last[N];
struct pr {
    int x, y;
};
vector<pr> vec[N];
int ans[N];
int main() {
    int q;
    cin >> n >> q;
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    build(1, 1, n);
    for(int i = 1; i <= n; ++i) {
        pv[i] = last[a[i]];
        last[a[i]] = i;
    }
    for(int i = 1, x, y; i <= q; ++i) {
        scanf("%d %d", &x, &y);
        vec[y].push_back((pr){x, i});
    } 
    for(int i = 1; i <= n; ++i) {
        int pre = pv[i];
        int minv = query(1, pre + 1, i, 1, n);
        //printf("%d: pv: %d, minv: %d\n", i, pre, minv);
        if(!pre) {
            T.add(1, 1);
            T.add(i + 1, -1);
        } else {
            if(minv >= a[i]) {
                T.add(pre + 1, 1);
                T.add(i + 1, -1);
            } else {
                T.add(1, 1);
                T.add(i + 1, -1);
            }
        }
        for(pr p : vec[i]) {
            int x = p.x, id = p.y;
            ans[id] = T.query(x);
        }
    }
    for(int i = 1; i <= q; ++i) {
        printf("%d\n", ans[i]);
    }
}

/*
8 4
1 2 2 1 1 2 3 2
4 6
3 6
1 6
5 8

2
3
3
3
*/