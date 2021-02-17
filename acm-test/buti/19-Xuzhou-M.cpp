#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 233333;
const int M = 466666;

struct Edge {
    int to, pre;
} e[M];
int last[N], tot = 0;

void ine(int a, int b) {
    ++tot;
    e[tot].to = b; e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b) { ine(a, b); ine(b, a); }

#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)

int siz[N]; // 子树大小
int dep[N]; // 深度
int anc[N][30]; // 祖先
int cen[N][2]; // 重心
bool tag[N][2];
int lg;

// dad是用来防止重复遍历的
void change(int x, int dad, int dept) {
    siz[x] = 1;
    dep[x] = dept;
    for(int i = 1; i <= lg; ++i) {
        if(dep[x] < (1 << i)) break;
        anc[x][i] = anc[anc[x][i - 1]][i - 1];
    }
    for(int i = last[x]; i; i = e[i].pre) {
        int y = e[i].to; if(y == dad) continue;
        anc[y][0] = x;
        change(y, x, dept + 1);
        siz[x] += siz[y];
    }
}

void dfs(int x, int dad) {
    int to = 0, bi = 0;
    for(int i = last[x]; i; i = e[i].pre) {
        int y = e[i].to; if(y == dad) continue;
        dfs(y, x);
        if(siz[y] * 2 > siz[x]) to = y;
        if(siz[y] * 2 == siz[x]) bi = y;
    }
    if(!to) {
        cen[x][0] = x; /*cen[x][1] = bi;*/ return;
    } 
    int y = cen[to][0], mid = (siz[x] + 1) / 2;
    if(siz[y] >= mid) cen[x][0] = y;
    else {
        int fa;
        for(; anc[y][0] && siz[anc[y][0]] < mid; y = fa) {
            for(int i = lg; i >= 0; --i) {
                if(!anc[y][i]) continue;
                if(siz[anc[y][i]] < mid) {
                    fa = anc[y][i]; break;
                }
            }
        }
        cen[x][0] = anc[y][0];
        //if(siz[y] * 2 == siz[x]) cen[x][1] = y;
    }
}

void redo(int x, int dad) {
    int c = cen[x][0], sz;
    cen[x][1] = 0;
    for(int i = last[c]; i; i = e[i].pre) {
        int cc = e[i].to;
        sz = siz[cc];
        if(sz > siz[c]) sz = siz[x] - siz[c];
        if(sz * 2 == siz[x]) cen[x][1] = cc;
    }
    for(int i = last[x]; i; i = e[i].pre) {
        int y = e[i].to; if(y == dad) continue;
        redo(y, x);
    }
}

void chk(int x, int dad) {
    for(int i = last[x]; i; i = e[i].pre) {
        int y = e[i].to; if(y == dad) continue;
        chk(y, x);
    }
    for(int j = 0; j < 2; ++j) {
        int c = cen[x][j]; if(!c) continue;
        for(int i = last[c]; i; i = e[i].pre) {
            int y = e[i].to;
            int sz = siz[y];
            if(sz > siz[c]) sz = siz[x] - siz[c];
            if(sz > siz[x] - sz) tag[x][j] = 1;
        }
    }
}


int main() {
    int n;
    cin >> n;
    for(lg = 1; lg <= 20; lg++) if(n < (1 << (lg - 1))) break;
    for(int i = 1, u, v; i < n; ++i) {
        scanf("%d %d", &u, &v);
        ine2(u, v);
    }
    change(1, 0, 1);
    dfs(1, 0);
    redo(1, 0);
    
    for(int i = 1; i <= n; ++i) {
        if(cen[i][1]) sort(cen[i], cen[i] + 2);
        printf("%d", cen[i][0]);
        if(cen[i][1]) printf(" %d", cen[i][1]);
        printf("\n");
    }
}