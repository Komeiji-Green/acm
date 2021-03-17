#pragma optimize("Ofast")
#include<bits/stdc++.h>
#include<vector>
using namespace std;
const int maxn = 100000 + 7;
typedef long long ll;

struct RR {
    int col;
    ll x;
    bool operator< (const RR& b) {
        return x < b.x;
    }
};

void merge1(RR* dest, RR* le, RR* ri) {
    RR vec[4], tmp[4];
    for(int i = 0; i < 2; ++i) tmp[i] = le[i], tmp[i + 2] = ri[i];
    ll x;
    int c, sz = 0;
    for(int i = 0; i < 4; ++i) {
        RR pr = tmp[i];
        if(!(c = pr.col)) continue;
        x = pr.x;
        bool f = 1;
        for(int j = 0; j < sz; ++j) {
            if(vec[j].col == c) {
                vec[j].x = max(vec[j].x, x); f = 0; break;
            }
        }
        if(f) vec[sz++] = pr;
    }
    sort(vec, vec + sz);
    for(int i = 0; i < 2; ++i) dest[i].col = 0;
    for(int i = 0; i < 2 && i < sz; ++i) {
        dest[i] = vec[sz-1-i];
    }
}

void merge2(RR* dest, RR* le, RR* ri) {
    RR vec[4], tmp[4];
    for(int i = 0; i < 2; ++i) tmp[i] = le[i], tmp[i + 2] = ri[i];
    ll x;
    int c, sz = 0;
    for(int i = 0; i < 4; ++i) {
        RR pr = tmp[i];
        if(!(c = pr.col)) continue;
        x = pr.x;
        bool f = 1;
        for(int j = 0; j < sz; ++j) {
            if(vec[j].col == c) {
                vec[j].x = min(vec[j].x, x); f = 0; break;
            }
        }
        if(f) vec[sz++] = pr;
    }
    sort(vec, vec + sz);
    for(int i = 0; i < 2; ++i) dest[i].col = 0;
    for(int i = 0; i < 2 && i < sz; ++i) {
        dest[i] = vec[i];
    }
}

struct ST {
    RR a[maxn];
    RR maxv[maxn<<2][2], minv[maxn<<2][2];
    void Pushup(int k) {
        int l = (k<<1), r = (k<<1|1);
        merge1(maxv[k], maxv[l], maxv[r]);
        merge2(minv[k], minv[l], minv[r]);
    }
    void build(int k, int l, int r) {
        if(l == r) {
            maxv[k][0] = a[l]; maxv[k][1].col = 0;
            minv[k][0] = a[l]; minv[k][1].col = 0;
        } else {
            int m = l + ((r - l) >> 1);
            build(k<<1, l, m);
            build(k<<1|1, m + 1, r);
            Pushup(k);
        }
    }
    void update(int k, int x, int l, int r) {
        if(l == r) {
            maxv[k][0] = a[l]; maxv[k][1].col = 0;
            minv[k][0] = a[l]; minv[k][1].col = 0;
        } else {
            int m = ((l + r) >> 1);
            if(x <= m) update(k<<1, x, l, m);
            else update(k<<1|1, x, m + 1, r);
            Pushup(k);
        }
    }
    void query(int k, int L, int R, RR* MM, RR* mm, int l, int r) {
        if(L <= l && r <= R) {
            for(int i = 0; i < 2; ++i) MM[i] = maxv[k][i];
            for(int i = 0; i < 2; ++i) mm[i] = minv[k][i];
        } else {
            int m = ((l + r) >> 1);
            RR M1[2] = {}, M2[2] = {}, m1[2] = {}, m2[2] = {};
            if(L <= m) query(k<<1, L, R, M1, m1, l, m);
            if(R > m) query(k<<1|1, L, R, M2, m2, m + 1, r);
            merge1(MM, M1, M2);
            merge2(mm, m1, m2);
        }
    }
} Tx, Ty;

int main() {
    int T;
    cin >> T;
    for(int cas = 1; cas <= T; ++cas) {
        int n, m;
        scanf("%d %d", &n, &m);
        ll x, y;
        for(int i = 1, c; i <= n; ++i) {
            scanf("%lld %lld %d", &x, &y, &c);
            Tx.a[i].col = c; Ty.a[i].col = c;
            Tx.a[i].x = x + y; Ty.a[i].x = x - y; 
        }
        Tx.build(1, 1, n); Ty.build(1, 1, n);
        int op, k, c, l, r;
        RR MM[2], mm[2];
        ll res = 0;
        printf("Case #%d:\n", cas);
        while(m--) {
            scanf("%d", &op);
            if(op == 1) {
                scanf("%d %lld %lld", &k, &x, &y);
                Tx.a[k].x += x + y;
                Ty.a[k].x += x - y;
                Tx.update(1, k, 1, n); Ty.update(1, k, 1, n);
            } else if(op == 2) {
                scanf("%d %d", &k, &c);
                Tx.a[k].col = c; Ty.a[k].col = c;
                Tx.update(1, k, 1, n); Ty.update(1, k, 1, n);
            } else {
                scanf("%d %d", &l, &r);
                res = 0;
                Tx.query(1, l, r, MM, mm, 1, n);
                for(int i = 0; i < 2; ++i) {
                    for(int j = 0; j < 2; ++j) {
                        if(MM[i].col && mm[j].col && MM[i].col != mm[j].col) 
                            res = max(res, MM[i].x - mm[j].x);
                    }
                }
                Ty.query(1, l, r, MM, mm, 1, n);
                for(int i = 0; i < 2; ++i) {
                    for(int j = 0; j < 2; ++j) {
                        if(MM[i].col && mm[j].col && MM[i].col != mm[j].col) 
                            res = max(res, MM[i].x - mm[j].x);
                    }
                }
                printf("%lld\n", res);
            }
        }
        /*for(int i = 1; i <= 2 * n; ++i) {
            //printf("%lld %lld %d\n", (Tx.a[i].x + Ty.a[i].x) / 2, (Tx.a[i].x - Ty.a[i].x) / 2, Tx.a[i].col);
            printf("%lld %lld %d %d\n", (Tx.maxv[i][0].x), (Tx.maxv[i][1].x), Tx.maxv[i][0].col, Tx.maxv[i][1].col);
        }*/
    }
}