#include<iostream>
#include <queue>
#include <cstring>
#include <cstdio>
using namespace std;
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define mp make_pair

typedef long long ll;

const int M = 300000;
const int N = 2333;

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

int l, r, m;    // 左、右、边

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
        if(dfs(i))
            ans++;
    }
    return ans;
}

// jakldndklnklangklndsalnglkdnaslngkldsnalngkldnlangldasgd

char s[505][506];
struct Pos{
    int r, c;
} pos[5000];

int main()
{
    int sz, k;
    scanf("%d %d", &sz, &k);
    
    int u, v;
    rep(i, 1, k) {
        scanf("%d %d", &u, &v);
        ine(u, sz + v, 0);
    }

    l = sz;
    int ans = Hungarian();
    printf("%d\n", ans);
}