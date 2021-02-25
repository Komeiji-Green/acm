#include<bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define mp make_pair

typedef long long ll;

const int M = 2333333;
const int N = 233333;

struct Edge {
    int to, pre;
} e[M];
int last[N], tot;

void ine(int a, int b) {
    ++tot;
    e[tot].to = b;
    e[tot].pre = last[a];
    last[a] = tot;
}
inline void ine2(int a, int b) { ine(a, b); ine(b, a); }

#define reg(i, x) for(int i = last[x]; i; i = e[i].pre)


int clc, low[N], dfn[N];
bool vis[N];
int sta[N], top = 0;
int scc[N], sccnum = 0;
void init(int n) {
    tot = 0; clc = 0; sccnum = 0; top = 0;
    for(int i = 1; i <= n; ++i) last[i] = 0, vis[i] = 0, low[i] = 0, dfn[i] = 0;
}
queue<int> q;
void tarjan(int cur, int dad) {
    sta[++top] = cur;
    vis[cur] = 0;
    dfn[cur] = ++clc;
    low[cur] = clc;
    reg(i, cur) {
        int nex = e[i].to;
        if (!dfn[nex]) { // 树边
            tarjan(nex, cur);
            low[cur] = min(low[cur], low[nex]);
        } else if (!vis[nex]) { // 横边
            low[cur] = min(low[cur], dfn[nex]);
        }
    }
    if((dfn[cur] == low[cur]) /*|| (dad == 0 && !flag)*/) { 
        sccnum++;
        do {
            vis[sta[top]] = 1;
            scc[sta[top]] = sccnum;
        } while(top && sta[top--] != cur);
    }
}

int f[N];
int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}
void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    f[fx] = fy;
}

char s[N];
vector<int> vec[N], G[N];
int main() {
    int T;
    cin >> T;
    while(T--) {
        int n, m, nn;
        scanf("%d %d", &n, &m);
        nn = 2 * n + 1;
        for(int i = 1; i <= nn; ++i) f[i] = i, vec[i].clear(), G[i].clear();
        scanf("%s", s + 1);
        for(int i = 1, u, v, x, y; i <= m; ++i) {
            scanf("%d %d", &u, &v);
            merge(abs(u), abs(v));
            x = u > 0 ? (abs(u)<<1|1) : (abs(u)<<1);
            y = v > 0 ? (abs(v)<<1|1) : (abs(v)<<1);
            G[x^1].push_back(y);
            G[y^1].push_back(x);
        }
        for(int i = 1; i <= n; ++i) {
            int fa = find(i);
            vec[fa].push_back(i);
        }
        bool fl = 1;
        for(int i = 1; i <= n; ++i) {
            if(!vec[i].size()) continue;
            int sz = vec[i].size();
            for(int j = 1; j < sz; ++j) {
                if(s[vec[i][j]]=='A') fl = 0;
            }
            int p = vec[i][0];
            if(s[p] == 'E') {
                tot = 0; clc = 0; sccnum = 0; top = 0;
                for(int j : vec[i]) last[j<<1] = last[j<<1|1] = 0, vis[j<<1] = vis[j<<1|1] = 0, low[j<<1] = low[j<<1|1] = 0, dfn[j<<1] = dfn[j<<1|1] = 0;
                for(int j : vec[i]) {
                    int x = (j<<1);
                    for(int y : G[x]) ine(x, y);
                    x = (j<<1|1);
                    for(int y : G[x]) ine(x, y);
                }
                for(int j : vec[i]) {
                    if(!dfn[j<<1]) tarjan(j<<1, 0);
                    if(!dfn[j<<1|1]) tarjan(j<<1|1, 0);
                }
                for(int j : vec[i]) {
                    if(scc[j<<1] == scc[j<<1|1]) fl = 0;
                }
            } else {
                tot = 0; clc = 0; sccnum = 0; top = 0;
                for(int j : vec[i]) last[j<<1] = last[j<<1|1] = 0, vis[j<<1] = vis[j<<1|1] = 0, low[j<<1] = low[j<<1|1] = 0, dfn[j<<1] = dfn[j<<1|1] = 0;
                for(int j : vec[i]) {
                    int x = (j<<1);
                    for(int y : G[x]) ine(x, y);
                    x = (j<<1|1);
                    for(int y : G[x]) ine(x, y);
                }
                ine(p<<1, p<<1|1);
                for(int j : vec[i]) {
                    if(!dfn[j<<1]) tarjan(j<<1, 0);
                    if(!dfn[j<<1|1]) tarjan(j<<1|1, 0);
                }
                for(int j : vec[i]) {
                    if(scc[j<<1] == scc[j<<1|1]) fl = 0;
                }

                tot = 0; clc = 0; sccnum = 0; top = 0;
                for(int j : vec[i]) last[j<<1] = last[j<<1|1] = 0, vis[j<<1] = vis[j<<1|1] = 0, low[j<<1] = low[j<<1|1] = 0, dfn[j<<1] = dfn[j<<1|1] = 0;
                for(int j : vec[i]) {
                    int x = (j<<1);
                    for(int y : G[x]) ine(x, y);
                    x = (j<<1|1);
                    for(int y : G[x]) ine(x, y);
                }
                ine(p<<1|1, p<<1);
                for(int j : vec[i]) {
                    if(!dfn[j<<1]) tarjan(j<<1, 0);
                    if(!dfn[j<<1|1]) tarjan(j<<1|1, 0);
                }
                for(int j : vec[i]) {
                    if(scc[j<<1] == scc[j<<1|1]) fl = 0;
                }
            }
            if(!fl) break;
        }
        if(fl) {
            printf("TRUE\n");
        } else {
            printf("FALSE\n");
        }
    }
}