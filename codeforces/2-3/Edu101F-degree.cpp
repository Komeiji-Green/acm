#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 633333;
const int inf = 0x3f3f3f3f;

ll t[maxn<<2], lazy[maxn<<2];
// 区间和
void Pushup(int k) {
    t[k] = t[k<<1] + t[k<<1|1];
}
void Pushdown(int k, int len1, int len2) {
    if(lazy[k]) {
        lazy[k << 1] += lazy[k];
        lazy[k << 1 | 1] += lazy[k];
        t[k << 1] += lazy[k] * len1;
        t[k << 1 | 1] += lazy[k] * len2;
        lazy[k] = 0;
    }
}

void update(int k, int L, int R, ll v, int l, int r) {
    if(L <= l && r <= R) {
        lazy[k] += v;
        t[k] += v * (r - l + 1);
    } else {
        int m = l + ((r - l) >> 1);
        Pushdown(k, m - l + 1, r - m);
        if(L <= m) update(k<<1, L, R, v, l, m);
        if(R > m) update(k<<1|1, L, R, v, m + 1, r);
        Pushup(k);
    }
}

int pos;
void bsearch(int k, ll key, ll sum, int l, int r) {
    if(l == r) pos = l;
    else {
        int m = ((l + r) >> 1);
        Pushdown(k, m - l + 1, r - m);
        ll mid = sum + t[k<<1];
        if(key <= mid) bsearch(k<<1, key, sum, l, m);
        else if(key <= sum + t[k]) bsearch(k<<1|1, key, mid, m + 1, r);
        else return;
    }
}

int a[maxn];

struct node {
    int x; int res;
    bool operator< (const node& b) const {
        return x > b.x || x == b.x && res < b.res;
    }
};
int main() {
    int m; ll k;
    cin >> m >> k;
    int n = 600005;
    for(int i = 1; i <= m; ++i) {
        scanf("%d", &a[i]);
    }
    sort(a + 1, a + m + 1, greater<int>());
    priority_queue<node> q; q.push((node){0, 0});
    update(1, 0, 0, 1, 0, n);

    int ans = inf;
    for(int i = 1; i <= m; ++i) {
        node v = q.top(); q.pop();
        int x = v.x; 
        int res = v.res;
        //printf("%d %d\n", x, res);
        if(res > 0) q.push((node){x + 1, res - 1});
        res = (a[i] - 1) / 2;
        if(res > 0) q.push((node){x + 2, res - 1});
        res = (a[i] - 1) - (a[i] - 1) / 2;
        if(res > 0) q.push((node){x + 2, res - 1});
        update(1, x, x, -1, 0, n);
        int l, r;
        l = x + 2;
        r = x + 1 + (a[i] - 1) / 2;
        if(l <= r) update(1, l, r, 1, 0, n);
        r = x + 1 + (a[i] - 1) - (a[i] - 1) / 2;
        if(l <= r) update(1, l, r, 1, 0, n);
        pos = inf;
        bsearch(1, k, 0, 0, n);
        ans = min(ans, pos);
    }
    if(ans == inf) {
        printf("-1\n");
    } else {
        printf("%d\n", ans);
    }
}