#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

// 可持久化并查集

const int maxn = 1000000 * 9;
struct Node {
    int l, r, fa, dep, size, id;
    bool die;
} tr[maxn];
int tot = 0;

int n, cnt;

int clone(int u) {
    ++tot;
    tr[tot] = tr[u];
    return tot;
}

int build(int l, int r) {
    int u = ++tot;
    if(l == r) {
        tr[u].fa = l;
        tr[u].dep = 1;
        tr[u].size = 1;
        tr[u].id = l;
        tr[u].die = 0;
    } else {
        int mid = l + ((r - l) >> 1);
        tr[u].l = build(l, mid);
        tr[u].r = build(mid + 1, r);
    }
    return u;
}

int update(int &cur, int last, int l, int r, int x) {
    cur = clone(last);
    if(l == r) {
        return cur;
    } else {
        int mid = l + ((r - l) >> 1);
        if(x <= mid) return update(tr[cur].l, tr[last].l, l, mid, x);
        else return update(tr[cur].r, tr[last].r, mid + 1, r, x);
    }
}

int query(int u, int l, int r, int x) {
    if(l == r) {
        return u;
    } else {
        int mid = l + ((r - l) >> 1);
        if(x <= mid) return query(tr[u].l, l, mid, x);
        else return query(tr[u].r, mid + 1, r, x);
    }
}

/*
int find(int rt, int x) {
    int u = query(rt, 1, n, x);
    if(tr[u].fa == x) return x;
    else return find(rt, tr[u].fa);
}*/


/////////////

int rt[maxn];

//  返回树上结点而非id
int find(int k, int x) {
    int cur = query(rt[k], 1, n, x);
    if(tr[cur].fa == x) return cur;
    else return find(k, tr[cur].fa);
}

void merge(int i, int k, int a, int b) {
    int na = query(rt[k], 1, n, a);
    int nb = query(rt[k], 1, n, b);
    if(tr[na].die || tr[nb].die) {
        rt[i] = rt[k];
        return;
    }
    int ua = find(k, tr[na].id);
    int ub = find(k, tr[nb].id);
    if(ua == ub) {
        rt[i] = rt[k];
        return;
    }
    if(tr[ua].dep > tr[ub].dep) {
        swap(a, b); swap(ua, ub);
    }
    int fa = tr[ua].fa, fb = tr[ub].fa, da = tr[ua].dep, db = tr[ub].dep, sz = tr[ua].size;
    int cur = update(rt[i], rt[k], 1, n, fa);
    tr[cur].fa = fb;
    cur = update(rt[i], rt[i], 1, n, fb);
    tr[cur].size += sz;
    if(da == db) tr[cur].dep++;
}

void erase(int i, int k, int a) {
    int na = query(rt[k], 1, n, a);
    if(tr[na].die) {
        rt[i] = rt[k];
        return;
    }
    tr[na].die = 1;
    int ua = find(k, tr[na].id);
    int cur = update(rt[i], rt[k], 1, n, tr[ua].fa);
    tr[cur].size--;
}

void move(int i, int k, int a, int b) {
    int na = query(rt[k], 1, n, a);
    int nb = query(rt[k], 1, n, b);
    if(tr[na].die || tr[nb].die) {
        rt[i] = rt[k];
        return;
    }
    int ua = find(k, tr[na].id);
    int ub = find(k, tr[nb].id);
    if(ua == ub) {
        rt[i] = rt[k];
        return;
    }
    int cur = update(rt[i], rt[k], 1, n, tr[ua].fa);
    tr[cur].size--;
    cur = update(rt[i], rt[i], 1, n, a);
    tr[cur].id = ++cnt;

    int fb = tr[ub].fa;
    cur = update(rt[i], rt[i], 1, n, cnt);
    tr[cur].fa = fb;
    cur = update(rt[i], rt[i], 1, n, fb);
    tr[cur].size++;
    if(tr[cur].dep == 1) tr[cur].dep++;
}

bool check(int i, int k, int a, int b) {
    rt[i] = rt[k];
    int na = query(rt[k], 1, n, a);
    int nb = query(rt[k], 1, n, b);
    if(tr[na].die || tr[nb].die) return false;
    int ua = find(k, tr[na].id);
    int ub = find(k, tr[nb].id);
    return ua == ub;
}

int many(int i, int k, int a) {
    rt[i] = rt[k];
    int na = query(rt[k], 1, n, a);
    if(tr[na].die) return 0;
    int ua = find(k, tr[na].id);
    return tr[ua].size;
}

// 洛谷P3402
int main() {
    int m;
    scanf("%d%d", &n, &m);
    cnt = n;
    rt[0] = build(1, n);

    int k, op, a, b;
    for(int i = 1; i <= m; ++i) {
        scanf("%d", &op);
        if(op == 1) { // dsu_merge
            scanf("%d%d", &a, &b);
            merge(i, i - 1, a, b);
        } else if(op == 2) {
            scanf("%d", &k);
            rt[i] = rt[k];
        } else {
            scanf("%d%d", &a, &b);
            printf("%d\n", check(i, i - 1, a, b));
        }
    }
}