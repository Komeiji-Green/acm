#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


const int N = 233333, M = 233333;
struct Edge {
    int to, pre;
} e[M];
int last[N], tot;
void ine(int a, int b) {
    ++tot;
    e[tot].to = b; e[tot].pre = last[a];
    last[a] = tot;
}
void ine2(int a, int b) {
    ine(a, b); ine(b, a);
}

int d[N], cen;
void dfs(int x, int dad) {
    for(int i = last[x]; i; i = e[i].pre) {
        int y = e[i].to; if(y == dad) continue;
        d[y] = d[x] + 1;
        if(d[y] > d[cen]) cen = y;
        dfs(y, x);
    }
}
int n, a, b, da, db;
int main() {
    int T;
    cin >> T;
    while(T--) {
        scanf("%d %d %d %d %d", &n, &a, &b, &da, &db);
        tot = 0;
        for(int i = 0; i <= n; ++i) last[i] = 0;
        for(int i = 1, u, v; i < n; ++i) {
            scanf("%d %d", &u, &v);
            ine2(u, v);
        }
        cen = 0; d[0] = d[1] = 0;
        dfs(1, 0); d[cen] = 0; dfs(cen, 0);
        int len = d[cen];
        bool f = 1;
        if(len <= 2 * da) f = 0;
        if(f) {
            d[a] = 0; dfs(a, 0);
            if(d[b] <= da) f = 0;
        }
        if(db <= 2 * da) f = 0;
        if(f) {
            printf("Bob\n");
        } else {
            printf("Alice\n");
        }
    }
}