#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 300007;
struct ST {
    int su[N*20], lch[N*20], rch[N*20], tot;
    void init() {
        for(int i = 0; i <= tot; ++i) su[i] = 0, lch[i] = 0, rch[i] = 0;
        tot = 0;
    }
    void pushup(int k) {
        su[k] = su[lch[k]] + su[rch[k]];
    }
    void update(int &k, int x, int v, int l, int r) {
        if(!k) k = ++tot;
        if(l == r) {
            su[k] += v;
        } else {
            int m = ((l + r) >> 1);
            if(x <= m) update(lch[k], x, v, l, m);
            else update(rch[k], x, v, m + 1, r);
            pushup(k);
        }
    }
    int query(int k, int L, int R, int l, int r) {
        if(!k) return 0;
        if(L <= l && r <= R) {
            return su[k];
        } else {
            int m = ((l + r) >> 1);
            int res = 0;
            if(L <= m) res += query(lch[k], L, R, l, m);
            if(R > m) res += query(rch[k], L, R, m+1, r);
            return res;
        }
    }
} tr, tc;
int row[N], col[N], rr[N], cc[N], cnt[2][2];

ll fun(ll n) {
    return n * (n - 1) / 2;
}
int main() {
    int T, n, m, r, c, l1, r1, l2, r2, x, y, k, d;
    ll ans;
    cin >> T;
    char op[4];
    while(T--) {
        scanf("%d %d", &n, &m);
        tr.init(); tc.init();
        for(int i = 1; i <= n; ++i) row[i] = 0, col[i] = 0;
        cnt[0][0] = cnt[0][1] = cnt[1][0] = cnt[1][1] = 0;
        for(int i = 1; i <= n; ++i) {
            scanf("%d %d", &r, &c);
            rr[i] = r; cc[i] = c;
            tr.update(row[r], c, 1, 1, n);
            tc.update(col[c], r, 1, 1, n);
            cnt[0][0] += (r == 1 && c == 1);
            cnt[0][1] += (r == 1 && c == n);
            cnt[1][0] += (r == n && c == 1);
            cnt[1][1] += (r == n && c == n);
        }
        l1 = 1, r1 = n, l2 = 1, r2 = n;
        x = 1; y = 1;
        while(m--) {
            scanf("%s", op);
            if(op[0] == 'L') {
                scanf("%d", &k);
                d = min(y-1, k);
                k -= d; y -= d;
                while(k--) {
                    if(l2 == r2) break;
                    ++l2;
                    cnt[0][0] += tc.query(col[l2], 1, l1, 1, n);
                    cnt[1][0] += tc.query(col[l2], r1, n, 1, n);
                }
            } else if(op[0] == 'R') {
                scanf("%d", &k);
                d = min(n - (y + r2 - l2), k);
                k -= d; y += d;
                while(k--) {
                    if(l2 == r2) break;
                    ++y;
                    --r2;
                    cnt[0][1] += tc.query(col[r2], 1, l1, 1, n);
                    cnt[1][1] += tc.query(col[r2], r1, n, 1, n);
                }
            } else if(op[0] == 'U') {
                scanf("%d", &k);
                d = min(x-1, k);
                k -= d; x -= d;
                while(k--) {
                    if(l1 == r1) break;
                    ++l1;
                    cnt[0][0] += tr.query(row[l1], 1, l2, 1, n);
                    cnt[0][1] += tr.query(row[l1], r2, n, 1, n);
                }
            } else if(op[0] == 'D') {
                scanf("%d", &k);
                d = min(n - (x + r1 - l1), k);
                k -= d; x += d;
                while(k--) {
                    if(l1 == r1) break;
                    ++x;
                    --r1;
                    cnt[1][0] += tr.query(row[r1], 1, l2, 1, n);
                    cnt[1][1] += tr.query(row[r1], r2, n, 1, n);
                }
            } else if(op[0] == '?') {
                scanf("%d", &k);
                r = rr[k], c = cc[k];
                if(l1 <= r && r <= r1) {
                    r = x + (r - l1);
                } else if(r < l1) {
                    r = x;
                } else {
                    r = x + r1 - l1;
                }
                if(l2 <= c && c <= r2) {
                    c = y + (c - l2);
                } else if(c < l2) {
                    c = y;
                } else {
                    c = y + r2 - l2;
                }
                printf("%d %d\n", r, c);
            } else {
                if(l1 == r1 && l2 == r2) {
                    ans = fun(n);
                } else if(l1 == r1) {
                    ans = fun(l2) + fun(n-r2+1);
                } else if(l2 == r2) {
                    ans = fun(l1) + fun(n-r1+1);
                } else {
                    ans = fun(cnt[0][0]) + fun(cnt[0][1]) + fun(cnt[1][0]) + fun(cnt[1][1]);
                }
                printf("%lld\n", ans);
            }
            //printf("pos: %d %d\n", x, y);
            //printf("sq: %d %d %d %d\n", l1, r1, l2, r2);
        }
    }
}

/*
1
5 1000 
1 1
2 2
3 3
4 4
5 5
D 1
R 1
U 1
L 1
L 2
U 1
*/