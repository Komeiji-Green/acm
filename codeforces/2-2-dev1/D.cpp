#include<bits/stdc++.h>
using namespace std;

const int N = 1000050, M = 1000050;
struct Edge {
    int from, to, pre;
};

int deg[N], link[N];
struct Graph {
    Edge e[M];
    int last[N], tot;
    void ine(int a, int b) {
        ++tot;
        e[tot].from = a; e[tot].to = b; e[tot].pre = last[a];
        last[a] = tot;
    }
    void ine2(int a, int b) {
        ine(a, b); ine(b, a);
    }
    void init(int n) {
        tot = 0;
        for(int i = 0; i <= n; ++i) last[i] = 0;
    }
} G, iG, Tr;

vector<int> vec;
int inq[N], vis[N];

void getT(int x, int dad) {
    //if(vis[x]) return;
    vis[x] = 1;
    for(int i = iG.last[x]; i; i = iG.e[i].pre) {
        int y = iG.e[i].to; if(y == dad || vis[y]) continue;
        if(inq[x]) Tr.ine2(x, y);
        else Tr.ine2(link[y], y);
        getT(y, x);
    }
}

vector<int> li[N];
int col[N], p[N], q[N];

void dfs(int x, int dad) {
    vis[x] = 1;
    int ch = 0;
    for(int i = Tr.last[x]; i; i = Tr.e[i].pre) {
        int y = Tr.e[i].to; if(y == dad || vis[y]) continue;
        ch = y;
        dfs(y, x);
        if(!col[y]) {
            col[x] = 1; li[x].push_back(y);
        }
    }
    if(!dad && ch && !col[x]) {
        li[ch].push_back(x);
    }
    if(!dad && !ch) col[x] = 1;
}


int main() {
    int T, n, m, u, v;
    cin >> T;
    while(T--) {
        scanf("%d %d", &n, &m);

        G.init(n); iG.init(n); Tr.init(n);
        for(int i = 0; i <= n; ++i) deg[i] = 0, inq[i] = 0;
        vec.clear();

        while(m--) {
            scanf("%d %d", &u, &v);
            G.ine2(u, v); ++deg[u]; ++deg[v];
        }
        int minv = n, x;
        for(int i = 1; i <= n; ++i) {
            if(deg[i] <= minv) {
                minv = deg[i]; x = i;
            }
        }
        for(int i = G.last[x]; i; i = G.e[i].pre) {
            int y = G.e[i].to;
            vec.push_back(y);
            inq[y] = 1;
        }
        for(int y = 1; y <= n; ++y) {
            if(y != x && !inq[y]) {
                Tr.ine2(x, y);
            }
        }
        for(auto y : vec) {
            for(int i = 1; i <= n; ++i) vis[i] = 0;
            for(int i = G.last[y]; i; i = G.e[i].pre) {
                int z = G.e[i].to;
                vis[z] = 1;
            }
            link[y] = 0;
            for(int i = 1; i <= n; ++i) {
                if(vis[i]) continue;
                if(!inq[i] && !link[y]) {
                    link[y] = i;
                    iG.ine2(y, x);
                }
                if(inq[i] && i != y) {
                    iG.ine2(i, y);
                }
            }
        }
        for(int i = 1; i <= n; ++i) vis[i] = 0;
        getT(x, 0);
        for(auto y : vec) {
            if(!vis[y]) getT(y, 0);
        }
        for(int i = 1; i <= n; ++i) {
            vis[i] = 0, col[i] = 0;
            li[i].clear();
        }
        for(int i = 1; i <= n; ++i) {
            if(!vis[i]) dfs(i, 0);
        }
        int cnt = 0;
        for(int i = 1; i <= n; ++i) {
            if(col[i] == 1) {
                ++cnt;
                int sz = li[i].size();
                p[i] = cnt; q[i] = cnt + sz;
                for(int j = 0; j < sz; ++j) {
                    p[li[i][j]] = cnt + 1 + j;
                    q[li[i][j]] = cnt + j;
                }
                cnt += sz;
            }
        }
        for(int i = 1; i <= n; ++i) printf("%d ", p[i]); printf("\n");
        for(int i = 1; i <= n; ++i) printf("%d ", q[i]); printf("\n");
    }
}