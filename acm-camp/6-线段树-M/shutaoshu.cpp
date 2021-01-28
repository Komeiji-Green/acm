#include<bits/stdc++.h>
using namespace std;

/**
 * 第一层线段树（静态）的每一个结点一颗第二层线段树（动态开）
 * 第二层线段树维护trie树上某个结点的信息（一个待区间查询的集合）
 * 那么，第一层线段树维护的就是trie树上一段dfs区间里所有结点所维护的集合的并
 * 这里trie树上任意两个结点所对应的集合是无交集的
 **/

const int N = 233333;
int tr[N][26], e[N], cur;
int t[N*100], ch[N*100][2], tot;
int n;

// 区间和
void Pushup(int k) {
    int le = ch[k][0] ? t[ch[k][0]] : 0, ri = ch[k][1] ? t[ch[k][1]] : 0;
    t[k] = le + ri;
}
// 单点修改
void add(int idx, int v, int &k, int l, int r) {
    if(!k) k = ++tot;
    if(l == r) {
        t[k] += v;
    } else {
        int m = l + ((r - l) >> 1);
        if(idx <= m)
            add(idx, v, ch[k][0], l, m); 
        else 
            add(idx, v, ch[k][1], m + 1, r);
        Pushup(k);
    }
}
// 区间查询
int query(int L, int R, int k, int l, int r) {
    if(!k) return 0;
    if(L <= l && r <= R)
        return t[k];
    else {
        int m = l + ((r - l) >> 1);
        int ret = 0;
        if(L <= m) 
            ret += query(L, R, ch[k][0], l, m);
        if(R > m) 
            ret += query(L, R, ch[k][1], m + 1, r); // [m + 1, r] [L, R]
        return ret;
    }
}

int rt[N], nn;
// -rk: trie树字典序 -x: 串所对应下标
void ADD(int rk, int x, int v) {
    for(int i = rk; i <= nn; i += i & (-i)) {
        add(x, v, rt[i], 1, n);
    }
}
int QUERY(int rk, int l, int r) {
    int res = 0;
    for(int i = rk; i; i -= i & (-i)) {
        res += query(l, r, rt[i], 1, n);
    }
    return res;
}

int node[N], id[N];
int insert(char *s) {
    int p = 0;
    for(int i = 0, c; s[i]; ++i) {
        c = s[i] - 'a';
        if(!tr[p][c]) tr[p][c] = ++cur;
        p = tr[p][c];
    }
    return p;
}

int dfn[N], post[N], clc = -1;
void dfs(int x) {
    dfn[x] = ++clc;
    for(int i = 0, y; i < 26; ++i) {
        y = tr[x][i];
        if(!y) continue;
        dfs(y);
    }
    post[x] = clc;
}

void swp(int x, int y) {
    if(x == y) return;
    ADD(id[x], x, -1);
    ADD(id[y], y, -1);
    ADD(id[x], y, 1);
    ADD(id[y], x, 1);
    swap(id[x], id[y]);
}

int gao(char *q, int k, int l, int r) {
    int p = 0;
    if(k == 0) return QUERY(clc, l, r);
    for(int i = 0, c, len = 0; q[i]; ++i) {
        c = q[i] - 'a';
        if(!tr[p][c]) return 0;
        p = tr[p][c];
        ++len;
        if(len == k) break;
    }
    return QUERY(post[p], l, r) - QUERY(dfn[p] - 1, l, r);
}

char s[N];
int main() {
    int m;
    cin >> n >> m;
    for(int i = 1; i <= n; ++i) {
        scanf("%s", s);
        node[i] = insert(s);
    }
    dfs(0);
    nn = clc;
    for(int i = 1; i <= n; ++i) {
        id[i] = dfn[node[i]];
        ADD(id[i], i, 1);
    }

    int op, k, l, r;
    while(m--) {
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d%d", &l, &r);
            swp(l, r);
        } else {
            scanf("%s%d%d%d", s, &k, &l, &r);
            printf("%d\n", gao(s, k, l, r));
        }
    }
}