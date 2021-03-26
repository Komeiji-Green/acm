#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
const int maxn = 100007;
ll po[maxn*2];
struct node {
    ll len;
    ll V, T;
    ll cnt, t1, t2;
    void init(int l, int r) {
        len = r-l+1; V = 0; T = len; cnt = 0; t1 = t2 = 0;
    }
    void put(ll n, ll d1, ll d2) {
        V = (po[n]*V%mod + len*d1%mod + (po[n]*d2%mod)*T%mod) % mod;
        T = T*po[n*2]%mod;
        t1 = (t1*po[n]%mod + d1) % mod;
        t2 = (d2*po[cnt]%mod + t2) % mod;
        cnt += n;
    }
} tr[maxn<<2];
void build(int k, int l, int r) {
    tr[k].init(l, r);
    int mid = ((l + r) >> 1);
    if(l == r) return;
    build(k<<1, l, mid); build(k<<1|1, mid + 1, r);
}
void pushdown(int k) {
    if(tr[k].cnt) {
        tr[k<<1].put(tr[k].cnt, tr[k].t1, tr[k].t2);
        tr[k<<1|1].put(tr[k].cnt, tr[k].t1, tr[k].t2);
        tr[k].cnt = 0; tr[k].t1 = tr[k].t2 = 0;
    }
}
void update(int k, int le, int ri, int l, int r, int d) {
    if(le <= l && r <= ri) {
        tr[k].put(1, d, d);
    } else {
        pushdown(k);
        int mid = ((l + r) >> 1);
        if(le <= mid) update(k<<1, le, ri, l, mid, d);
        if(ri > mid) update(k<<1|1, le, ri, mid + 1, r, d);
        tr[k].V = (tr[k<<1].V + tr[k<<1|1].V) % mod;
        tr[k].T = (tr[k<<1].T + tr[k<<1|1].T) % mod;
    }
}

ll query(int k, int le, int ri, int l, int r) {
    if(le <= l && r <= ri) return tr[k].V;
    else {
        pushdown(k);
        int mid = ((l + r) >> 1);
        ll res = 0;
        if(le <= mid) res += query(k<<1, le, ri, l, mid);
        if(ri > mid) res = (res + query(k<<1|1, le, ri, mid + 1, r)) % mod;
        return res;
    }
}

int main() {
    po[0] = 1; for(int i = 1; i < 2 * maxn; ++i) po[i] = 10ll * po[i-1] % mod;

    int TT, n, m, le, ri, d; cin >> TT;
    ll res;
    char op[10];
    for(int cas = 1; cas <= TT; ++cas) {
        scanf("%d %d", &n, &m);
        build(1, 1, n);
        printf("Case %d:\n", cas);
        while(m--) {
            scanf("%s", op);
            if(op[0] == 'w') {
                scanf("%d %d %d", &le, &ri, &d);
                update(1, le, ri, 1, n, d);
                //printf("  %lld %lld\n", tr[3].t1, tr[3].t2);
            } else {
                scanf("%d %d", &le, &ri);
                res = query(1, le, ri, 1, n);
                printf("%lld\n", (res + mod) % mod);
            }
        }
    }
} 