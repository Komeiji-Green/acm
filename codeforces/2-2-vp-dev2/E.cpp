#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 233333;

char s[maxn], tt[maxn];
int le[maxn], ri[maxn];

int t[maxn<<2], lazy[maxn<<2];
// 区间和
void Pushup(int k) {
    t[k] = t[k<<1] + t[k<<1|1];
}
void Pushdown(int k, int len1, int len2) {
    if(lazy[k] != -1) {
        lazy[k << 1] = lazy[k];
        lazy[k << 1 | 1] = lazy[k];
        t[k << 1] = lazy[k] * len1;
        t[k << 1 | 1] = lazy[k] * len2;
        lazy[k] = -1;
    }
}
// 递归建树: 结点下标，结点对应的区间左右边界
void build(int k, int l, int r) {
    lazy[k] = -1;
    if(l == r) t[k] = (tt[l] == '1') ? 1 : 0;
    else {
        int m = l + ((r - l) >> 1);
        build(k<<1, l, m);
        build(k<<1|1, m + 1, r);
        Pushup(k);
    }
}

bool flag;
void chk(int k, int l, int r) {
    if(l == r) {
        if((s[l] - '0') != t[k]) flag = 0;
    } else {
        int m = l + ((r - l) >> 1);
        Pushdown(k, m - l + 1, r - m);
        chk(k<<1, l, m);
        chk(k<<1|1, m + 1, r);
    }
}

int query(int k, int L, int R, int l, int r) {
    if(L <= l && r <= R) {
        return t[k];
    } else {
        int mid = ((l + r) >> 1);
        Pushdown(k, mid - l + 1, r - mid);
        int res = 0;
        if(L <= mid) res += query(k<<1, L, R, l, mid);
        if(R > mid) res += query(k<<1|1, L, R, mid + 1, r);
        return res;
    }
}

void update(int k, int L, int R, int v, int l, int r) {
    if(L <= l && r <= R) {
        lazy[k] = v;
        t[k] = v * (r - l + 1);
    } else {
        int m = l + ((r - l) >> 1);
        Pushdown(k, m - l + 1, r - m);
        if(L <= m) update(k<<1, L, R, v, l, m);
        if(R > m) update(k<<1|1, L, R, v, m + 1, r);
        Pushup(k);
    }
}

int main() {
    int T;
    cin >> T;
    while(T--) {
        int n, q;
        scanf("%d %d", &n, &q);
        scanf("%s %s", s + 1, tt + 1);
        build(1, 1, n);
        for(int i = 1; i <= q; ++i) {
            scanf("%d %d", &le[i], &ri[i]);
        }
        bool f = 1;
        for(int i = q; i >= 1; --i) {
            int L = le[i], R = ri[i];
            int cnt1 = query(1, L, R, 1, n);
            int cnt0 = (R - L + 1) - cnt1;
            int num = (R - L + 1);
            int hf = (num + 1) / 2;
            if(cnt1 < hf) {
                //printf("%d: 1 to 0\n", i);
                update(1, L, R, 0, 1, n);
            } else if(cnt0 < hf) {
                update(1, L, R, 1, 1, n);
                //printf("%d: 0 to 1\n", i);
            } else {
                f = 0; break;
                //printf("hfhf\n", i);
            }
        }
        if(f) {
            flag = 1; chk(1, 1, n);
            if(!flag) {
                f = 0;
                //printf("nomatch\n");
            }
        }
        if(f) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }   
}