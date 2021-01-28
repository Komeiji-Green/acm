#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
typedef int ll;

const ll inf = 0x3f3f3f3f;

int n;

const int N = 100500;
int mm[N];
ll dp[N][25], a[N];
void initrmq() {
    mm[0] = -1;
    for(int i = 1; i <= n; i++) {
        if(i & (i - 1)) mm[i] = mm[i - 1];
        else mm[i] = mm[i - 1] + 1;
    }

    for(int i = 1; i <= n; i++) {
        dp[i][0] = a[i];
    }

    for(int k = 1; k <= 20; k++) {
        for(int i = 1; i <= n; i++) {
            if((i + (1 << k)) > (n + 1)) break;
            dp[i][k] = min(dp[i][k - 1], dp[i + (1 << (k - 1))][k - 1]);
        }
    }
}
// [l, r]
ll sub_rmq(int l, int r) {
    int k = mm[r - l + 1];
    return min(dp[l][k], dp[r + 1 - (1 << k)][k]);
}
ll rmq(int l, int r) {
    int ql = (l - 1) / n, qr = (r - 1) / n;
    l = (((l - 1) % n + n) % n + 1);
    r = (((r - 1) % n + n) % n + 1);
    ll ret = inf;
    if(ql + 1 < qr) {
        return sub_rmq(1, n);
    } else if(ql < qr) {
        return min(sub_rmq(l, n), sub_rmq(1, r));
    } else {
        return sub_rmq(l, r);
    }
}


const int maxn = 10000000 + 5;
ll t[maxn], lazy[maxn];
int ch[maxn][2];
int tot = 0;

// 区间和
void Pushup(int k, int l, int r) {
    int m = l + ((r - l) >> 1);
    t[k] = min(ch[k][0] ? t[ch[k][0]] : rmq(l, m), ch[k][1] ? t[ch[k][1]] : rmq(m + 1, r));
}
void marking(int &k, ll lz) {
    if(!k) k = ++tot;
    lazy[k] = t[k] = lz;
}
void Pushdown(int k) {
    if(lazy[k]) {
        marking(ch[k][0], lazy[k]);
        marking(ch[k][1], lazy[k]);
        lazy[k] = 0;
    }
}
// 动态开点：动态建树，在单次操作后，所有与操作区间有交集的极大树上区间均被开出
void add(int L, int R, ll v, int &k, int l, int r) {
    if(!k) k = ++tot;
    if(L <= l && r <= R) {
        lazy[k] = v;
        t[k] = v;
    } else {
        Pushdown(k);
        int m = l + ((r - l) >> 1);
        if(L <= m)
            add(L, R, v, ch[k][0], l, m); 
        if(R > m) 
            add(L, R, v, ch[k][1], m + 1, r);
        Pushup(k, l, r);
    }
}
// 查询区间，结点下标及结点区间
ll query(int L, int R, int &k, int l, int r) {
    if(!k) {
        k = ++tot;
        t[k] = rmq(l, r);
    }
    if(L <= l && r <= R)
        return t[k];
    else {
        Pushdown(k);
        int m = l + ((r - l) >> 1);
        ll ret = inf;
        if(L <= m) 
            ret = min(ret, query(L, R, ch[k][0], l, m));
        if(R > m) 
            ret = min(ret, query(L, R, ch[k][1], m + 1, r)); // [m + 1, r] [L, R]
        //Pushup(k, l, r);
        return ret;
    }
}

int root = 0;

// 动态开点+ST表，CF803G
int main() {
    int k, m;
    cin >> n >> k;
    m = n * k;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    initrmq();
    /*for(int k = 0; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            printf("%d %d: %d\n", i, i + k, rmq(i, i + k));
        }
    }*/
    int q, op, L, R, X;
    cin >> q;
    while(q--) {
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d %d %d", &L, &R, &X);
            add(L, R, X, root, 1, m);
        } else if(op == 2) {
            scanf("%d %d", &L, &R);
            int ret = query(L, R, root, 1, m);
            printf("%d\n", ret);
        } else if(op == 3) {
            for(int i = 1; i <= tot; i++) {
                printf("%d: value: %d, lazy: %d, lch: %d, rch: %d\n", i, t[i], lazy[i], ch[i][0], ch[i][1]);
            }
        }
    }
}

