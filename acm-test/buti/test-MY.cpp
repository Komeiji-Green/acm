
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#include<map>
using namespace std;
typedef long long ll;
 
const int N = 1400007;
const int maxn = 100007;
const ll M = 0x3f3f3f3f3f3f3f3f;
 
int id[1005], num;
ll pos[1005];
 
ll lsh[4][maxn<<2];
int siz[4];
int inv(ll x, int j) {
    int sz = siz[j];
    int idx = upper_bound(lsh[j] + 1, lsh[j] + sz + 1, x) - lsh[j] - 1;
    return idx;
}
//int Cnt = 0;
struct ST {
    map<ll, int> ump[N], dmp[N]; int mk;
    void clear(int k, int l, int r) {
        map<ll, int> tmp1, tmp2;
        ump[k].swap(tmp1); dmp[k].swap(tmp2);
        if(l == r) return;
        int m = ((l + r) >> 1);
        clear(k<<1, l, m); clear(k<<1|1, m + 1, r);
    }
    // tp == 1 : y - x = d;
    // tp == -1 : x + y = d;
    void update(int k, int L, int R, ll D, int tp, int idx, int l, int r) {
        if(L <= l && r <= R) {
            ll y = tp == 1 ? lsh[mk][l] + D : D - lsh[mk][l];
            if(idx) {
                if(tp == 1) ump[k].emplace(y, idx);
                else dmp[k].emplace(y, idx);
               // ++Cnt;
            } else {
                if(tp == 1) ump[k].erase(y);
                else dmp[k].erase(y);
            }
        } else {
            int m = l + ((r - l) >> 1);
            if(L <= m) update(k<<1, L, R, D, tp, idx, l, m);
            if(R > m) update(k<<1|1, L, R, D, tp, idx, m + 1, r);
        }
    }
    // tp == 1 : y - x = d;
    // tp == -1 : x + y = d;
    void query(int k, int xx, ll x, ll y, int l, int r) {
        if(!k) return;
        ll dif = (x - lsh[mk][l]);
        ll key = y - dif;
        auto it = ump[k].lower_bound(key);
        if(it != ump[k].end()) {
            pos[++num] = (it->first) + dif;
            id[num] = it->second;
        }
        key = y + dif;
        it = dmp[k].lower_bound(key);
        if(it != dmp[k].end()) {
            pos[++num] = (it->first) - dif;
            id[num] = it->second;
        }
        if(l == r) return;
        int m = l + ((r - l) >> 1);
        if(xx <= m) query(k<<1, xx, x, y, l, m);
        else query(k<<1|1, xx, x, y, m + 1, r);
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
Line seg[4][maxn];
int main() {
    int Te, n, m;
    Line cur; Point p, q;
    ll L, R, D; int tp, Type;
    ll x, y; int z, d;
    cin >> Te;
    //clock_t st = clock(), ed;
    for(int j = 0; j <= 3; ++j) T[j].mk = j;
    for(int cas = 1; cas <= Te; ++cas) {
        cin >> n >> m;
        for(int i = 1; i <= m; ++i) li[i].clear();
        for(int i = 1; i <= n; ++i) {
            cur.input();
            cur.s = cur.s * 2; cur.e = cur.e * 2;
            for(int j = 0; j <= 3; ++j) seg[j][i] = Line(cur.s.rotate(j), cur.e.rotate(j));
        }
 
        // lsh
        for(int j = 0; j <= 3; ++j) {
            for(int i = 1; i <= n; ++i) {
                lsh[j][i*4-3] = seg[j][i].s.x;
                lsh[j][i*4-2] = seg[j][i].s.x + 1;
                lsh[j][i*4-1] = seg[j][i].e.x;
                lsh[j][i*4] = seg[j][i].e.x + 1;
            }
            lsh[j][4*n+1] = -M; lsh[j][4*n+2] = M;
            sort(lsh[j] + 1, lsh[j] + 4 * n + 3);
            siz[j] = unique(lsh[j] + 1, lsh[j] + 4 * n + 3) - lsh[j] - 1;
        }
 
        for(int j = 0; j <= 3; ++j) T[j].clear(1, 1, siz[j]);
 
        for(int j = 0; j <= 3; ++j) {
            for(int i = 1, l, r; i <= n; ++i) {
                //cur = Line(seg[i].s.rotate(j), seg[i].e.rotate(j));
                seg[j][i].get(L, R, D, tp);
                l = inv(L, j); r = inv(R, j);
                T[j].update(1, l, r, D, tp, i, 1, siz[j]);
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
                int xx = inv(p.x, d);
                T[d].query(1, xx, p.x, p.y, 1, siz[d]);
                if(!num) break;
                y = M; int idx = 0;
                for(int j = 1; j <= num; ++j) {
                    if(pos[j] <= y) y = pos[j], idx = id[j];
                }
 
                li[i].push_back(idx);
 
                for(int j = 0, l, r; j <= 3; ++j) {
                    //cur = Line(seg[idx].s.rotate(j), seg[idx].e.rotate(j));
                    seg[j][idx].get(L, R, D, tp);
                    l = inv(L, j); r = inv(R, j);
                    T[j].update(1, l, r, D, tp, 0, 1, siz[j]);
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