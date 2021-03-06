
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#include<map>
using namespace std;
typedef long long ll;
 
const int N = 1300007;
const int maxn = 100007;
const ll M = 4000050005ll;
 
int id[1001], num;
ll pos[1001];
 
//int Cnt = 0;
struct ST {
    int lch[N], rch[N];
    map<ll, int> ump[N], dmp[N]; 
    int tot = 0;
    void clear() {
        for(int i = 0; i <= tot; ++i) ump[i].clear(), dmp[i].clear(), lch[i] = 0, rch[i] = 0;
        tot = 0;
    }
    // tp == 1 : y - x = d;
    // tp == -1 : x + y = d;
    void update(int &k, ll L, ll R, ll D, int tp, int idx, ll l, ll r) {
        if(!k) k = ++tot;
        if(L <= l && r <= R) {
            ll y = tp == 1 ? l + D : D - l;
            if(idx) {
                if(tp == 1) ump[k][y] = idx;
                else dmp[k][y] = idx;
               // ++Cnt;
            } else {
                if(tp == 1) ump[k].erase(y);
                else dmp[k].erase(y);
            }
        } else {
            ll m = l + ((r - l) >> 1);
            if(L <= m) update(lch[k], L, R, D, tp, idx, l, m);
            if(R > m) update(rch[k], L, R, D, tp, idx, m + 1, r);
        }
    }
    // tp == 1 : y - x = d;
    // tp == -1 : x + y = d;
    void query(int k, ll x, ll y, ll l, ll r) {
        if(!k) return;
        ll key = y - (x - l);
        auto it = ump[k].lower_bound(key);
        if(it != ump[k].end()) {
            pos[++num] = (it->first) + (x - l);
            id[num] = it->second;
        }
        key = y + (x - l);
        it = dmp[k].lower_bound(key);
        if(it != dmp[k].end()) {
            pos[++num] = (it->first) - (x - l);
            id[num] = it->second;
        }
        if(l == r) return;
        ll m = l + ((r - l) >> 1);
        if(x <= m) query(lch[k], x, y, l, m);
        else query(rch[k], x, y, m + 1, r);
    }
} T[4];
 
struct Point {
    ll x, y;
    Point() {}
    Point(ll _x, ll _y) {
        x = _x; y = _y;
    }
    void input() {
        scanf("%lld%lld", &x, &y);
    }
    void output() {
        printf("%lld %lld\n", x, y);
    }
    Point rotate(int op) const {
        if(op == 3) {
            return Point(x-y, x+y);
        } else if(op == 0) {
            return Point(-x-y, x-y);
        } else if(op == 1) {
            return Point(-x+y, -x-y);
        } else {
            return Point(x+y, -x+y);
        }
    }
    Point operator* (const ll p) const {
        return Point(x * p, y * p);
    }
    Point rotleft() const {
        return Point(-y, x);
    }
    Point rotright() const {
        return Point(y, -x);
    }
};
 
struct Line {
    Point s, e;
    Line() {}
    Line(Point _s, Point _e) {
        s = _s; e = _e;
    } 
    void input() {
        s.input(); e.input();
    }
    // tp == 1 : y - x = d;
    // tp == -1 : x + y = d;
    void get(ll &l, ll &r, ll &d, int &tp) {
        if(s.x > e.x) swap(s, e);
        l = s.x; r = e.x;
        if(s.y < e.y) tp = 1, d = s.y - s.x;
        else tp = -1, d = s.x + s.y;
    }
};
vector<int> li[maxn];
Line seg[maxn];
int rt[5];
int main() {
    int Te, n, m;
    Line cur; Point p, q;
    ll L, R, D; int tp, Type;
    ll x, y; int z, d;
    cin >> Te;
    //clock_t st = clock(), ed;
    for(int cas = 1; cas <= Te; ++cas) {
        cin >> n >> m;
        for(int i = 1; i <= m; ++i) li[i].clear();
        for(int i = 1; i <= n; ++i) {
            cur.input();
            cur.s = cur.s * 2; cur.e = cur.e * 2;
            seg[i] = cur;
        }
        for(int j = 0; j <= 3; ++j) {
            T[j].clear(); rt[j] = 0;
            for(int i = 1; i <= n; ++i) {
                cur = Line(seg[i].s.rotate(j), seg[i].e.rotate(j));
                cur.get(L, R, D, tp);
                T[j].update(rt[j], L, R, D, tp, i, -M, M);
            }
        }
        for(int i = 1; i <= m; ++i) {
            scanf("%lld %lld %d %d", &x, &y, &z, &d);
            p = (Point(x, y) * 2);
            if(z == 0) p.x++;
            else p.y++;
            p = p.rotate(d);
            while(1) {
 
                //p.output();
                //printf("dir: %d\n", d);
 
                num = 0;
                T[d].query(rt[d], p.x, p.y, -M, M);
                if(!num) break;
                y = M; int idx = 0;
                for(int j = 1; j <= num; ++j) {
                    if(pos[j] <= y) y = pos[j], idx = id[j];
                }
 
                li[i].push_back(idx);
 
                for(int j = 0; j <= 3; ++j) {
                    cur = Line(seg[idx].s.rotate(j), seg[idx].e.rotate(j));
                    cur.get(L, R, D, tp);
                    T[j].update(rt[j], L, R, D, tp, 0, -M, M);
                    if(j == d) Type = tp;
                }
 
                d = (d + Type + 4) % 4;
 
                p = Point(p.x, y);
                if(Type == 1) p = p.rotleft();
                else p = p.rotright();
            }
        }
        printf("Case #%d:\n", cas);
        for(int i = 1; i <= m; ++i) {
            int sz = li[i].size(); 
            printf("%d", sz);
            for(int idx : li[i]) printf(" %d", idx);
            printf("\n");
        }
        //ed = clock();
    }
    //cout << (double)(ed-st)/1000<<endl;
    //printf("%d\n", Cnt);
    return 0;
}