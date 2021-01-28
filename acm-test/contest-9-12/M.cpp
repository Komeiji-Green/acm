#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define mp make_pair

typedef long long ll;

const int M = 566666;
const int N = 233333;

struct Edge {
    int from, to, pre;
    ll w;
} e[M];
int last[N];
int tot = 0;

void ine(int a, int b, ll w) {
    tot++;
    e[tot].from = a; e[tot].to = b; e[tot].w = w;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b, ll w) { ine(a, b, w); ine(b, a, w); }

#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)

int n;
ll ch[N], fa[N], size[N];

void dfs(int x, int dad) {
    ch[x] = 0; size[x] = 1;
    reg(i, x) {
        int y = e[i].to;
        if(y == dad) continue;
        dfs(y, x);
        ch[x] += ch[y] + size[y];
        size[x] += size[y];
    }
    reg(i, x) {
        int y = e[i].to;
        if(y == dad) continue;
        fa[y] = fa[x] + ch[x] - ch[y] - size[y] + n - size[y];
    }
}

void change(int x, int dad) {
    reg(i, x) {
        int y = e[i].to;
        if(y == dad) continue;
        
    }
}

int main() {
    int n;
    cin >> n;
    int u, v;
    tot = 0;
    rep(i, 1, n - 1) {
        scanf("%d %d", &u, &v);
        ine2(u, v);
    }


}
