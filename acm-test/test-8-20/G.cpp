#include<iostream>
#include <cstring>
#include <cstdio>
using namespace std;
typedef long long ll;

#define rep(i, a, b) for(int i = (a); i <= (b); i++)

typedef unsigned int uint;

const int maxn = 1000000 + 5;
unsigned int t[maxn<<2];
unsigned int lazy[maxn<<2];

void Pushup(int k) {
    int l = (k<<1);
    int r = (k<<1|1);
    t[k] = t[l] | t[r];
}

void marking(int k, uint lz) {
    lazy[k] = lz;
    t[k] = lz;
}

void Pushdown(int k) {
    if(lazy[k]) {
        marking(k<<1, lazy[k]);
        marking(k<<1|1, lazy[k]);
        lazy[k] = 0;
    }
}

// 递归建树: 结点下标，结点对应的区间左右边界
void build(int k, int l, int r) {
    if(l == r) {
        t[k] = (1 << 2);
    }
    else {
        int m = l + ((r - l) >> 1);
        build(k<<1, l, m);
        build(k<<1|1, m + 1, r);
        Pushup(k);
    }
}

// 查询区间，结点下标及结点区间
uint ans;
void query(int L, int R, int k, int l, int r) {
    if(l >= L && r <= R) {
        ans |= t[k];
    }
    else {
        int m = l + ((r - l) >> 1);
        Pushdown(k);
        if(L <= m) 
            query(L, R, k << 1, l, m);
        if(R > m) 
            query(L, R, k << 1 | 1, m + 1, r); // [m + 1, r] [L, R]
    }
}


void update(int L, int R, uint col, int k, int l, int r) {
    if(L <= l && r <= R) {
        lazy[k] = col;
        t[k] = col;
    } else {
        int m = l + ((r - l) >> 1);
        Pushdown(k);
        if(L <= m)
            update(L, R, col, k << 1, l, m);
        if(R > m)
            update(L, R, col, k << 1 | 1, m + 1, r);
        Pushup(k);
    }
}

int ret[35];
int main()
{
    int n, q;
    char op[4];
    while(scanf("%d %d", &n, &q) != EOF && n != 0 && q != 0) {
        memset(t, 0, sizeof(t));
        memset(lazy, 0, sizeof(lazy));
        build(1, 1, n);
        int a, b, c;
        rep(i, 1, q) {
            scanf("%s", op);
            if(op[0] == 'P') {
                scanf("%d %d %d", &a, &b, &c);
                update(a, b, unsigned(1<<c), 1, 1, n);
            } else {
                scanf("%d %d", &a, &b);
                ans = 0;
                query(a, b, 1, 1, n);
                int num = 0;
                rep(j, 1, 30) {
                    if(ans & (1 << j)) ret[++num] = j;
                }
                rep(j, 1, num) {
                    if(j == num) {
                        printf("%d\n", ret[j]);
                    } else {
                        printf("%d ", ret[j]);
                    }
                }
            }
        }
    }
}