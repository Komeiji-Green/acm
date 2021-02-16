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

void merge1(vector<RR>& dest, vector<RR>&le, vector<RR>&ri) {
    vector<RR> vec, tmp;
    tmp = le; for(auto pr : ri) tmp.push_back(pr);
    ll x;
    int c, sz;
    for(auto pr : tmp) {
        if(!(c = pr.col)) continue;
        x = pr.x;
        bool f = 1;
        sz = vec.size();
        for(int j = 0; j < sz; ++j) {
            if(vec[j].col == c) {
                vec[j].x = max(vec[j].x, x); f = 0; break;
            }
        }
        if(f) vec.push_back(pr);
    }
    sort(vec.begin(), vec.end());
    sz = vec.size();
    dest.clear();
    for(int i = 0; i < 2 && i < sz; ++i) {
        dest.push_back(vec[sz-1-i]);
    }
}

void merge2(vector<RR>& dest, vector<RR>&le, vector<RR>&ri) {
    vector<RR> vec, tmp;
    tmp = le; for(auto pr : ri) tmp.push_back(pr);
    ll x;
    int c, sz;
    for(auto pr : tmp) {
        if(!(c = pr.col)) continue;
        x = pr.x;
        bool f = 1;
        sz = vec.size();
        for(int j = 0; j < sz; ++j) {
            if(vec[j].col == c) {
                vec[j].x = min(vec[j].x, x); f = 0; break;
            }
        }
        if(f) vec.push_back(pr);
    }
    sort(vec.begin(), vec.end());
    sz = vec.size();
    dest.clear();
    for(int i = 0; i < 2 && i < sz; ++i) {
        dest.push_back(vec[i]);
    }
}

struct ST {
    RR a[maxn];
    vector<RR> maxv[maxn<<2], minv[maxn<<2];
    void Pushup(int k) {
        int l = (k<<1), r = (k<<1|1);
        merge1(maxv[k], maxv[l], maxv[r]);
        merge2(minv[k], minv[l], minv[r]);
    }
    void build(int k, int l, int r) {
        if(l == r) {
            maxv[k].assign(1, a[l]);
            minv[k].assign(1, a[l]);
        } else {
            int m = l + ((r - l) >> 1);
            build(k<<1, l, m);
            build(k<<1|1, m + 1, r);
            Pushup(k);
        }
    }
    void update(int k, int x, int l, int r) {
        if(l == r) {
            maxv[k].assign(1, a[l]);
            minv[k].assign(1, a[l]);
        } else {
            int m = ((l + r) >> 1);
            if(x <= m) update(k<<1, x, l, m);
            else update(k<<1|1, x, m + 1, r);
            Pushup(k);
        }
    }
    void query(int k, int L, int R, vector<RR>& MM, vector<RR>& mm, int l, int r) {
        if(L <= l && r <= R) {
            MM = maxv[k]; mm = minv[k];
        } else {
            int m = ((l + r) >> 1);
            vector<RR> M1, M2, m1, m2;
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
    clock_t st = clock(), ed;
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
        vector<RR> MM, mm;
        ll res = 0;
        //printf("Case #%d:\n", cas);
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
                for(auto p1 : MM) {
                    for(auto p2 : mm) {
                        if(p1.col != p2.col) res = max(res, p1.x - p2.x);
                    }
                }
                Ty.query(1, l, r, MM, mm, 1, n);
                for(auto p1 : MM) {
                    for(auto p2 : mm) {
                        if(p1.col != p2.col) res = max(res, p1.x - p2.x);
                    }
                }
                //printf("%lld\n", res);
            }
        }
    }
    ed = clock();
    cout << (double)(ed - st) / 1000 << endl;
}