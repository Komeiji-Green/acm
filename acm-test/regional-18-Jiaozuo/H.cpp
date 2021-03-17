#pragma optimize(2)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 200005;

struct Q {
    int l, r;
};
vector<Q> vec[maxn];

struct Suffix_Automata {
    map<int, int> trans[maxn<<1];
    int len[maxn<<1], link[maxn<<1], ep[maxn<<1], sz, last;
    vector<int> G[maxn<<1];
    void clear() {
        for(int i = 0; i <= sz; ++i) {
            len[i] = 0; link[i] = 0; ep[i] = 0; trans[i].clear();
        }
        sz = 1; last = 1;
    }
    void extend(int id, int idx) {
        int cur = (++sz), p;
        len[cur] = len[last] + 1;   // len[1] == 0
        ep[cur] = idx; // endpos
        for(p = last; p && !trans[p].count(id); p = link[p]) trans[p][id] = cur;
        if(!p) link[cur] = 1;
        else {
            int q = trans[p][id];
            if(len[p] + 1 == len[q]) link[cur] = q;
            else {
                int clone = (++sz);
                len[clone] = len[p] + 1;
                trans[clone] = trans[q];
                link[clone] = link[q];
                for(; p && trans[p][id] == q; p = link[p]) trans[p][id] = clone;
                link[q] = link[cur] = clone;
            }
        }
        last = cur;
    }
    void dfs(int x) {
        for(auto y : G[x]) {
            dfs(y);
            ep[x] = max(ep[x], ep[y]);
        }
    }
    void gao() {
        for(int i = 1; i <= sz; ++i) G[i].clear(); 
        for(int i = 2; i <= sz; ++i) G[link[i]].push_back(i);
        dfs(1);
        for(int i = 2; i <= sz; ++i) {
            int L = ep[i] - len[i] + 1;
            int R = ep[i] - len[link[i]];
            vec[ep[i]].push_back((Q){L, R});
        }
    }
} sam;

int a[maxn];
struct Node {
    ll sum, lz;
    void init() {
        sum = 0; lz = 0;
    }
    void put(ll v, int len) {
        sum = v * len;
        lz = v;
    }
} tr[maxn<<2];
inline void up(int k) {tr[k].sum = tr[k<<1].sum + tr[k<<1|1].sum;}
inline void pd(int k, int len1, int len2) {
    if(tr[k].lz) {
        tr[k<<1].put(tr[k].lz,len1); 
        tr[k<<1|1].put(tr[k].lz, len2);
        tr[k].lz = 0;
    }
}
void build(int k, int l, int r) {
    tr[k].lz = 0;
    if(l == r) tr[k].sum = 0;
    else {
        int m = ((l + r) >> 1);
        build(k<<1, l, m); build(k<<1|1, m + 1, r);
        up(k);
    }
}
void update(int k, int le, int ri, int l, int r, ll v) {
    if(le <= l && r <= ri) tr[k].put(v, r-l+1);
    else {
        int m = ((l + r) >> 1);
        pd(k, m-l+1, r-m);
        if(le <= m) update(k<<1, le, ri, l, m, v);
        if(ri > m) update(k<<1|1, le, ri, m + 1, r, v);
        up(k);
    }
}

ll query(int k, int le, int ri, int l, int r) {
    if(le <= l && r <= ri) return tr[k].sum;
    else {
        int m = ((l + r) >> 1);
        pd(k, m-l+1, r-m);
        ll res = 0;
        if(le <= m) res += query(k<<1, le, ri, l, m);
        if(ri > m) res += query(k<<1|1, le, ri, m + 1, r);
        return res;
    }
}

struct Val {
    int x, y;
} stk[maxn];
ll solve(int n) {
    ll ans = 0;
    int top = 0, L, R;
    for(int i = 1; i <= n; ++i) {
        while(top && stk[top].y < a[i]) --top;
        if(!top) L = 1;
        else L = stk[top].x + 1;
        stk[++top] = (Val){i, a[i]};
        update(1, L, i, 1, n, a[i]);
        //cout << L << " " << i << endl;
        for(auto pr : vec[i]) {
            ans += query(1, pr.l, pr.r, 1, n);
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T, n;
    cin >> T;
    while(T--) {
        cin >> n;
        sam.clear();
        for(int i = 1; i <= n; ++i) vec[i].clear();
        for(int i = 1; i <= n; ++i) {
            cin >> a[i]; //cout << "extend\n";
            sam.extend(a[i], i);
        }
        sam.gao();
        //cout << "yes\n";
        /*for(int i = 1; i <= n; ++i) {
            for(auto pr : vec[i]) {
                cout << i << ": " << pr.l << " " << pr.r << endl;
            }
        }*/
        build(1, 1, n);
        ll res = solve(n);
        cout << res << endl;
    }
}