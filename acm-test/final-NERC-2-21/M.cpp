#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 50;
int G[N][N];
int low[N], dfn[N], clc, n;
bool vis[N];
int sta[N], top = 0;
int scc[N], sccnum = 0;

void tarjan(int x, int dad) {
    sta[++top] = x;
    vis[x] = 0; dfn[x] = ++clc; low[x] = clc;
    for(int y = 1; y <= n; ++y) {
        if(y == x || !G[x][y]) continue;
        if(!dfn[y]) {
            tarjan(y, x);
            low[x] = min(low[x], low[y]);
        } else if(!vis[y]) {
            low[x] = min(low[x], low[y]);
        }
    }
    if((dfn[x] == low[x])) {
        ++sccnum;
        do {
            vis[sta[top]] = 1;
            scc[sta[top]] = sccnum;
        } while(top && sta[top--] != x);
    }
}

int C[N][N];
int a[205][505][5];
int pos[N];

int main() {
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            scanf("%d", &G[i][j]);
        }
    }
    for(int i = 1; i <= n; ++i) {
        if(!dfn[i]) tarjan(i, 0);
    }
    for(int x = 1; x <= n; ++x) {
        for(int y = 1; y <= n; ++y) {
            if(!G[x][y]) continue;
            int u = scc[x], v = scc[y]; // u > v
            if(u == v) continue;
            C[u][v] = 1;
        }
    }
    int cnt = 0; // 边号
    for(int i = 1; i <= sccnum; ++i) {
        int h = 5 * i;
        for(int x = 1; x <= 500; ++x) for(int y = 1; y <= 5; ++y) a[h][x][y] = -1;
    }
    for(int i = 1; i <= sccnum; ++i) {
        for(int j = 1; j <= sccnum; ++j) {
            if(!C[i][j]) continue;
            // i > j
            // h, x, y
            ++cnt;
            a[5 * i][4 * cnt][3] = 0;
            for(int k = j + 1, x = 4 * cnt, y = 3; k < i; ++k) {
                a[5 * k][4 * cnt][3] = 0;
                a[5*k+1][x-1][y] = a[5*k+1][x+1][y] = a[5*k+1][x][y+1] = a[5*k+1][x][y-1] = -1;
                a[5*k+2][x-1][y] = a[5*k+2][x+1][y] = a[5*k+2][x][y+1] = a[5*k+2][x][y-1] = -1;
            }
        }
    }
    int h = 5 * sccnum + 5, x = max(4 * cnt + 5, 10), y = 5;
    for(int i = 1; i <= n; ++i) {
        int f = scc[i];
        ++pos[f]; int p = pos[f];
        a[5*f+1][p][1] = i;
    }
    printf("%d %d %d\n", x, y, h);
    for(int k = h; k >= 1; --k) {
        for(int j = 1; j <= y; ++j) {
            for(int i = 1; i <= x; ++i) {
                int ch = a[k][i][j];
                if(ch == 0) {
                    putchar('.');
                } else if(ch == -1) {
                    putchar('#');
                } else {
                    printf("%d", ch);
                }
            }
            printf("\n");
        }
        printf("\n");
    }

    /*
    for(int i = 1; i <= sccnum; ++i) {
        for(int j = 1; j <= sccnum; ++j) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }*/
    
}