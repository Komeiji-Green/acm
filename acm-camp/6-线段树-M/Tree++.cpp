#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;

const int maxn = 100000 + 5;
ll a[maxn], t[maxn<<2], lazy[maxn<<2], minv[maxn<<2];
// 区间和
void Pushup(int k) {
    t[k] = t[k<<1] + t[k<<1|1];
    minv[k] = min(minv[k<<1], minv[k<<1|1]);
}
void marking(int k, ll lz) {
    lazy[k] += lz;
    minv[k] += lz;
}
void Pushdown(int k) {
    if(lazy[k]) {
        marking(k<<1, lazy[k]);
        marking(k<<1|1, lazy[k]);
        lazy[k] = 0;
    }
}
// 递归建树: 先保存minv值
void build(int k, int l, int r) {
    if(l == r) {
        minv[k] = a[l];
        t[k] = 0;
    }
    else {
        int m = l + ((r - l) >> 1);
        build(k<<1, l, m);
        build(k<<1|1, m + 1, r);
        Pushup(k);
    }
}
// 更新：用minv值来判断该段区间是否需要更新
// 如果不需要更新，打懒标记
// 否则继续
// 初始调用时，需要[L, R] 包含于 [l, r]
int tot = 0;
void blank(int x) {
    int bl = x * 4;
    for(int i = 0; i < bl; i++) {
        putchar(' ');
    }
}
void add(int L, int R, ll v, int k, int l, int r) {
    int cur = tot;
    tot++;
    /*blank(cur);
    printf("enter: %d %d %d: ", k, l, r);
    printf("minv: %lld, lazy: %lld\n", minv[k], lazy[k]);*/
    if(L <= l && r <= R && (minv[k] + v) > 0) {   // 该区间里所有点不需要再更新
        lazy[k] += v;
        minv[k] += v;
        /*blank(cur);
        printf("back1: %d %d %d: minv: %lld, lazy: %lld\n", k, l, r, minv[k], lazy[k]);*/
    } else if(l == r) {   // 单点，需要更新
        t[k] += 1;
        minv[k] = a[l];
        /*blank(cur);
        printf("back2: %d %d %d: minv: %lld, lazy: %lld\n", k, l, r, minv[k], lazy[k]);*/
    } else {
        Pushdown(k);
        int m = l + ((r - l) >> 1);
        if(L <= m)
            add(L, R, v, k << 1, l, m);
        tot = cur + 1;
        if(R > m)
            add(L, R, v, k << 1 | 1, m + 1, r);
        Pushup(k);
        /*blank(cur);
        printf("back3: %d %d %d: minv: %lld, lazy: %lld\n", k, l, r, minv[k], lazy[k]);*/
    }
}
// 查询区间，结点下标及结点区间
// [L, R] 表示待查询区间
// k 是当前线段树结点的标号
// [l, r] 是当前线段树结点所对应的区间
ll query(int L, int R, int k, int l, int r) {
    if(L <= l && r <= R)
        return t[k];
    else {
        Pushdown(k);
        int m = l + ((r - l) >> 1);
        ll ans = 0;
        if(L <= m) 
            ans += query(L, R, k << 1, l, m);
        if(R > m) 
            ans += query(L, R, k << 1 | 1, m + 1, r); // [m + 1, r] [L, R]
        return ans;
    }
}

int main() {
    int n, m;
    char op[10];
    while(scanf("%d %d", &n, &m) != EOF) {
        memset(lazy, 0, sizeof(lazy));
        for(int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        build(1, 1, n);

        int l, r;
        while(m--) {
            scanf("%s", op);
            scanf("%d %d", &l, &r);
            if(op[0] == 'a') {
                tot = 0;
                add(l, r, -1, 1, 1, n);
            } else {
                ll ret = query(l, r, 1, 1, n);
                printf("%lld\n", ret);
            }
        }
    }
}

// [L, R] 表示待查询区间
// k 是当前线段树结点的标号
// [l, r] 是当前线段树结点所对应的区间
// 这里采用二叉树的顺序存储，于是子结点下标可以通过计算得到，同时子结点所维护区间也可以从当前区间二分得到。
ll query(int L, int R, int k, int l, int r) {
    if(L <= l && r <= R) // 如果当前区间包含于待查询区间，则直接返回其贡献 
        return t[k]; 
    else { // 否则应当向下二分以找到待查区间边界。
        Pushdown(k);
        int m = l + ((r - l) >> 1);
        ll ans = 0;
        if(L <= m) // 这里
            ans += query(L, R, 2 * k, l, m);
        if(R > m) 
            ans += query(L, R, 2 * k + 1, m + 1, r); 
        return ans;
    }
}