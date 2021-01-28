#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 1<<24;
struct Node {
    int l, r, val;
} tr[maxn];
int tot = 0;

int a[maxn];

int clone(int u) {
    ++tot;
    tr[tot] = tr[u];
    return tot;
}

int build(int l, int r) {
    int u = ++tot;
    if(l == r) {
        tr[u].val = a[l];
    } else {
        int mid = l + ((r - l) >> 1);
        tr[u].l = build(l, mid);
        tr[u].r = build(mid + 1, r);
    }
    return u;
}

// x: 版本
int update(int u, int l, int r, int x, int val) {
    u = clone(u);
    if(l == r) {
        tr[u].val = val;
    } else {
        int mid = l + ((r - l) >> 1);
        if(x <= mid) {
            tr[u].l = update(tr[u].l, l, mid, x, val); 
        } else {
            tr[u].r = update(tr[u].r, mid + 1, r, x, val);
        }
    }
    return u;
}

int query(int u, int l, int r, int x) {
    if(l == r) {
        return tr[u].val;
    } else {
        int mid = l + ((r - l) >> 1);
        if(x <= mid) {
            return query(tr[u].l, l, mid, x);
        } else {
            return query(tr[u].r, mid + 1, r, x);
        }
    }
}


int rt[maxn];
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1;  i<= n; ++i) scanf("%d", &a[i]);
    rt[0] = build(1, n);

    int k, op, x, v;
    for(int i = 1; i <= m; ++i) {
        scanf("%d%d%d", &k, &op, &x);
        if(op == 1) {
            scanf("%d", &v);
            rt[i] = update(rt[k], 1, n, x, v);
        } else {
            printf("%d\n", query(rt[k], 1, n, x));
            rt[i] = rt[k];
        }
    }
}