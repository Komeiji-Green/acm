#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;

const int maxn = 200000 + 5;
int a[maxn], t[maxn<<2], lazy[maxn<<2];

// 最大值
void Pushup(int k) {
    t[k] = max(t[k<<1], t[k<<1|1]);
}

void Pushdown(int k, int len1, int len2) {
    if(lazy[k]) {
        lazy[k << 1] += lazy[k];
        lazy[k << 1 | 1] += lazy[k];
        t[k << 1] += lazy[k] * len1;
        t[k << 1 | 1] += lazy[k] * len2;
        lazy[k] = 0;
    }
}

// 递归建树: 结点下标，结点对应的区间左右边界
void build(int k, int l, int r) {
    if(l == r) t[k] = a[l];
    else {
        int m = l + ((r - l) >> 1);
        build(k<<1, l, m);
        build(k<<1|1, m + 1, r);
        Pushup(k);
    }
}

// 查询区间，结点下标及结点区间
int query(int L, int R, int k, int l, int r) {
    if(l >= L && r <= R)
        return t[k];
    else {
        int m = l + ((r - l) >> 1);
        //Pushdown(k, m - l + 1, r - m);
        int ans = 0;
        if(L <= m) 
            ans = max(ans, query(L, R, k << 1, l, m));
        if(R > m) 
            ans = max(ans, query(L, R, k << 1 | 1, m + 1, r)); // [m + 1, r] [L, R]
        return ans;
    }
}


void update(int L, int R, int v, int k, int l, int r) {
    if(L <= l && r <= R) {
        lazy[k] += v;
        t[k] += v * (r - l + 1);
    } else {
        int m = l + ((r - l) >> 1);
        Pushdown(k, m - l + 1, r - m);
        if(L <= m)
            update(L, R, v, k << 1, l, m);
        if(R > m)
            update(L, R, v, k << 1 | 1, m + 1, r);
        Pushup(k);
    }
}

// 点更新
void update(int p, int v, int k, int l, int r) {
    if(l == r) {
        t[k] = v;
    } else {
        int m = l + ((r - l) >> 1);
        if(p <= m)
            update(p, v, k<<1, l, m);
        else
            update(p, v, k<<1|1, m + 1, r);
        Pushup(k);
    }
}


int main()
{
    int n, m;
    while(scanf("%d", &n) != EOF) {
        scanf("%d", &m);

        for(int i = 1; i <= n; i++)
            scanf("%d", &a[i]);

        build(1, 1, n);

        //memset(lazy, 0, sizeof(lazy));
        //printf("Case %d:\n", tt);
        
        char op[10];
        int l, r;
        int v;
        while(m--) {
            scanf("%s", op);
            if(op[0] == 'Q') {
                scanf("%d%d",&l,&r);
                printf("%d\n", query(l, r, 1, 1, n));
            } else {
                scanf("%d%d", &l, &v);
                update(l, v, 1, 1, n);
            }
        }
    }
}