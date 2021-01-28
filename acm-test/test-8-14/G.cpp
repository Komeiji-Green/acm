#include<iostream>
#include <queue>
#include <cstring>
using namespace std;
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define mp make_pair

typedef long long ll;

const int M = 200000;
const int N = 1000;

struct Edge {
    int from, to, pre;
    ll w;
} e[M];
int last[M];
int tot = 0;

void ine(int a, int b, ll w) {
    tot++;
    e[tot].from = a; e[tot].to = b; e[tot].w = w;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b, ll w) {
    ine(a, b, w); ine(b, a, w);
}


#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)

int n, m, l, r, color;

// 二分图染色
int col[N];
bool paint(int x, int color) {
    col[x] = color;
    reg(i, x) {
        int y = e[i].to;
        if(col[y] == col[x])
            return false;
        else if(!col[y] && !paint(y, -color)) {
            return false;
        }
    }
    return true;
}

int L[N], R[N];
int linker[N];
bool vis[N];
bool dfs(int x) {
    reg(i, x) {
        int y = e[i].to;
        if(vis[y]) continue;
        vis[y] = true;
        if(!linker[y] || dfs(linker[y])) {
            linker[y] = x;
            return true;
        }
    }
    return false;
}

int Hungarian() {
    int ans = 0;
    memset(linker, 0, sizeof(linker));
    rep(i, 1, l) {
        memset(vis, 0, sizeof(vis));
        if(dfs(L[i]))
            ans++;
    }
    return ans;
}

int main()
{
    while(scanf("%d", &n) != EOF) {
        scanf("%d", &m);
        int u, v;

        tot = 0;
        memset(last, 0, sizeof(last));
        rep(i, 1, m) {
            scanf("%d %d", &u, &v);
            ine2(u, v, 0);
        }

        color = 1;
        memset(col, 0, sizeof(col));
        bool ok = true;
        rep(i, 1, n) {
            if(!col[i]) {
                ok = paint(i, color);
                if(!ok) break;
            }
        }
        if(!ok) {
            printf("No\n");
            continue;
        }

        l = r = 0;
        rep(i, 1, n) {
            if(col[i] == 1) {
                L[++l] = i; //printf("%d: 1\n", i);
            }
            if(col[i] == -1) {
                R[++r] = i; //printf("%d: -1\n", i);
            }
        }

        int ans = Hungarian();
        printf("%d\n", ans);
    }
}