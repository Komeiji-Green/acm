#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 33033333;
const ll M = 200000;
const int N = 233333;

ll t[maxn];
int lch[maxn], rch[maxn], tot, n;
void pushup(int k) {
    t[k] = t[lch[k]] + t[rch[k]];
}
void add(int &k, int x, ll v, int l, int r) {
    if(!k) k = ++tot;
    if(l == r) t[k] += v;
    else {
        int mid = ((l + r) >> 1);
        if(x <= mid) add(lch[k], x, v, l, mid);
        else add(rch[k], x, v, mid + 1, r);
        pushup(k);
    }
}
ll query(int k, int L, int R, int l, int r) {
    if(!k) return 0;
    if(L <= l && r <= R) {
        return t[k];
    } else {
        int mid = ((l + r) >> 1);
        ll res = 0;
        if(L <= mid) res += query(lch[k], L, R, l, mid);
        if(R > mid) res += query(rch[k], L, R, mid + 1, r);
        return res;
    }
}

int rt[N];
void ADD(int x, ll y) { // a[x] == y;
    for(int i = abs(y); i <= M; i += i & (-i)) add(rt[i], x, y, 1, n);
}
ll QUERY(int L, int R, ll y) { // sum[L<=x<=R,a[x]<=y]
    ll res = 0;
    if(y > M) y = M;
    for(int i = y; i; i -= i & (-i)) res += query(rt[i], L, R, 1, n);
    return res;
}

ll a[N];
int main() {
    int q;
    cin >> n >> q;
    for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
    int op, x, L, R;
    ll y, sum, ssum;
    for(int i = 1; i <= n; ++i) {
        ADD(i, a[i]);
    }
    while(q--) {
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d %lld", &x, &y);
            ADD(x, -a[x]); ADD(x, y);
            a[x] = y;
        } else {
            scanf("%d %d", &L, &R);
            sum = 0;
            //printf("ttt: ");
            while((ssum = QUERY(L, R, sum + 1)) > sum) {
                sum = ssum;
               // printf("%lld ", sum);
            }
            //printf("\n");
            printf("%lld\n", sum + 1);
        }

    }
}