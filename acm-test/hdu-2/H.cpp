#include<bits/stdc++.h>
#include<vector>
using namespace std;
typedef long long ll;

const int maxn = 200050;
const ll INF = 0x7fffffffffffffff;

struct Line {
    ll a, b; int id;
    bool operator< (const Line& rhs) {
        return a < rhs.a || a == rhs.a && b > rhs.b;
    }
    ll calc(ll x) {
        x-=a; x=x*x; x=x*x;
        return x + b;
    }
} line[maxn];
ll crosspoint(Line a, Line b) {
    if(b < a) swap(a, b);
    ll le = 1, ri = 50001ll;
    ll mid = ((le + ri) >> 1);
    while(le < ri) {
        if(a.calc(mid) < b.calc(mid)) {
            le = mid + 1;
        } else {
            ri = mid;
        }
        mid = ((le + ri) >> 1);
    }
    return mid;
}
int from[maxn], to[maxn];
int qt[maxn]; ll qv[maxn];

vector<Line> vec[maxn<<2]; vector<ll> pos[maxn<<2];
int C[maxn<<2];
void clear(int k, int l, int r) {
    vec[k].clear(); C[k]=0; pos[k].clear();
    if(l == r) return;
    int mid = ((l + r) >> 1);
    clear(k<<1, l, mid); clear(k<<1|1, mid + 1, r);  
}
void update(int k, int L, int R, Line s, int l, int r) {
    if(L <= l && r <= R) {
        vec[k].push_back(s);
    } else {
        int m = ((l + r) >> 1);
        if(L <= m) update(k<<1, L, R, s, l, m);
        if(R > m) update(k<<1|1, L, R, s, m + 1, r);
    }
}
void build(int k, int l, int r) {
    int& top = C[k];
    vector<Line>& li = vec[k];
    vector<ll>& ps = pos[k];
    int sz = li.size(); ps.resize(sz);
    ll p;
    for(int i = 0; i < sz; ++i) {
        for(; top > 0; --top) {
            if(li[i].a == li[top-1].a) continue;
            p = crosspoint(li[top-1], li[i]);
            if(p > ps[top-1]) break;
        }
        li[top]=li[i]; ps[top] = top ? p : 1;
        ++top;
    }
    if(l == r) return;
    int m = ((l + r) >> 1);
    build(k<<1, l, m); build(k<<1|1, m + 1, r);
}
ll query(int k, int t, ll x, int l, int r) {
    ll res = INF;
    int top = C[k];
    vector<Line>& li = vec[k];
    vector<ll>& ps = pos[k];
    if(top) {
        auto p = upper_bound(ps.begin(), ps.begin() + top, x);
        --p;
        res = li[p-ps.begin()].calc(x);
    }
    if(l == r) return res;
    int m = ((l + r) >> 1);
    if(t <= m) res = min(res, query(k<<1, t, x, l, m));
    else res = min(res, query(k<<1|1, t, x, m + 1, r));
    return res;
}

int main() {
    int T, n, m;
    cin >> T;
    while(T--) {
        scanf("%d %d", &n, &m);
        for(int i = 1;  i<= n; ++i) {
            scanf("%lld %lld", &line[i].a, &line[i].b);
            line[i].id=i, from[i]=1;
        }
        for(int i = 1; i <= n + m; ++i) to[i] = m;
        int op, d, num = 0;
        for(int t = 1; t <= m; ++t) {
            scanf("%d", &op);
            if(op == 1) {
                ++n;
                scanf("%lld %lld", &line[n].a, &line[n].b); 
                line[n].id=n; from[n]=t;
            } else if(op == 2) {
                scanf("%d", &d);
                to[d]=t;
            } else {
                qt[++num] = t;
                scanf("%lld", &qv[num]);
            }
        }
        sort(line + 1, line + n + 1);
        clear(1, 1, m);
        for(int i = 1; i <= n; ++i) {
            int L = from[line[i].id], R = to[line[i].id];
            //printf("%d %d\n", L, R);
            update(1, L, R, line[i], 1, m);
        }
        //printf("ttttt\n");
        build(1, 1, m);  
        //printf("ttttt\n");
        ll res;
        for(int i = 1; i <= num; ++i) {
            res = query(1, qt[i], qv[i], 1, m);
            if(res == INF) printf("-1\n");
            else printf("%lld\n", res);
        }
    }
}